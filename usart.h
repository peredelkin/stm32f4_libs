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
#include <usart_dr.h>

typedef struct {
    usart_dr_t* trxd;
    const usart_sr_t* sr_mask;
    USART_TypeDef* usart;
}usart_t;

/*--------------------USART Status Register Reead---------------------*/
extern bool usart_sr_read (usart_t* usart,usart_sr_type sr_mask);
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
/*--------------------USART Status Register Reset---------------------*/
extern void usart_sr_rst(usart_t* usart,usart_sr_type sr_mask);
extern void usart_sr_rxne_rst (usart_t* usart);
extern void usart_sr_tc_rst (usart_t* usart);
extern void usart_sr_lbd_rst (usart_t* usart);
extern void usart_sr_cts_rst (usart_t* usart);
/*-------------------USART TRX Data Register--------------------------*/
void usart_read_dr(usart_t* usart,usart_dr_type *data);
void usart_write_dr(usart_t* usart,usart_dr_type *data);
bool usart_tx_data(usart_t* usart);
bool usart_rx_data(usart_t* usart);

#endif /* USART_H */
