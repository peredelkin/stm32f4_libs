/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: ruslan
 *
 * Created on 29 марта 2018 г., 11:28
 */

#include <stm32f4xx.h>
#include <gpio_pin.h>
#include <usart.h>
#include <dma.h>
#include <stdio.h>

static void delay_1s(void) {
    int counter = 1000;

    SysTick->LOAD = 168000 - 1;
    SysTick->VAL = 0;
    SysTick->CTRL = SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_CLKSOURCE_Msk;

    do {
        while (!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk));
    } while (--counter > 0);

    SysTick->CTRL = 0;
}

void init_rcc(void) {
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN; //GPIO_D
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; //GPIO_A
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN; // USART2
    RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN; // DMA1
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN; // TIM1
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN; //TIM3
}

pin blue_led(GPIOD, 15);
pin red_led(GPIOD, 14);
pin orange_led(GPIOD, 13);
pin green_led(GPIOD, 12);

void init_gpio() {
    blue_led.mode(GPIO_MODER_MODER15_0);
    red_led.mode(GPIO_MODER_MODER14_0);
    orange_led.mode(GPIO_MODER_MODER13_0);
    green_led.mode(GPIO_MODER_MODER12_0);

    pin usart2_tx(GPIOA, 2);
    usart2_tx.mode(GPIO_MODER_MODER2_1);
    usart2_tx.alternate((0b0111 << ((2 % 8)*4)));

    pin tim1_cap1_pin(GPIOA, 8); // PA8 TIM1_CH1
    tim1_cap1_pin.mode(GPIO_MODER_MODER8_1); //ALT
    tim1_cap1_pin.pupd(GPIO_PUPDR_PUPDR8_1); // PD
    tim1_cap1_pin.alternate((0b0001 << ((8 % 8)*4))); //AF1
}

usart::bus usart2(USART2);

//extern "C" void USART2_IRQHandler(void) {
//    usart2.txe_handler();
//    NVIC_ClearPendingIRQ(USART2_IRQn);
//}

void init_usart(void) {

    //NVIC_EnableIRQ(USART2_IRQn);

    usart2.init(SystemCoreClock / 4, 115200, true, false);
}

dma::stream dma1_ch6(DMA1_Stream6);

char dma_str[50] = "Dma_inited\r\n";

extern "C" void DMA1_Stream6_IRQHandler(void) {
    if (DMA1->HISR & DMA_HISR_TCIF6) {
        DMA1->HIFCR = DMA_HIFCR_CTCIF6;
        dma1_ch6.disable();
        usart2.flag_tc_reset();
    }
    NVIC_ClearPendingIRQ(DMA1_Stream6_IRQn);
}

void dma_init(void) {
    /* USART2_TX: DMA1, Stream 6, Channel 4 */

    NVIC_EnableIRQ(DMA1_Stream6_IRQn);

    dma1_ch6.disable();

    usart2.dma_tx_disable();

    dma1_ch6.ch_sel(dma::CHSEL_4);

    dma1_ch6.minc_enable();

    dma1_ch6.dir_set(dma::DIR_M_P);

    dma1_ch6.numb_of_data_set(strlen((const char*) dma_str));

    dma1_ch6.periph_addr_set(usart2.data_register_addr());

    dma1_ch6.mem_0_addr_set((uint32_t) dma_str);

    dma1_ch6.tcie_enable();

    usart2.dma_tx_enable();

    usart2.flag_tc_reset();

    dma1_ch6.enable();
}

typedef struct {
    uint16_t previous = 0;
    uint16_t current = 0;
    uint16_t capture = 0;
    uint16_t half_capture = 0;
    uint32_t mark = 0;
    const uint16_t max = 65535;
} capture_t;

capture_t tim1_cap;

class timer {
public:
    TIM_TypeDef *TIM;
    timer(TIM_TypeDef *tim) {
        TIM = tim;
    }
};

timer timer_1(TIM1);
timer timer_3(TIM3);

template <uint16_t interrupt_mask,uint16_t status_mask> class timer_ch {
    typedef void (*timer_event) ();
private:
    timer *tim;
    timer_event event = NULL;
    bool once = false;
public:
    timer_ch (timer *n_timer) {
        tim = n_timer;
    }
    void EventSet(timer_event event_set,bool event_once) {
        event = event_set;
        once = event_once;
    }
    void ITEnable() {
        tim->TIM->SR &= ~status_mask;
        tim->TIM->DIER |= interrupt_mask;
    }
    void ITDisable() {
        tim->TIM->DIER &= ~interrupt_mask;
    }
    void ITHandler() {
        if(tim->TIM->DIER & interrupt_mask) {
            if(tim->TIM->SR & status_mask) {
                tim->TIM->SR &= ~status_mask;
                if(event) event();
                if(once) ITDisable();
            }
        }
    }
};

timer_ch <TIM_DIER_CC1IE,TIM_SR_CC1IF> tim1_ch1(&timer_1);
timer_ch <TIM_DIER_CC2IE,TIM_SR_CC2IF> tim1_ch2(&timer_1);
timer_ch <TIM_DIER_CC3IE,TIM_SR_CC3IF> tim1_ch3(&timer_1);

timer_ch <TIM_DIER_CC1IE,TIM_SR_CC1IF> tim3_ch1(&timer_3);
timer_ch <TIM_DIER_CC2IE,TIM_SR_CC2IF> tim3_ch2(&timer_3);

