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
#include <timer.h>
#include <timer_event.h>
#include <timer_capture.h>

static void delay_1s(void) {
    int counter = 100;

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
    //Leds
    blue_led.mode(GPIO_MODER_MODER15_0);
    red_led.mode(GPIO_MODER_MODER14_0);
    orange_led.mode(GPIO_MODER_MODER13_0);
    green_led.mode(GPIO_MODER_MODER12_0);

    //    Uart
    pin usart2_tx(GPIOA, 2);
    usart2_tx.mode(GPIO_MODER_MODER2_1);
    usart2_tx.alternate((0b0111 << ((2 % 8)*4)));

    //Capture TIMER
    pin tim1_cap1_pin(GPIOA, 8); // PA8 TIM1_CH1
    tim1_cap1_pin.mode(GPIO_MODER_MODER8_1); //ALT
    tim1_cap1_pin.pupd(GPIO_PUPDR_PUPDR8_1); // PU
    tim1_cap1_pin.alternate((0b0001 << ((8 % 8)*4))); //AF1
}

usart::bus usart2(USART2);

extern "C" void USART2_IRQHandler(void) {
    usart2.interrupt_txe_handler();
    NVIC_ClearPendingIRQ(USART2_IRQn);
}

void init_usart(void) {

    NVIC_EnableIRQ(USART2_IRQn);

    usart2.init(SystemCoreClock / 4, 115200, true, false);
}

dma::stream dma1_ch6(DMA1_Stream6);

char dma_str[50] = "Dma_inited\r\n";

volatile bool actual_capture_print_flag = false;

