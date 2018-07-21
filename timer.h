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

    uint16_t CR1_Read(uint16_t mask) {
        return (TIM->CR1 & mask);
    }

    void CR1_Set(uint16_t mask) {
        TIM->CR1 |= mask;
    }

    void CR1_Reset(uint16_t mask) {
        TIM->CR1 &= ~mask;
    }

    uint16_t State() {
        return (TIM->CR1 & TIM_CR1_CEN);
    }

    void Enable() {
        TIM->CR1 |= TIM_CR1_CEN;
    }

    void Disable() {
        TIM->CR1 &= ~TIM_CR1_CEN;
    }

    uint16_t DIER_Read(uint16_t mask) {
        return (TIM->DIER & mask);
    }

    void DIER_Set(uint16_t mask) {
        TIM->DIER |= mask;
    }

    void DIER_Reset(uint16_t mask) {
        TIM->DIER &= ~mask;
    }

    uint16_t SR_Read(uint16_t mask) {
        return (TIM->SR & mask);
    }

    void SR_Reset(uint16_t mask) {
        TIM->SR &= ~mask;
    }
    
    void EGR_Set(uint16_t mask) {
        TIM->EGR = mask;
    }

    uint16_t CNT_Read() {
        return TIM->CNT;
    }

    void CNT_Write(uint16_t data) {
        TIM->CNT = data;
    }

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

#endif /* TIMER_H */

