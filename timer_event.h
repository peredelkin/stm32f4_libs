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

template <typename bit_capacity, const uint16_t DIER_Mask, const uint16_t SR_Mask,
const uint16_t EGR_Mask> class timer_capture_compare_interrupt_event {
    typedef void (*timer_event)();
private:
    TIM_TypeDef* TIM; //Timer
    __IO uint32_t* CCR; //capture/compare register
    timer_event Event = NULL; //Calling Event
public:
    bool Execute_Once = false; //Reset DIER if True
    //DIER

    uint16_t Interrupt_Status() {
        return (TIM->DIER & DIER_Mask);
    }

    void Interrupt_Enable() {
        TIM->SR &= ~SR_Mask; //Reset Before Enable
        TIM->DIER |= DIER_Mask;
    }

    void Interrupt_Disable() {
        TIM->DIER &= ~DIER_Mask;
    }
    //SR

    uint16_t Status_Read() {
        return (TIM->SR & SR_Mask);
    }

    void Status_Reset() {
        TIM->SR &= ~SR_Mask;
    }
    //EGR

    void Event_Generate() {
        TIM->EGR = EGR_Mask;
    }
    //CCR

    bit_capacity Capture_Compare_Read() {
        return (bit_capacity)*CCR;
    }

    void Capture_Compare_Write(bit_capacity data) {
        *CCR = (bit_capacity) data;
    }
    //Event

    void Event_Set(timer_event EVENT_Set) {
        Event = EVENT_Set;
    }
    //Handler

    void Interrupt_Handler() {
        if (Interrupt_Status()) {
            if (Status_Read()) {
                Status_Reset();
                if (Event) {
                    Event();
                }
                if (Execute_Once) {
                    Interrupt_Disable();
                }
            }
        }
    }

    timer_capture_compare_interrupt_event(TIM_TypeDef* TIM_Set, __IO uint32_t * CCR_Set, timer_event Event_Set, bool Once_Dier_Set) {
        TIM = TIM_Set;
        CCR = CCR_Set;
        Event = Event_Set;
        Execute_Once = Once_Dier_Set;
    }
};

#endif /* TIMER_EVENT_H */

