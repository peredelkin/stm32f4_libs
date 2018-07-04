/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "timer.h"

uint16_t timer_16::DIER_Read(uint16_t mask) {
    return (TIM->DIER & mask);
}

void timer_16::DIER_Set(uint16_t mask) {
    TIM->DIER |= mask;
}

void timer_16::DIER_Reset(uint16_t mask) {
    TIM->DIER &= ~mask;
}

uint16_t timer_16::SR_Read(uint16_t mask) {
    return (TIM->SR & mask);
}

void timer_16::SR_Reset(uint16_t mask) {
    TIM->SR &= ~mask;
}

uint16_t timer_16::CCR1_Read() {
    return TIM->CCR1;
}

void timer_16::CCR1_Write(uint16_t ccr_data) {
    TIM->CCR1 = ccr_data;
}

uint16_t timer_16::CCR2_Read() {
    return TIM->CCR2;
}

void timer_16::CCR2_Write(uint16_t ccr_data) {
    TIM->CCR2 = ccr_data;
}

uint16_t timer_16::CCR3_Read() {
    return TIM->CCR3;
}

void timer_16::CCR3_Write(uint16_t ccr_data) {
    TIM->CCR3 = ccr_data;
}

uint16_t timer_16::CCR4_Read() {
    return TIM->CCR4;
}

void timer_16::CCR4_Write(uint16_t ccr_data) {
    TIM->CCR4 = ccr_data;
}

timer_16::timer_16(TIM_TypeDef* TIM_Set) {
    TIM = TIM_Set;
}