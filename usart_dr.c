/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   usart_dr.c
 * Author: ruslan
 * 
 * Created on 15 февраля 2018 г., 10:50
 */

#include <usart_dr.h>
#include <usart.h>

void usart_read_dr(usart_t* usart,usart_dr_type *data) {
    READ_REG_BY_MASK(usart->usart->DR,usart->trxd->trx_mask,*data);
}
void usart_write_dr(usart_t* usart,usart_dr_type *data) {
    WRITE_REG_BY_MASK(usart->usart->DR,usart->trxd->trx_mask,*data);
}

/**
 * 
 * @param usart
 * @return: End of txd
 */
bool usart_tx_data(usart_t* usart) {
    usart_write_dr(usart,&usart->trxd->txd[usart->trxd->txd_index]);
    if(usart->trxd->txd_index == usart->trxd->txd_index_max ||
            usart->trxd->txd_index == usart->trxd->txd_size) return 1;
    usart->trxd->txd_index++;
    return 0;
}

/**
 * 
 * @param usart
 * @return: End of rxd 
 */
bool usart_rx_data(usart_t* usart) {
    usart_read_dr(usart,&usart->trxd->rxd[usart->trxd->rxd_index]);
    if(usart->trxd->rxd_index == usart->trxd->rxd_index_max ||
            usart->trxd->rxd_index == usart->trxd->rxd_size) return 1;
    usart->trxd->rxd_index++;
    return 0;
}