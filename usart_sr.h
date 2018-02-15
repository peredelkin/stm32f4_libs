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

typedef uint16_t usart_sr_type;

typedef struct {
    usart_sr_type pe;
    usart_sr_type fe;
    usart_sr_type ne;
    usart_sr_type ore;
    usart_sr_type idle;
    usart_sr_type rxne;
    usart_sr_type tc;
    usart_sr_type txe;
    usart_sr_type lbd;
    usart_sr_type cts;
}usart_sr_t;

#endif /* USART_SR_H */
