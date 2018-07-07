/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   timer.h
 * Author: ruslan
 *
 * Created on 4 июля 2018 г., 15:11
 */

#ifndef TIMER_H
#define TIMER_H

#include <stm32f4xx.h>

class timer_16 {
private:
    TIM_TypeDef* TIM;
public:
    uint16_t CR1_Read(uint16_t mask);
    void CR1_Set(uint16_t mask);
    void CR1_Reset(uint16_t mask);

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

#endif /* TIMER_H */

