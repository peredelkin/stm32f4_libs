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
    typedef void (*timer_event)();
    typedef uint16_t(timer_16::*ccr_read)();
    typedef void (timer_16::*ccr_write)(uint16_t ccr_data);
private:
    bool once;
    uint16_t interrupt_mask;
    uint16_t status_mask;
    timer_16 *tim;
    timer_event event;
    ccr_read ccr_read_method;
    ccr_write ccr_write_method;
public:

    uint16_t Cap_Com_Read() {
        return (tim->*ccr_read_method)();
    }

    void Cap_Com_Write(uint16_t ccr_data) {
        (tim->*ccr_write_method)(ccr_data);
    }

    void Event_Enable(bool once_set) {
        once = once_set;
        tim->SR_Reset(status_mask);
        tim->DIER_Set(interrupt_mask);
    }

    timer_16_channel_event(
    timer_event event_set,
    bool once_set,
    timer_16 *tim_set,
    uint16_t interrupt_mask_set,
    uint16_t status_mask_set,
    ccr_read ccr_read_method_set,
    ccr_write ccr_wrie_method_set
    ) {
        once = once_set;
        interrupt_mask = interrupt_mask_set;
        status_mask = status_mask_set;
        tim = tim_set;
        event = event_set;
        ccr_read_method = ccr_read_method_set;
        ccr_write_method = ccr_wrie_method_set;
    }
};

#endif /* TIMER_EVENT_H */

