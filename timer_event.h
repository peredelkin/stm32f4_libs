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

template <typename bit_capacity> class  timer {
private:
    TIM_TypeDef *TIM;
public:
    
};

template <typename bit_capacity> class timer_event {
private:
    uint16_t dma_interrupt_mask;
    uint16_t status_mask;
    bool once = true;
    timer <bit_capacity> *tim;
    __IO uint32_t *ccr;
public:
    timer_event(timer <bit_capacity> *tim_set,__IO uint32_t *ccr_set,
            uint16_t dma_interrupt_mask_set,uint16_t status_mask_set,
            bool once_set) {
        
    }
};

#endif /* TIMER_EVENT_H */

