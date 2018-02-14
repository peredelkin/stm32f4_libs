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

extern bool usart_sr_pe_read (usart_t* usart);
extern bool usart_sr_fe_read (usart_t* usart);
extern bool usart_sr_ne_read (usart_t* usart);
extern bool usart_sr_ore_read (usart_t* usart);
extern bool usart_sr_idle_read (usart_t* usart);
extern bool usart_sr_rxne_read (usart_t* usart);
extern bool usart_sr_tc_read (usart_t* usart);
extern bool usart_sr_txe_read (usart_t* usart);
extern bool usart_sr_lbd_read (usart_t* usart);
extern bool usart_sr_cts_read (usart_t* usart);

#endif /* USART_H */
