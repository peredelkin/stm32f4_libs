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

template <typename cnt_type> class timer {
public:
    TIM_TypeDef *TIM;

    timer(TIM_TypeDef *tim) {
        TIM = tim;
    }

    cnt_type CountRead() {
        return (cnt_type) (TIM->CNT);
    }

    void CountWrite(cnt_type count) {
        TIM->CNT = count;
    }

    void Disable() {
        TIM->CR1 &= ~TIM_CR1_CEN;
    }

    void Enable() {
        TIM->CR1 |= TIM_CR1_CEN;
    }

    bool Status() {
        if (TIM->CR1 & TIM_CR1_CEN) {
            return true;
        } else {
            return false;
        }
    }
};

template <uint16_t interrupt_mask, uint16_t status_mask, typename cnt_type> class timer_ch {
    typedef void (*timer_event) ();
private:
    __IO uint32_t *ccr;
    timer <cnt_type> *tim;
    timer_event event = NULL;
    bool once = false;
public:

    timer_ch(timer <cnt_type> *n_timer, volatile uint32_t* n_ccr) {
        ccr = n_ccr;
        tim = n_timer;
    }

    cnt_type CapComRead() {
        return *ccr;
    }

    void CapComWrite(cnt_type cap_com) {
        *ccr = cap_com;
    }

    void EventSet(timer_event event_set, bool event_once) {
        event = event_set;
        once = event_once;
    }

    void ITEnable() {
        tim->TIM->SR &= ~status_mask;
        tim->TIM->DIER |= interrupt_mask;
    }

    void ITDisable() {
        tim->TIM->DIER &= ~interrupt_mask;
    }

    void ITHandler() {
        if (tim->TIM->DIER & interrupt_mask) {
            if (tim->TIM->SR & status_mask) {
                tim->TIM->SR &= ~status_mask;
                if (event) event();
                if (once) ITDisable();
            }
        }
    }
};

#endif /* TIMER_EVENT_H */

