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
const uint16_t EGR_Mask> class tim_cc_it_event {
    typedef void (*timer_event)();
private:
    TIM_TypeDef* TIM; //Timer
    __IO uint32_t* CCR; //capture/compare register
    timer_event Event = NULL; //Calling Event
    bool Once_Dier = false; //Reset DIER if True
public:
    //DIER

    uint16_t DIER_Read() {
        return (TIM->DIER & DIER_Mask);
    }

    void DIER_Set() {
        TIM->DIER |= DIER_Mask;
    }

    void DIER_Reset() {
        TIM->DIER &= ~DIER_Mask;
    }
    //SR

    uint16_t SR_Read() {
        return (TIM->SR & SR_Mask);
    }

    void SR_Reset() {
        TIM->SR &= ~SR_Mask;
    }
    //EGR

    void EGR_Set() {
        TIM->EGR = EGR_Mask;
    }
    //CCR

    bit_capacity CCR_Read() {
        return *CCR;
    }

    void CCR_Write(bit_capacity data) {
        *CCR = data;
    }
    //Event

    void Event_Set(timer_event EVENT_Set) {
        Event = EVENT_Set;
    }
    //Handler

    void ITHandler() {
        if (TIM->DIER & DIER_Mask) { //Check IT Enabled
            if (TIM->SR & SR_Mask) { //Check Status
                TIM->SR &= ~SR_Mask; //Reset Status
                if (Event) { //Check Event
                    Event(); //Call Event
                }
                if (Once_Dier) { //Check Once Call Interrupt
                    TIM->DIER &= ~DIER_Mask; //Reset Interrupt
                }
            }
        }
    }

    tim_cc_it_event(TIM_TypeDef* TIM_Set, __IO uint32_t * CCR_Set, timer_event Event_Set, bool Once_Dier_Set) {
        TIM = TIM_Set;
        CCR = CCR_Set;
        Event = Event_Set;
        Once_Dier = Once_Dier_Set;
    }
};

#endif /* TIMER_EVENT_H */

