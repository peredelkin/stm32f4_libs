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
#include "macroses.h"

typedef uint16_t usart_sr_t;
typedef uint16_t usart_dr_t;

typedef struct {
    USART_TypeDef* usart;
} usart_t;

/******************* USART_SR register Functions *******************/
bool usart_sr_read(usart_t* usart,usart_sr_t sr_bit);
void usart_sr_reset(usart_t* usart,usart_sr_t sr_bit);

bool usart_sr_pe_read(usart_t* usart);

bool usart_sr_fe_read(usart_t* usart);

bool usart_sr_ne_read(usart_t* usart);

bool usart_sr_ore_read(usart_t* usart);

bool usart_sr_idle_read(usart_t* usart);

bool usart_sr_rxne_read(usart_t* usart);
void usart_sr_rxne_reset(usart_t* usart);

bool usart_sr_tc_read(usart_t* usart);
void usart_sr_tc_reset(usart_t* usart);

bool usart_sr_txe_read(usart_t* usart);

bool usart_sr_lbd_read(usart_t* usart);
void usart_sr_lbd_reset(usart_t* usart);

bool usart_sr_cts_read(usart_t* usart);
void usart_sr_cts_reset(usart_t* usart);
/*******************  USART_DR register Functions  *******************/

#endif /* USART_H */
