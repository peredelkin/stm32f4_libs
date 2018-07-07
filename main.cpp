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
    //Leds
    blue_led.mode(GPIO_MODER_MODER15_0);
    red_led.mode(GPIO_MODER_MODER14_0);
    orange_led.mode(GPIO_MODER_MODER13_0);
    green_led.mode(GPIO_MODER_MODER12_0);

    //Uart
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

void tim1_ch1_capture(void);
void tim1_ch2_58_59_compare(void);
void tim1_ch3_mark_compare(void);
void tim1_ch4_stop_compare(void);

timer_16 tim1(TIM1);
timer_16_channel_event tim1_ch1(&tim1_ch1_capture, false,
        &tim1,
        TIM_DIER_CC1IE, TIM_SR_CC1IF,
        &timer_16::CCR1_Read, &timer_16::CCR1_Write);

timer_16_channel_event tim1_ch2(&tim1_ch2_58_59_compare, true,
        &tim1,
        TIM_DIER_CC2IE, TIM_SR_CC2IF,
        &timer_16::CCR2_Read, &timer_16::CCR2_Write);

timer_16_channel_event tim1_ch3(&tim1_ch3_mark_compare, true,
        &tim1,
        TIM_DIER_CC3IE, TIM_SR_CC3IF,
        &timer_16::CCR3_Read, &timer_16::CCR3_Write);

timer_16_channel_event tim1_ch4(&tim1_ch4_stop_compare, true,
        &tim1,
        TIM_DIER_CC4IE, TIM_SR_CC4IF,
        &timer_16::CCR4_Read, &timer_16::CCR4_Write);

extern "C" void TIM1_CC_IRQHandler(void) {
    tim1_ch1.IT_Handler();
    tim1_ch2.IT_Handler();
    tim1_ch3.IT_Handler();
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

uint16_t previous_capture = 0;
uint16_t current_capture = 0;
uint16_t actual_capture = 0;
uint32_t mark_compare = 0;
bool mark = false;
uint8_t tooth = 0;

void coil_handler(void) {
    if(tooth==18) {
        tim3_ch1.CapCom_Write(actual_capture+current_capture);
        tim3_ch1.IT_Enable();
    }
    if(tooth==19) {
        tim3_ch2.CapCom_Write(actual_capture+current_capture);
        tim3_ch2.IT_Enable();
    }
}

void vr_handler(void) {
    if (mark) {
        coil_handler();
        if (!(DMA1->HISR & DMA_HISR_TCIF6)) {
            sprintf(dma_str, "Cap %u,Tooth %u\r\n",actual_capture,tooth);
            dma1_ch6.numb_of_data_set(strlen((const char*) dma_str));
            dma1_ch6.enable();
        }
        switch (tooth) {
            case 57:
            {
                tim1_ch2.CapCom_Write((uint16_t) (actual_capture + current_capture));
                tim1_ch2.IT_Enable();
                tooth++;
            }
            break;
            case 58:
            {
                tim1_ch2.CapCom_Write((uint16_t) (actual_capture + current_capture));
                tim1_ch2.IT_Enable();
                tooth++;
            }
            break;
            case 60:
            {
                TIM1->EGR = TIM_EGR_CC4G; //Call Stop if Mark Missed
            }
            break;
            default:
            {
                tooth++;
            }
            break;
        }
    }
}

void tim1_ch1_capture(void) {
    previous_capture = current_capture; //Set Previous from Current
    current_capture = tim1_ch1.CapCom_Read(); //Set Current
    actual_capture = current_capture - previous_capture; //Calc Actual
    mark_compare = (uint32_t)((actual_capture*2)+(actual_capture/2)); //Calc MARK
    tim1_ch4.CapCom_Write(0xffff + current_capture); //Set Stop
    if (tim1.State()) {
        if(mark_compare < 0xffff) {
            tim1_ch3.CapCom_Write((uint16_t)(mark_compare + current_capture)); //Set Mark
            tim1_ch3.IT_Enable(); //Enable Mark
        }
        vr_handler();
        green_led.reset(); //mark led
    } else {
        tim1.Enable(); //Enable Timer
        tim1_ch4.IT_Enable(); //Enable STOP
        red_led.reset(); //stop led
    }
}

void tim1_ch2_58_59_compare(void) {
    current_capture = tim1.CNT_Read(); //Read Current CNT
    vr_handler();
    blue_led.toggle(); //58 59 led
}

void tim1_ch3_mark_compare(void) {
    mark = true;
    tooth = 0;
    green_led.set(); //mark led
}

void tim1_ch4_stop_compare(void) {
    tim1.Disable(); //Disable Timer
    tim1.CNT_Write(0); //Reset Timer
    tim3.CNT_Write(0); //Reset Slave Timer
    
    previous_capture = 0;
    current_capture = 0;
    actual_capture = 0;
    mark_compare = 0;
    mark = false;
    tooth = 0;
    
    red_led.set(); //stop led
    green_led.reset(); //mark led
    blue_led.reset(); //58 59 led
}

void init_tmr1() {
    NVIC_EnableIRQ(TIM1_CC_IRQn); // Capture/compare

    TIM1->CCMR1 |= TIM_CCMR1_CC1S_0; // Capture TI1

    TIM1->CCER |= TIM_CCER_CC1P; // Falling edge

    TIM1->CCER |= TIM_CCER_CC1E; // Capture Enable

    TIM1->PSC = (uint16_t) (168 - 1); // Prescaler

    TIM1->EGR = TIM_EGR_UG; // Re-initialize

    //=================Master========================

    TIM1->CR2 |= TIM_CR2_MMS_0; // Master 001 Enable

    TIM1->SMCR |= TIM_SMCR_MSM; // Fo better Sync

    TIM1->SMCR &= ~TIM_SMCR_TS; // ITR0

    //=================Master End=====================

    tim1_ch1.IT_Enable(); //Interrupt Enable
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
        //delay_1s();
        //                if (!(DMA1->HISR & DMA_HISR_TCIF6)) {
        //                    sprintf(dma_str, "RPM %u \r\n", 1000000 / tim1_cap.capture);
        //                    dma1_ch6.numb_of_data_set(strlen((const char*) dma_str));
        //                    dma1_ch6.enable();
        //                }
    }
    return 0;
}

