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
typedef uint16_t usart_brr_t;
typedef uint16_t usart_cr_t;

typedef struct {
    void* data;
    usart_dr_t data_index;
    usart_dr_t data_size;
    usart_dr_t data_max;
} usart_trx_t;

typedef struct {
    usart_trx_t receive;
    usart_trx_t transmit;
    USART_TypeDef* usart;
} usart_t;

/******************* USART_SR register Functions *******************/
extern bool usart_sr_read_bit(usart_t* usart,usart_sr_t sr_bit);
extern void usart_sr_reset_bit(usart_t* usart,usart_sr_t sr_bit);

extern bool usart_sr_pe_read(usart_t* usart);

extern bool usart_sr_fe_read(usart_t* usart);

extern bool usart_sr_ne_read(usart_t* usart);

extern bool usart_sr_ore_read(usart_t* usart);

extern bool usart_sr_idle_read(usart_t* usart);

extern bool usart_sr_rxne_read(usart_t* usart);
extern void usart_sr_rxne_reset(usart_t* usart);

extern bool usart_sr_tc_read(usart_t* usart);
extern void usart_sr_tc_reset(usart_t* usart);

extern bool usart_sr_txe_read(usart_t* usart);

extern bool usart_sr_lbd_read(usart_t* usart);
extern void usart_sr_lbd_reset(usart_t* usart);

extern bool usart_sr_cts_read(usart_t* usart);
extern void usart_sr_cts_reset(usart_t* usart);
/*******************  USART_DR register Functions  *******************/
extern void usart_dr_write(usart_t* usart,void* data,usart_dr_t index);
extern void usart_dr_read(usart_t* usart,void* data,usart_dr_t index);
/******************  USART_BRR register Functions  *******************/
extern void usart_brr_write(usart_t* usart,usart_brr_t mantissa,usart_brr_t fraction);
extern void usart_brr_set(usart_t* usart,uint32_t fpclk,uint32_t baud);
/******************  USART_CR1 register Functions  *******************/
extern bool usart_cr1_read_bit(usart_t* usart,usart_cr_t cr_bit);
extern void usart_cr1_set_bit(usart_t* usart,usart_cr_t cr_bit);
extern void usart_cr1_reset_bit(usart_t* usart,usart_cr_t cr_bit);
extern bool usart_cr1_over8_read(usart_t* usart);
/******************  USART_CR2 register Functions  *******************/
extern bool usart_cr2_read_bit(usart_t* usart,usart_cr_t cr_bit);
extern void usart_cr2_set_bit(usart_t* usart,usart_cr_t cr_bit);
extern void usart_cr2_reset_bit(usart_t* usart,usart_cr_t cr_bit);
/******************  USART_CR3 register Functions  *******************/
extern bool usart_cr3_read_bit(usart_t* usart,usart_cr_t cr_bit);
extern void usart_cr3_set_bit(usart_t* usart,usart_cr_t cr_bit);
extern void usart_cr3_reset_bit(usart_t* usart,usart_cr_t cr_bit);
/******************  USART_GTPR register Functions ******************/
extern void usart_gtpr_write(usart_t* usart,usart_brr_t guard_time,usart_brr_t prescaler);
/******************  USART_STD_INIT ******************/
extern void usart_standard_init(usart_t* usart);
#endif /* USART_H */
