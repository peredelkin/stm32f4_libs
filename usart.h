/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   usart.h
 * Author: ruslan
 *
 * Created on 14 февраля 2018 г., 10:23
 */

#ifndef USART_H
#define USART_H

#include <stm32f4xx.h>
#include <stdbool.h>
#include <macroses.h>
#include <usart_sr.h>

typedef struct {
    const usart_sr_mask_t* sr_mask;
    USART_TypeDef* usart;
}usart_t;

#endif /* USART_H */
