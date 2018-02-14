/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   usart_sr.h
 * Author: ruslan
 *
 * Created on 14 февраля 2018 г., 14:50
 */

#ifndef USART_SR_H
#define USART_SR_H

#include <stm32f4xx.h>
#include <stdbool.h>
#include <macroses.h>
#include <usart.h>

#define MAKE_USART_SR_MASK {\
    .pe = USART_SR_PE,\
    .fe = USART_SR_FE,\
    .ne = USART_SR_NE,\
    .ore = USART_SR_ORE,\
    .idle = USART_SR_IDLE,\
    .rxne = USART_SR_RXNE,\
    .tc = USART_SR_TC,\
    .txe = USART_SR_TXE,\
    .lbd = USART_SR_LBD,\
    .cts = USART_SR_CTS\
}

typedef uint16_t usart_sr_mask_type;

typedef struct {
    usart_sr_mask_type pe;
    usart_sr_mask_type fe;
    usart_sr_mask_type ne;
    usart_sr_mask_type ore;
    usart_sr_mask_type idle;
    usart_sr_mask_type rxne;
    usart_sr_mask_type tc;
    usart_sr_mask_type txe;
    usart_sr_mask_type lbd;
    usart_sr_mask_type cts;
}usart_sr_mask_t;

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

#endif /* USART_SR_H */
