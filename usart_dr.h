/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   usart_dr.h
 * Author: ruslan
 *
 * Created on 15 февраля 2018 г., 10:50
 */

#ifndef USART_DR_H
#define USART_DR_H

#include <stm32f4xx.h>

typedef uint16_t usart_dr_type;

typedef struct {
    const usart_dr_type dr_mask;
    usart_dr_type* txd;
    usart_dr_type* rxd;
    usart_dr_type txd_index;
    usart_dr_type txd_size;
    usart_dr_type txd_index_max;
    usart_dr_type rxd_index;
    usart_dr_type rxd_size;
    usart_dr_type rxd_index_max;
}usart_dr_t;

#endif /* USART_DR_H */