void capture_handler(TIM_TypeDef *TIM, capture_t *cap) {
    if (TIM->CR1 & TIM_CR1_CEN) {
        cap->previous = cap->current; //set prev
        cap->current = (uint16_t) TIM->CCR1; //set cur
        cap->capture = (uint16_t) (cap->max + 1 + (cap->current - cap->previous)); //calc cap
        cap->half_capture = cap->capture / 2;
        cap->mark = (cap->capture * 2)+(cap->half_capture); //calc mark
        TIM->CCR3 = (uint16_t) ((cap->max) + cap->current); //set "Stop"
        if ((cap->mark) < (cap->max)) {
            TIM->CCR2 = (uint16_t) (cap->mark + cap->current); //Set "Mark"
            tim1_ch2.ITEnable();//Enable "Mark"
        }
        blue_led.reset();
    } else {
        TIM->CCR3 = (uint16_t) cap->max; //Set "Stop"
        tim1_ch3.ITEnable(); //Enable "Stop"
        TIM->CR1 |= TIM_CR1_CEN; //Enable Timer
        red_led.set();
    }
}

void mark_handler(TIM_TypeDef *TIM, capture_t *cap) {
    if (!(DMA1->HISR & DMA_HISR_TCIF6)) {
        sprintf(dma_str, "RPM %u \r\n", 1000000 / tim1_cap.capture);
        dma1_ch6.numb_of_data_set(strlen((const char*) dma_str));
        dma1_ch6.enable();
    }
    blue_led.set();
}

void stop_handler(TIM_TypeDef *TIM, capture_t *cap) {

    TIM->CR1 &= ~TIM_CR1_CEN; //Disable Timer
    TIM->CNT = (uint16_t) 0; //Reset Timer
    TIM3->CNT = (uint16_t) 0; //Reset Slave TIM3

    cap->previous = 0;
    cap->current = 0;
    cap->capture = 0;
    cap->mark = 0;
    red_led.reset();
    blue_led.reset();
}

void tim1_ch1_event(void) {
    capture_handler(TIM1, &tim1_cap);
}

void tim1_ch2_event(void) {
    mark_handler(TIM1, &tim1_cap);
}

void tim1_ch3_event(void) {
    stop_handler(TIM1, &tim1_cap);
}

void tim3_ch1_event(void) {
    green_led.set();
}

void tim3_ch2_event(void) {
    green_led.reset();
}

extern "C" void TIM1_CC_IRQHandler(void) {
    tim1_ch1.ITHandler();
    tim1_ch2.ITHandler();
    tim1_ch3.ITHandler();
}

extern "C" void TIM3_IRQHandler(void) {
    tim3_ch1.ITHandler();
    tim3_ch2.ITHandler();
}

void init_tmr1() {
    NVIC_EnableIRQ(TIM1_CC_IRQn); // Capture/compare

    TIM1->CCMR1 |= TIM_CCMR1_CC1S_0; // Capture TI1

    TIM1->CCER |= TIM_CCER_CC1P; // Falling edge

    TIM1->CCER |= TIM_CCER_CC1E; // Capture Enable

    TIM1->PSC = (uint16_t) 168 - 1; // Prescaler

    TIM1->EGR = TIM_EGR_UG; // Re-initialize

    //Master

    TIM1->CR2 |= TIM_CR2_MMS_0; // Master 001 Enable

    TIM1->SMCR |= TIM_SMCR_MSM; // Fo better Sync

    TIM1->SMCR &= ~TIM_SMCR_TS; // ITR0
    
    tim1_ch1.EventSet(tim1_ch1_event,false);
    tim1_ch2.EventSet(tim1_ch2_event,true);
    tim1_ch3.EventSet(tim1_ch3_event,true);
    
    tim1_ch1.ITEnable(); // Capture Interrupt Enable
}

void init_tmr3() {
    NVIC_EnableIRQ(TIM3_IRQn);
    
    TIM3->CCR1 = (uint16_t) 0;
    
    TIM3->CCR2 = (uint16_t) 1000;

    TIM3->PSC = (uint16_t) 84 - 1; // Prescaler

    TIM3->EGR = TIM_EGR_UG; // Re-initialize

    //Slave

    TIM3->SMCR |= TIM_SMCR_MSM; // Fo better Sync

    TIM3->SMCR |= (TIM_SMCR_SMS_2 | TIM_SMCR_SMS_0); // Slave 101 Gated Mode

    TIM3->SMCR &= ~TIM_SMCR_TS; // ITR0

    TIM3->CR1 |= TIM_CR1_CEN; //Need Enable in Slave
    
    tim3_ch1.EventSet(tim3_ch1_event,false);
    tim3_ch2.EventSet(tim3_ch2_event,false);
    
    tim3_ch1.ITEnable();
    tim3_ch2.ITEnable();
}

/*
 * 
 */
int main(void) {
    init_rcc();
    init_gpio();
    init_usart();
    dma_init();
    init_tmr3();
    init_tmr1();
    while (1) {
        //delay_1s();
        //                if (!(DMA1->HISR & DMA_HISR_TCIF6)) {
        //                    sprintf(dma_str, "RPM %u \r\n", 1000000 / tim1_cap.capture);
        //                    dma1_ch6.numb_of_data_set(strlen((const char*) dma_str));
        //                    dma1_ch6.enable();
        //                }
    }
    return 0;
}

