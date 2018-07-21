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
//#include <usart.h>
//#include <dma.h>
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

    //Uart
//    pin usart2_tx(GPIOA, 2);
//    usart2_tx.mode(GPIO_MODER_MODER2_1);
//    usart2_tx.alternate((0b0111 << ((2 % 8)*4)));

    //Capture TIMER
    pin tim1_cap1_pin(GPIOA, 8); // PA8 TIM1_CH1
    tim1_cap1_pin.mode(GPIO_MODER_MODER8_1); //ALT
    tim1_cap1_pin.pupd(GPIO_PUPDR_PUPDR8_1); // PU
    tim1_cap1_pin.alternate((0b0001 << ((8 % 8)*4))); //AF1
}

//usart::bus usart2(USART2);

//extern "C" void USART2_IRQHandler(void) {
//    usart2.txe_handler();
//    NVIC_ClearPendingIRQ(USART2_IRQn);
//}

//void init_usart(void) {
//
//    //NVIC_EnableIRQ(USART2_IRQn);
//
//    usart2.init(SystemCoreClock / 4, 115200, true, false);
//}
//
//dma::stream dma1_ch6(DMA1_Stream6);
//
//char dma_str[50] = "Dma_inited\r\n";
//
//volatile bool actual_capture_print_flag = false;

extern "C" void DMA1_Stream6_IRQHandler(void) {
    if (DMA1->HISR & DMA_HISR_TCIF6) {
        DMA1->HIFCR = DMA_HIFCR_CTCIF6;
//        dma1_ch6.disable();
//        usart2.flag_tc_reset();
//        actual_capture_print_flag = false;
    }
    NVIC_ClearPendingIRQ(DMA1_Stream6_IRQn);
}

//void dma_init(void) {
//    /* USART2_TX: DMA1, Stream 6, Channel 4 */
//
//    NVIC_EnableIRQ(DMA1_Stream6_IRQn);
//
//    dma1_ch6.disable();
//
//    usart2.dma_tx_disable();
//
//    dma1_ch6.ch_sel(dma::CHSEL_4);
//
//    dma1_ch6.minc_enable();
//
//    dma1_ch6.dir_set(dma::DIR_M_P);
//
//    dma1_ch6.numb_of_data_set(strlen((const char*) dma_str));
//
//    dma1_ch6.periph_addr_set(usart2.data_register_addr());
//
//    dma1_ch6.mem_0_addr_set((uint32_t) dma_str);
//
//    dma1_ch6.tcie_enable();
//
//    usart2.dma_tx_enable();
//
//    usart2.flag_tc_reset();
//
//    dma1_ch6.enable();
//}

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

//uint16_t actual_capture_print = 0;

volatile uint16_t current_capture = 0;
volatile uint16_t last_capture = 0;

typedef struct {
    volatile uint16_t tnbm2_w;
    volatile uint16_t tnbm1_w;
    volatile uint16_t tnbm_w;
}tooth_times_t;

tooth_times_t Tooth_Times;

typedef struct {
    volatile bool B_bm1;
}gap_search_t;

gap_search_t Gap_Search;

#define SY_ZSGMT 58 //system constant segment length in camshaft teeth

typedef struct {
    volatile bool B_zztab;
    volatile uint8_t zztabptr;
    volatile bool B_bm;
    volatile uint16_t zztab[SY_ZSGMT];
}zztab_store_t;

zztab_store_t Zztab_Store;

typedef struct {
    bool check_ok;
    bool one_missed;
    bool one_to_much;
} gap_check_t;

gap_check_t Gap_Check;

void ggdpg_zztab_store_init(zztab_store_t* zztab_store_struct) {
    zztab_store_struct->B_zztab = false;
    zztab_store_struct->zztabptr = 2;
    zztab_store_struct->B_bm = false;
}

