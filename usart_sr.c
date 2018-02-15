/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   usart_sr.c
 * Author: ruslan
 * 
 * Created on 14 февраля 2018 г., 14:50
 */

#include <usart_sr.h>
#include <usart.h>

bool usart_sr_read (usart_t* usart,usart_sr_type sr_mask) {
    if(CHECK_BIT_BY_MASK(usart->usart->SR,sr_mask)) return 1;
    return 0;
}
/**
 * 
 * @param usart
 * @return : Parity error
 */
bool usart_sr_pe_read (usart_t* usart) {
    return usart_sr_read(usart,usart->sr_mask->pe);
}
/**
 * 
 * @param usart
 * @return : Framing error
 */
bool usart_sr_fe_read (usart_t* usart) {
    return usart_sr_read(usart,usart->sr_mask->fe);
}
/**
 * 
 * @param usart
 * @return : Noise detected flag
 */
bool usart_sr_ne_read (usart_t* usart) {
    return usart_sr_read(usart,usart->sr_mask->ne);
}
/**
 * 
 * @param usart
 * @return : Overrun error
 */
bool usart_sr_ore_read (usart_t* usart) {
    return usart_sr_read(usart,usart->sr_mask->ore);
}
/**
 * 
 * @param usart
 * @return : IDLE line detected
 */
bool usart_sr_idle_read (usart_t* usart) {
    return usart_sr_read(usart,usart->sr_mask->idle);
}
/**
 * 
 * @param usart
 * @return : Read data register not empty
 */
bool usart_sr_rxne_read (usart_t* usart) {
    return usart_sr_read(usart,usart->sr_mask->rxne);
}
/**
 * 
 * @param usart
 * @return : Transmission complete
 */
bool usart_sr_tc_read (usart_t* usart) {
    return usart_sr_read(usart,usart->sr_mask->tc);
}
/**
 * 
 * @param usart
 * @return : Transmit data register empty
 */
bool usart_sr_txe_read (usart_t* usart) {
    return usart_sr_read(usart,usart->sr_mask->txe);
}
/**
 * 
 * @param usart
 * @return : LIN break detection flag
 */
bool usart_sr_lbd_read (usart_t* usart) {
    return usart_sr_read(usart,usart->sr_mask->lbd);
}
/**
 * 
 * @param usart
 * @return : CTS flag
 */
bool usart_sr_cts_read (usart_t* usart) {
    return usart_sr_read(usart,usart->sr_mask->cts);
}

void usart_sr_rst(usart_t* usart,usart_sr_type sr_mask) {
    RESET_BIT(usart->usart->SR,sr_mask);
}

void usart_sr_rxne_rst (usart_t* usart) {
    usart_sr_rst(usart,usart->sr_mask->rxne);
}

void usart_sr_tc_rst (usart_t* usart) {
    usart_sr_rst(usart,usart->sr_mask->tc);
}

void usart_sr_lbd_rst (usart_t* usart) {
    usart_sr_rst(usart,usart->sr_mask->lbd);
}

void usart_sr_cts_rst (usart_t* usart) {
    usart_sr_rst(usart,usart->sr_mask->cts);
}