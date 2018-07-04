/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   timer_event.h
 * Author: ruslan
 *
 * Created on 1 июля 2018 г., 0:06
 */

#ifndef TIMER_EVENT_H
#define TIMER_EVENT_H

#include <stm32f4xx.h>

class timer_16 {
private:
    TIM_TypeDef* TIM;
public:

    uint16_t DIER_Read(uint16_t mask);
    void DIER_Set(uint16_t mask);
    void DIER_Reset(uint16_t mask);

    uint16_t SR_Read(uint16_t mask);
    void SR_Reset(uint16_t mask);

    uint16_t CCR1_Read();
    void CCR1_Write(uint16_t ccr_data);

    uint16_t CCR2_Read();
    void CCR2_Write(uint16_t ccr_data);

    uint16_t CCR3_Read();
    void CCR3_Write(uint16_t ccr_data);

    uint16_t CCR4_Read();
    void CCR4_Write(uint16_t ccr_data);

    timer_16(TIM_TypeDef* TIM_Set);
};

class timer_16_channel_event {
private:
    bool once;
    uint16_t interrupt_mask;
    uint16_t status_mask;
    timer_16 *tim;
    void (*timer_event)();
public:
    uint16_t(timer_16::*CCR_Read_Method)();
    void (timer_16::*CCR_Write_Method)(uint16_t ccr_data);

    uint16_t Cap_Com_Read() {
        return (tim->*CCR_Read_Method)();
    }

    void Cap_Com_Write(uint16_t ccr_data) {
        (tim->*CCR_Write_Method)(ccr_data);
    }

    void Event_Enable(bool once_set) {
        once = once_set;
        tim->SR_Reset(status_mask);
        tim->DIER_Set(interrupt_mask);
    }

    timer_16_channel_event(timer_16 *tim_set,
            uint16_t interrupt_mask_set,
            uint16_t status_mask_set) {
        interrupt_mask = interrupt_mask_set;
        status_mask = status_mask_set;
        tim = tim_set;
    }
};

#endif /* TIMER_EVENT_H */

