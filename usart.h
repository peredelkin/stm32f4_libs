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
#include <string.h>
#include "macroses.h"

typedef uint16_t usart_sr_t;
typedef uint16_t usart_dr_t;
typedef uint16_t usart_brr_t;
typedef uint16_t usart_cr_t;

typedef struct {
    void* data;
    usart_dr_t data_index;
    usart_dr_t data_size;
    usart_dr_t index_max;
} usart_trx_t;

typedef struct {
    usart_trx_t receive;
    usart_trx_t transmit;
    USART_TypeDef* usart;
} usart_t;

/******************* USART_SR register Functions *******************/
extern bool usart_status_register_bit_read(usart_t* usart,usart_sr_t sr_bit);
extern void usart_status_register_bit_clr(usart_t* usart,usart_sr_t sr_bit);
/*******************  USART_DR register Functions  *******************/
extern void usart_data_write(usart_t* usart,void* data,usart_dr_t index);
extern void usart_data_read(usart_t* usart,void* data,usart_dr_t index);
/******************  USART_BRR register Functions  *******************/
extern void usart_baud_rate_register_write(usart_t* usart,usart_brr_t mantissa,usart_brr_t fraction);
/******************  USART_CR1 register Functions  *******************/
extern bool usart_control_register_1_bit_read(usart_t* usart,usart_cr_t cr_bit);
extern void usart_control_register_1_bit_set(usart_t* usart,usart_cr_t cr_bit);
extern void usart_control_register_1_bit_clr(usart_t* usart,usart_cr_t cr_bit);
/******************  USART_CR2 register Functions  *******************/
extern bool usart_control_register_2_bit_read(usart_t* usart,usart_cr_t cr_bit);
extern void usart_control_register_2_bit_set(usart_t* usart,usart_cr_t cr_bit);
extern void usart_control_register_2_bit_clr(usart_t* usart,usart_cr_t cr_bit);
/******************  USART_CR3 register Functions  *******************/
extern bool usart_control_register_3_bit_read(usart_t* usart,usart_cr_t cr_bit);
extern void usart_control_register_3_bit_set(usart_t* usart,usart_cr_t cr_bit);
extern void usart_control_register_3_bit_clr(usart_t* usart,usart_cr_t cr_bit);
/******************  USART_GTPR register Functions ******************/
extern void usart_gtpr_write(usart_t* usart,usart_brr_t guard_time,usart_brr_t prescaler);
/******************  MAIN FUNCTIONS ******************/
extern void usart_baud_rate_set(usart_t* usart,uint32_t fpclk,uint32_t baud);
extern void usart_std_init(usart_t* usart);
extern void usart_send_poll(usart_t* usart);
#endif /* USART_H */