extern "C" void DMA1_Stream6_IRQHandler(void) {
    if (DMA1->HISR & DMA_HISR_TCIF6) {
        DMA1->HIFCR = DMA_HIFCR_CTCIF6;
        dma1_ch6.disable();
        usart2.flag_tc_reset();
        actual_capture_print_flag = false;
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

void tim1_ch1_capture(void);

void tim1_ch4_stop_compare(void);

timer_16 tim1(TIM1);
timer_16_channel_event tim1_ch1(&tim1_ch1_capture, false,
        &tim1,
        TIM_DIER_CC1IE, TIM_SR_CC1IF,
        &timer_16::CCR1_Read, &timer_16::CCR1_Write);

timer_16_channel_event tim1_ch4(&tim1_ch4_stop_compare, true,
        &tim1,
        TIM_DIER_CC4IE, TIM_SR_CC4IF,
        &timer_16::CCR4_Read, &timer_16::CCR4_Write);

extern "C" void TIM1_CC_IRQHandler(void) {
    tim1_ch1.IT_Handler();
    tim1_ch4.IT_Handler();
}

void orange_led_on() {
    orange_led.set();
}

void orange_led_off() {
    orange_led.reset();
}

timer_16 tim3(TIM3);
timer_16_channel_event tim3_ch1(&orange_led_on, true,
        &tim3,
        TIM_DIER_CC1IE, TIM_SR_CC1IF,
        &timer_16::CCR1_Read, &timer_16::CCR1_Write);

timer_16_channel_event tim3_ch2(&orange_led_off, true,
        &tim3,
        TIM_DIER_CC2IE, TIM_SR_CC2IF,
        &timer_16::CCR2_Read, &timer_16::CCR2_Write);

extern "C" void TIM3_IRQHandler(void) {
    tim3_ch1.IT_Handler();
    tim3_ch2.IT_Handler();
}

volatile uint16_t current_capture = 0;
volatile uint16_t last_capture = 0;

#define SY_ZSGMT 60 //system constant segment length in camshaft teeth

typedef struct {
    uint16_t tnbm_w; //1st shift
    uint16_t tnbm1_w; //2nd shift
    uint16_t tnbm2_w; //3rd shift
    bool B_bm1; //gap detected
} gap_search_t;

gap_search_t Gap_Search;

typedef struct {
    uint16_t zztab[SY_ZSGMT]; //Tooth time table
    uint8_t zztabptr; //Pointer to last entry in the table
    bool R_syn;
    bool B_zztab; //Set as soon as the tooth time table is completely filled
    bool one_to_much;
    bool one_missed;
    bool check_ok;
} gap_check_t;

gap_check_t Gap_Check;

void gap_search_init(gap_search_t* gap_search_struct) {
    gap_search_struct->B_bm1 = false;
    gap_search_struct->tnbm1_w = 0xffff;
    gap_search_struct->tnbm2_w = 0xffff;
    gap_search_struct->tnbm_w = 0xffff;
}

void gap_search(uint16_t capture_time, gap_search_t* gap_search_struct, gap_check_t * gap_check_struct) {
    gap_search_struct->tnbm2_w = gap_search_struct->tnbm1_w; //Shift 2nd to 3rd
    gap_search_struct->tnbm1_w = gap_search_struct->tnbm_w; //Shift 1st to 2nd
    gap_search_struct->tnbm_w = capture_time; //Cap to 0
    if (((gap_search_struct->tnbm1_w / 2) > gap_search_struct->tnbm_w) &&
            ((gap_search_struct->tnbm1_w / 2) > gap_search_struct->tnbm2_w)) { //(tnbm2_w < tnbm1_w > tnbm_w)
        blue_led.set();
        if (gap_search_struct->B_bm1 == false) {
            gap_search_struct->B_bm1 = true;
            if (gap_check_struct->R_syn == false) {
                gap_check_struct->R_syn = true;
            }
        }
    }
}

void gap_check_init(gap_check_t * gap_check_struct) {
    gap_check_struct->R_syn = false;
    gap_check_struct->B_zztab = false;
    gap_check_struct->check_ok = false;
    gap_check_struct->one_missed = false;
    gap_check_struct->one_to_much = false;
    gap_check_struct->zztabptr = 1;
    gap_check_struct->zztab[SY_ZSGMT - 1] = 0xffff;
    gap_check_struct->zztab[SY_ZSGMT - 2] = 0xffff;
    gap_check_struct->zztab[SY_ZSGMT - 3] = 0xffff;
}

void gap_check(gap_search_t* gap_search_struct, gap_check_t * gap_check_struct) {
    if (gap_check_struct->B_zztab == false) {

        gap_check_struct->zztab[gap_check_struct->zztabptr] = gap_search_struct->tnbm_w;
        
        if (gap_check_struct->R_syn == true) {
            gap_check_struct->zztab[0] = gap_check_struct->zztab[gap_check_struct->zztabptr - 1];
            gap_check_struct->zztab[1] = gap_check_struct->zztab[gap_check_struct->zztabptr];
            gap_check_struct->zztabptr = 1;
            gap_check_struct->R_syn = false;
        }

        if (gap_check_struct->zztabptr == (SY_ZSGMT - 1)) {
            gap_check_struct->zztabptr = 1;
            if (gap_search_struct->B_bm1) {
                gap_check_struct->B_zztab = true;
            } else {
                tim1.EGR_Set(TIM_EGR_CC4G); //gen stop
            }
        } else {
            gap_check_struct->zztabptr = gap_check_struct->zztabptr + 1;
        }

        if (gap_check_struct->B_zztab == true) {
            if ((gap_check_struct->zztab[SY_ZSGMT - 3] / 2) > gap_check_struct->zztab[SY_ZSGMT - 2]) {
                gap_check_struct->one_missed = true;
                orange_led.set();
            } else {
                if (((gap_check_struct->zztab[SY_ZSGMT - 2] / 2) > gap_check_struct->zztab[SY_ZSGMT - 3]) &&
                        ((gap_check_struct->zztab[SY_ZSGMT - 2] / 2) > gap_check_struct->zztab[SY_ZSGMT - 1])) {
                    gap_check_struct->check_ok = true;
                    green_led.set();
                } else {
                    if ((gap_check_struct->zztab[SY_ZSGMT - 1] / 2) > gap_check_struct->zztab[SY_ZSGMT - 2]) {
                        gap_check_struct->one_to_much = true;
                        orange_led.set();
                    } else {
                        tim1.EGR_Set(TIM_EGR_CC4G); //gen stop
                    }
                }
            }
            gap_search_struct->B_bm1 = false;
            gap_check_struct->B_zztab = false;
        }
    }
}

//if (!(DMA1->HISR & DMA_HISR_TCIF6)) {
//                sprintf(dma_str, "-1:%u\r\n0:%u\r\n1:%u\r\n", gap_check_struct->zztab[SY_ZSGMT - 3], gap_check_struct->zztab[SY_ZSGMT - 2], gap_check_struct->zztab[SY_ZSGMT - 1]);
//                dma1_ch6.numb_of_data_set(strlen((const char*) dma_str));
//                dma1_ch6.enable();
//            }

void GGDPG_init() {
    current_capture = 0;
    last_capture = 0;

    gap_search_init(&Gap_Search);
    gap_check_init(&Gap_Check);
    //call here

    orange_led.reset();
    green_led.reset();
    blue_led.reset();
    red_led.set();
}

void GGDPG(uint16_t capture_time) {
    blue_led.reset();
    green_led.reset();
    orange_led.reset();

    gap_search(capture_time, &Gap_Search, &Gap_Check);
    gap_check(&Gap_Search, &Gap_Check);
    //call here
}

void tim1_ch1_capture(void) {
    last_capture = current_capture;
    current_capture = tim1_ch1.CapCom_Read(); //Set Current
    tim1_ch4.CapCom_Write((0xffff) + current_capture); //Set Stop
    if (tim1.State()) {
        GGDPG(current_capture - last_capture);
    } else {
        tim1.Enable(); //Enable Timer
        tim1_ch4.IT_Enable(); //Enable STOP
        red_led.reset(); //stop led
    }
}

void tim1_ch4_stop_compare(void) {
    tim1_ch1.IT_Disable(); //Capture Interrupt Disable

    tim1.Disable(); //Disable Timer
    tim1.CNT_Write(0); //Reset Timer
    tim3.CNT_Write(0); //Reset Slave Timer

    GGDPG_init(); //Re init

    tim1_ch1.IT_Enable(); //Capture Interrupt Enable
}

void init_tmr1() {
    NVIC_EnableIRQ(TIM1_CC_IRQn); // Capture/compare

    TIM1->CCMR1 |= TIM_CCMR1_CC1S_0; // Capture TI1

    TIM1->CCMR1 |= TIM_CCMR1_IC1F_1; // Filter Fsampling=Fck_int,N=2


    TIM1->CCER = TIM_CCER_CC1P; // !Falling edge

    TIM1->CCER |= TIM_CCER_CC1E; // Capture Enable

    TIM1->PSC = (uint16_t) (168 - 1); // Prescaler

    TIM1->EGR = TIM_EGR_UG; // Re-initialize

    //=================Master========================

    TIM1->CR2 |= TIM_CR2_MMS_0; // Master 001 Enable

    TIM1->SMCR |= TIM_SMCR_MSM; // Fo better Sync

    TIM1->SMCR &= ~TIM_SMCR_TS; // ITR0

    //=================Master End=====================

    tim1_ch4.IT_Enable(); //STOP Interrupt Enable
    tim1.Enable(); //Enable Timer
}

void init_tmr3() {
    NVIC_EnableIRQ(TIM3_IRQn); //Compare

    TIM3->PSC = (uint16_t) (84 - 1); // Prescaler

    TIM3->EGR = TIM_EGR_UG; // Re-initialize

    //=====================Slave=============================

    TIM3->SMCR |= TIM_SMCR_MSM; // Fo better Sync

    TIM3->SMCR |= (TIM_SMCR_SMS_2 | TIM_SMCR_SMS_0); // Slave 101 Gated Mode

    TIM3->SMCR &= ~TIM_SMCR_TS; // ITR0

    TIM3->CR1 |= TIM_CR1_CEN; //Need Enable in Slave
    //===================Slave End========================
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
//        delay_1s();
//        if (!(DMA1->HISR & DMA_HISR_TCIF6)) {
//            sprintf(dma_str, "RPM %u \r\n", 100);
//            dma1_ch6.numb_of_data_set(strlen((const char*) dma_str));
//            dma1_ch6.enable();
//        }
    }
    return 0;
}

