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

class timer_16 {
private:
    TIM_TypeDef* TIM;
public:

    uint16_t CCR1_Read() {
        return TIM->CCR1;
    }

    void CCR1_Write(uint16_t ccr_data) {
        TIM->CCR1 = ccr_data;
    }

    uint16_t CCR2_Read() {
        return TIM->CCR2;
    }

    void CCR2_Write(uint16_t ccr_data) {
        TIM->CCR2 = ccr_data;
    }

    uint16_t CCR3_Read() {
        return TIM->CCR3;
    }

    void CCR3_Write(uint16_t ccr_data) {
        TIM->CCR3 = ccr_data;
    }

    uint16_t CCR4_Read() {
        return TIM->CCR4;
    }

    void CCR4_Write(uint16_t ccr_data) {
        TIM->CCR4 = ccr_data;
    }

    timer_16(TIM_TypeDef* TIM_Set) {
        TIM = TIM_Set;
    }
};

class timer_16_channel_event {
private:

    timer_16 *tim;
    uint16_t(timer_16::*CCR_Read_Method)();
    void (timer_16::*CCR_Write_Method)(uint16_t ccr_data);
public:

    uint16_t Cap_Com_Read() {
        return (tim->*CCR_Read_Method)();
    }

    void Cap_Com_Write(uint16_t ccr_data) {
        (tim->*CCR_Write_Method)(ccr_data);
    }

    timer_16_channel_event(timer_16 *tim_set) {
        tim = tim_set;
    }
};

#endif /* TIMER_EVENT_H */