void ggdpg_zztab_store(zztab_store_t* zztab_store_struct,tooth_times_t* tooth_times_struct,gap_search_t* gap_search_struct) {
    if(gap_search_struct->B_bm1) {
        if(zztab_store_struct->B_bm) {
            zztab_store_struct->zztab[zztab_store_struct->zztabptr] = tooth_times_struct->tnbm_w; //current capture time
            if(zztab_store_struct->zztabptr == (SY_ZSGMT-1)) {
                zztab_store_struct->B_zztab = true;
                zztab_store_struct->zztabptr = 0;
                blue_led.set(); //just for test
            } else {
                zztab_store_struct->zztabptr = zztab_store_struct->zztabptr + 1;
            }
        } else {
            zztab_store_struct->zztab[0] = tooth_times_struct->tnbm1_w; // 1st tooth with 3T
            zztab_store_struct->zztab[1] = tooth_times_struct->tnbm_w; // 2nd tooth with 1T (current capture time)
            zztab_store_struct->B_bm = true;
        }
    } else {
        if(zztab_store_struct->B_bm) {
            ggdpg_zztab_store_init(zztab_store_struct);
        }
    }
}

void ggdpg_tooth_times_shift_init(tooth_times_t *tooth_times_struct) {
    tooth_times_struct->tnbm1_w = 0xffff;
    tooth_times_struct->tnbm2_w = 0xffff;
    tooth_times_struct->tnbm_w = 0xffff;
}

void ggdpg_tooth_times_shift(tooth_times_t *tooth_times_struct,uint16_t capture_time) {
    tooth_times_struct->tnbm2_w = tooth_times_struct->tnbm1_w;
    tooth_times_struct->tnbm1_w = tooth_times_struct->tnbm_w;
    tooth_times_struct->tnbm_w = capture_time;
}

void ggdpg_gap_search_init(gap_search_t* gap_search_struct) {
    gap_search_struct->B_bm1 = false;
}

void ggdpg_gap_search(gap_search_t* gap_search_struct, tooth_times_t *tooth_times_struct) {
    if (gap_search_struct->B_bm1) {
        // (!)
    } else {
        uint16_t gap = tooth_times_struct->tnbm1_w / 2;
        if (gap > tooth_times_struct->tnbm_w) {
            if (gap > tooth_times_struct->tnbm2_w) {
                gap_search_struct->B_bm1 = true;
                blue_led.set(); //just for test
            }
        }
    }
}

void  ggdpg_gap_check_init(gap_check_t* gap_check_struct) {
    gap_check_struct->check_ok = false;
    gap_check_struct->one_missed = false;
    gap_check_struct->one_to_much = false;
}

void GGDPG_init() {
    current_capture = 0;
    last_capture = 0;
    
    ggdpg_zztab_store_init(&Zztab_Store);
    ggdpg_tooth_times_shift_init(&Tooth_Times);
    ggdpg_gap_search_init(&Gap_Search);
    ggdpg_gap_check_init(&Gap_Check);
    
    blue_led.reset(); //just for test
}

void GGDPG(uint16_t capture_time) {
    blue_led.reset(); //just for test
    ggdpg_tooth_times_shift(&Tooth_Times,capture_time);
    ggdpg_gap_search(&Gap_Search,&Tooth_Times);
    ggdpg_zztab_store(&Zztab_Store,&Tooth_Times,&Gap_Search);
}

void tim1_ch1_capture(void) {
    last_capture = current_capture;
    current_capture = tim1_ch1.CapCom_Read(); //Set Current
    tim1_ch4.CapCom_Write((0xffff) + current_capture); //Set Stop
    if (tim1.State()) {
        GGDPG(current_capture-last_capture);
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
    
    red_led.set(); //stop led
    
    tim1_ch1.IT_Enable(); //Capture Interrupt Enable
}

void init_tmr1() {
    NVIC_EnableIRQ(TIM1_CC_IRQn); // Capture/compare

    TIM1->CCMR1 |= TIM_CCMR1_CC1S_0; // Capture TI1
    
    TIM1->CCMR1 |= TIM_CCMR1_IC1F_1; // Filter Fsampling=Fck_int,N=2


    TIM1->CCER |= TIM_CCER_CC1P; // Falling edge

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
//    init_usart();
//    dma_init();
    init_tmr3();
    init_tmr1();
    while (1) {
//        delay_1s();
//        if (actual_capture_print_flag==true) {
//            if (!(DMA1->HISR & DMA_HISR_TCIF6)) {
//                sprintf(dma_str, "RPM %u \r\n", 1000000 / actual_capture_print);
//                dma1_ch6.numb_of_data_set(strlen((const char*) dma_str));
//                dma1_ch6.enable();
//            }
//        }
    }
    return 0;
}

