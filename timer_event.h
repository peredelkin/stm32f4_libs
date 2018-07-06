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

#include "timer.h"

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

    void _Event_Handler() {
        if (once) {
            IT_Disable();
        }
        if (event) event();
    }
public:

    uint16_t CapCom_Read() {
        return (tim->*ccr_read_method)();
    }

    void CapCom_Write(uint16_t ccr_data) {
        (tim->*ccr_write_method)(ccr_data);
    }

    void IT_Enable() {
        tim->SR_Reset(status_mask);
        tim->DIER_Set(interrupt_mask);
    }

    void IT_Disable() {
        tim->DIER_Reset(interrupt_mask);
    }

    void IT_Handler() {
        if (tim->SR_Read(status_mask)) {
            tim->SR_Reset(status_mask);
            if (tim->DIER_Read(interrupt_mask)) {
                _Event_Handler();
            }
        }
    }

    void Event_Set(timer_event event_set, bool once_set) {
        event = event_set;
        once = once_set;
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

