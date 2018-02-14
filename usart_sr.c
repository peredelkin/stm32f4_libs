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

#include "usart_sr.h"

bool usart_sr_pe_read (usart_t* usart) {
    if(CHECK_BIT_BY_MASK(usart->usart->SR,usart->sr_mask->pe)) return 1;
    return 0;
}
bool usart_sr_fe_read (usart_t* usart) {
    if(CHECK_BIT_BY_MASK(usart->usart->SR,usart->sr_mask->fe)) return 1;
    return 0;
}
bool usart_sr_ne_read (usart_t* usart) {
    if(CHECK_BIT_BY_MASK(usart->usart->SR,usart->sr_mask->ne)) return 1;
    return 0;
}
bool usart_sr_ore_read (usart_t* usart) {
    if(CHECK_BIT_BY_MASK(usart->usart->SR,usart->sr_mask->ore)) return 1;
    return 0;
}
bool usart_sr_idle_read (usart_t* usart) {
    if(CHECK_BIT_BY_MASK(usart->usart->SR,usart->sr_mask->idle)) return 1;
    return 0;
}
bool usart_sr_rxne_read (usart_t* usart) {
    if(CHECK_BIT_BY_MASK(usart->usart->SR,usart->sr_mask->rxne)) return 1;
    return 0;
}
bool usart_sr_tc_read (usart_t* usart) {
    if(CHECK_BIT_BY_MASK(usart->usart->SR,usart->sr_mask->tc)) return 1;
    return 0;
}
bool usart_sr_txe_read (usart_t* usart) {
    if(CHECK_BIT_BY_MASK(usart->usart->SR,usart->sr_mask->txe)) return 1;
    return 0;
}
bool usart_sr_lbd_read (usart_t* usart) {
    if(CHECK_BIT_BY_MASK(usart->usart->SR,usart->sr_mask->lbd)) return 1;
    return 0;
}
bool usart_sr_cts_read (usart_t* usart) {
    if(CHECK_BIT_BY_MASK(usart->usart->SR,usart->sr_mask->cts)) return 1;
    return 0;
}
