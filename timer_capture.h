/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   timer_capture.h
 * Author: ruslan
 *
 * Created on 3 июля 2018 г., 10:42
 */

#ifndef TIMER_CAPTURE_H
#define TIMER_CAPTURE_H

#include "timer_event.h"

template <typename bit_capacity,bit_capacity capture_max,
        const uint16_t DIER_Mask, const uint16_t SR_Mask,
        const uint16_t EGR_Mask> class timer_capture {
private:
    timer_capture_compare_interrupt_event
            <bit_capacity,DIER_Mask,SR_Mask,EGR_Mask> *timer_cap_com;
public:
    bit_capacity previous_value = 0;
    bit_capacity present_value = 0;
    bit_capacity actual_value = 0;
    
    void Handler() {
        previous_value = present_value;
        present_value = timer_cap_com->Capture_Compare_Read();
        actual_value = capture_max + 1 + present_value - previous_value;
    }
    timer_capture(timer_capture_compare_interrupt_event
    <bit_capacity,DIER_Mask,SR_Mask,EGR_Mask> *timer_cap_com_set) {
        timer_cap_com = timer_cap_com_set;
    }
};

#endif /* TIMER_CAPTURE_H */

