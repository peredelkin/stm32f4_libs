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
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN; //GPIO_C
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN; //GPIO_D
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; //GPIO_A
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN; // USART2
    RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN; // DMA1
    RCC->APB2ENR |= RCC_APB2ENR_TIM8EN; // TIM8
}

pin blue_led(GPIOD, 15);
pin red_led(GPIOD, 14);

void init_gpio() {
    blue_led.mode(GPIO_MODER_MODER15_0);
    red_led.mode(GPIO_MODER_MODER14_0);

    pin usart2_tx(GPIOA, 2);
    usart2_tx.mode(GPIO_MODER_MODER2_1);
    usart2_tx.alternate((0b0111 << ((2 % 8)*4)));

    pin tim8_cap1_pin(GPIOC, 6); // PC6
    tim8_cap1_pin.mode(GPIO_MODER_MODER6_1); //ALT
    tim8_cap1_pin.pupd(GPIO_PUPDR_PUPDR6_0); // PU
    tim8_cap1_pin.alternate((0b0011 << ((6 % 8)*4))); //AF3
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

uint16_t tim8_cap1 = 0;
uint32_t tim8_ch2 = 0;
bool mark = false;
bool start = false;

extern "C" void TIM8_CC_IRQHandler(void) {
    if ((TIM8->SR & TIM_SR_CC1IF) && (TIM8->DIER & TIM_DIER_CC1IE)) { //Check capture flag
        TIM8->SR &= ~TIM_SR_CC1IF; // Clear capture flag
        if (!(TIM8->CR1 & TIM_CR1_CEN)) {
            TIM8->CR1 |= TIM_CR1_CEN; //Counter Enable
        } else {
            TIM8->CNT = (uint16_t) 0; //Reset timer
            tim8_cap1 = (uint16_t) TIM8->CCR1; //Buffering

            if (mark) {
                mark = false;
                red_led.reset();
                TIM8->CCR2 = (uint16_t) 0xFFFF; //After Mark
            } else {
                tim8_ch2 = (uint32_t) ((tim8_cap1 * 2)+(tim8_cap1 / 2)); //Calc 2.5T
                if (tim8_ch2 > ((uint32_t) 0xFFFF)) { //Check ovf for CH2
                    if (TIM8->DIER & TIM_DIER_CC2IE) {
                        TIM8->DIER &= ~TIM_DIER_CC2IE; //Compare Interrupt Disable
                        start = false; // Stop
                    }
                } else {
                    TIM8->CCR2 = (uint16_t) tim8_ch2; //Set 2.5T
                    if (!(TIM8->DIER & TIM_DIER_CC2IE)) {
                        TIM8->DIER |= TIM_DIER_CC2IE; //Compare Interrupt Enable
                    }
                }
            }
        }
    }
    if ((TIM8->SR & TIM_SR_CC2IF) && (TIM8->DIER & TIM_DIER_CC2IE)) { //Check compare flag
        TIM8->SR &= ~TIM_SR_CC2IF; //Clear compare flag
        start = true; // Start
        mark = true; // For internal needs
        red_led.set();
    }
    //NVIC_ClearPendingIRQ(TIM8_IRQn);
}

void init_tmr() {
    NVIC_EnableIRQ(TIM8_CC_IRQn);

    TIM8->CR1 &= ~TIM_CR1_CEN; //Counter Disable

    TIM8->DIER |= TIM_DIER_CC1IE; //Capture Interrupt Enable

    TIM8->CCMR1 |= TIM_CCMR1_CC1S_0; //Capture TI1

    TIM8->CCER |= TIM_CCER_CC1P; //  inverted/falling edge

    TIM8->CCER |= TIM_CCER_CC1E; //Capture Enable

    //TIM8->CCER |= TIM_CCER_CC2E; //Compare Enable

    TIM8->CCR2 = (uint16_t) 0xFFFF; //Preset compare

    TIM8->PSC = (uint16_t) 83; // Prescaler

    TIM8->EGR |= TIM_EGR_UG; // Re-initialize 
}

/*
 * 
 */
int main(void) {
    init_rcc();
    init_gpio();
    init_usart();
    dma_init();
    init_tmr();
    while (1) {
        delay_1s();
        blue_led.set();
        delay_1s();
        blue_led.reset();
        if (!(DMA1->HISR & DMA_HISR_TCIF6)) {
            sprintf(dma_str, "CH2 %u \r\n", tim8_ch2);
            dma1_ch6.numb_of_data_set(strlen((const char*) dma_str));
            dma1_ch6.enable();
        }
    }
    return 0;
}

