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
extern bool usart_status_register_read_bit(usart_t* usart,usart_sr_t sr_bit);
extern void usart_status_register_reset_bit(usart_t* usart,usart_sr_t sr_bit);

extern bool usart_status_error_parity_stat(usart_t* usart);

extern bool usart_status_error_framing_stat(usart_t* usart);

extern bool usart_status_noise_error_stat(usart_t* usart);

extern bool usart_status_overrun_error_stat(usart_t* usart);

extern bool usart_status_idle_line_stat(usart_t* usart);

extern bool usart_status_rx_not_empty_stat(usart_t* usart);
extern void usart_status_rx_not_empty_clr(usart_t* usart);

extern bool usart_status_tx_complete_stat(usart_t* usart);
extern void usart_status_tx_complete_clr(usart_t* usart);

extern bool usart_status_tx_empty_stat(usart_t* usart);

extern bool usart_status_lin_break_stat(usart_t* usart);
extern void usart_status_lin_break_clr(usart_t* usart);

extern bool usart_status_clear_to_send_stat(usart_t* usart);
extern void usart_status_clear_to_send_clr(usart_t* usart);
/*******************  USART_DR register Functions  *******************/
extern void usart_data_write(usart_t* usart,void* data,usart_dr_t index);
extern void usart_send_poll(usart_t* usart);
extern void usart_data_read(usart_t* usart,void* data,usart_dr_t index);
/******************  USART_BRR register Functions  *******************/
extern void usart_baud_rate_register_write(usart_t* usart,usart_brr_t mantissa,usart_brr_t fraction);
extern void usart_baud_rate_set(usart_t* usart,uint32_t fpclk,uint32_t baud);
/******************  USART_CR1 register Functions  *******************/
extern bool usart_control_register_1_read_bit(usart_t* usart,usart_cr_t cr_bit);
extern void usart_control_register_1_set_bit(usart_t* usart,usart_cr_t cr_bit);
extern void usart_control_register_1_reset_bit(usart_t* usart,usart_cr_t cr_bit);

extern bool usart_ctrl_oversamp8_stat(usart_t* usart);
extern void usart_ctrl_oversamp8_ena(usart_t* usart);
extern void usart_ctrl_oversamp8_dis(usart_t* usart);

extern bool usart_ctrl_usart_stat(usart_t* usart);
extern void usart_ctrl_usart_ena(usart_t* usart);
extern void usart_ctrl_usart_dis(usart_t* usart);

extern bool usart_ctrl_9bit_stat(usart_t* usart);
extern void usart_ctrl_9bit_ena(usart_t* usart);
extern void usart_ctrl_9bit_dis(usart_t* usart);

extern bool usart_ctrl_wake_stat(usart_t* usart);
extern void usart_ctrl_wake_ena(usart_t* usart);
extern void usart_wake_dis(usart_t* usart);

extern bool usart_ctrl_parity_stat(usart_t* usart);
extern void usart_ctrl_parity_ena(usart_t* usart);
extern void usart_ctrl_parity_dis(usart_t* usart);

extern bool usart_ctrl_odd_stat(usart_t* usart);
extern void usart_ctrl_odd_ena(usart_t* usart);
extern void usart_ctrl_odd_dis(usart_t* usart);

extern bool usart_ctrl_interrupt_parity_error_stat(usart_t* usart);
extern void usart_ctrl_interrupt_parity_error_ena(usart_t* usart);
extern void usart_ctrl_interrupt_parity_error_dis(usart_t* usart);

extern bool usart_ctrl_interrupt_tx_empty_stat(usart_t* usart);
extern void usart_ctrl_interrupt_tx_empty_ena(usart_t* usart);
extern void usart_ctrl_interrupt_tx_empty_dis(usart_t* usart);

extern bool usart_ctrl_interrupt_tx_complete_stat(usart_t* usart);
extern void usart_ctrl_interrupt_tx_complete_ena(usart_t* usart);
extern void usart_ctrl_interrupt_tx_complete_dis(usart_t* usart);

extern bool usart_ctrl_interrupt_rx_not_empty_stat(usart_t* usart);
extern void usart_ctrl_interrupt_rx_not_empty_ena(usart_t* usart);
extern void usart_ctrl_interrupt_rx_not_empty_dis(usart_t* usart);

extern bool usart_ctrl_interrupt_idle_line_stat(usart_t* usart);
extern void usart_ctrl_interrupt_idle_line_ena(usart_t* usart);
extern void usart_ctrl_interrupt_idle_line_dis(usart_t* usart);

extern bool usart_ctrl_tx_stat(usart_t* usart);
extern void usart_ctrl_tx_ena(usart_t* usart);
extern void usart_ctrl_tx_dis(usart_t* usart);

extern bool usart_ctrl_rx_stat(usart_t* usart);
extern void usart_ctrl_rx_ena(usart_t* usart);
extern void usart_ctrl_rx_dis(usart_t* usart);

extern bool usart_ctrl_rx_wakeup_mute_stat(usart_t* usart);
extern void usart_ctrl_rx_wakeup_mute_ena(usart_t* usart);
extern void usart_ctrl_rx_wakeup_mute_dis(usart_t* usart);

extern bool usart_ctrl_send_break_stat(usart_t* usart);
extern void usart_ctrl_send_break_ena(usart_t* usart);
extern void usart_ctrl_send_break_dis(usart_t* usart);
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
extern void usart_std_init(usart_t* usart);
#endif /* USART_H */
