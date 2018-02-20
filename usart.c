/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   usart.c
 * Author: ruslan
 * 
 * Created on 14 февраля 2018 г., 10:23
 */

#include "usart.h"
/**
 * Read USART Status Register
 * @param usart: USART
 * @param sr_bit: Status Bit
 * @return: Value Of Status Bit 
 */
bool usart_sr_read_bit(usart_t* usart,usart_sr_t sr_bit) {
    if(CHECK_BIT_BY_MASK(usart->usart->SR,sr_bit)) return 1;
    return 0;
}
void usart_sr_reset_bit(usart_t* usart,usart_sr_t sr_bit) {
    RESET_BIT(usart->usart->SR,sr_bit);
}
/**
 * Read Parity Error Flag
 * @param usart: USART
 * @return: Parity Error
 */
bool usart_pe_stat_read(usart_t* usart) {
    return usart_sr_read_bit(usart,USART_SR_PE);
}
/**
 * Read Framing Error Flag
 * @param: usart
 * @return: Framing Error
 */
bool usart_fe_stat_read(usart_t* usart) {
    return usart_sr_read_bit(usart,USART_SR_FE);
}
/**
 * Read Noise Error Flag
 * @param: usart
 * @return: Noise Error Flag
 */
bool usart_ne_stat_read(usart_t* usart) {
    return usart_sr_read_bit(usart,USART_SR_NE);
}
/**
 * Read OverRun Error Flag
 * @param usart: USART
 * @return: OverRun Error 
 */
bool usart_ore_stat_read(usart_t* usart) {
    return usart_sr_read_bit(usart,USART_SR_ORE);
}
/**
 * Read IDLE line detected
 * @param usart: USART
 * @return: IDLE line detected
 */
bool usart_idle_stat_read(usart_t* usart) {
    return usart_sr_read_bit(usart,USART_SR_IDLE);
}
/**
 * Read Data Register Not Empty
 * @param usart: USART
 * @return: Read Data Register Not Empty 
 */
bool usart_rxne_stat_read(usart_t* usart) {
    return usart_sr_read_bit(usart,USART_SR_RXNE);
}
void usart_rxne_stat_reset(usart_t* usart) {
    usart_sr_reset_bit(usart,USART_SR_RXNE);
}
/**
 * Read Transmission Complete
 * @param usart: USART
 * @return: Transmission Complete 
 */
bool usart_tc_stat_read(usart_t* usart) {
    return usart_sr_read_bit(usart,USART_SR_TC);
}
void usart_tc_stat_reset(usart_t* usart) {
    return usart_sr_reset_bit(usart,USART_SR_TC);
}
/**
 * Read Transmit Data Register Empty
 * @param usart: USART
 * @return: Transmit Data Register Empty 
 */
bool usart_txe_stat_read(usart_t* usart) {
    return usart_sr_read_bit(usart,USART_SR_TXE);
}
/**
 * Read LIN Break Detection Flag
 * @param usart: USART
 * @return: LIN Break Detection Flag
 */
bool usart_lbd_stat_read(usart_t* usart) {
    return usart_sr_read_bit(usart,USART_SR_LBD);
}
void usart_lbd_stat_reset(usart_t* usart) {
    usart_sr_reset_bit(usart,USART_SR_LBD);
}
/**
 * Read CTS Flag
 * @param usart: USART
 * @return: CTS Flag
 */
bool usart_cts_stat_read(usart_t* usart) {
    return usart_sr_read_bit(usart,USART_SR_CTS);
}
void usart_cts_stat_reset(usart_t* usart) {
    usart_sr_reset_bit(usart,USART_SR_CTS);
}
/**
 * Wrtite "data" by "index" into USART Data Register
 * @param usart: USART
 * @param data: Data to write
 * @param index: Data Index
 */
void usart_data_write(usart_t* usart,void* data,usart_dr_t index) {
     usart->usart->DR = ((uint16_t)((uint8_t*)data)[index] & USART_DR_DR);
}
/**
 * Read from USART Data Register into "data" by "index"
 * @param usart: USART
 * @param data: Data to read
 * @param index: Data index
 */
void usart_data_read(usart_t* usart,void* data,usart_dr_t index) {
    ((uint8_t*)data)[index] = (uint8_t)(usart->usart->DR & USART_DR_DR);
}
/**
 * Write "mantissa" and "fraction" to  Baud rate register
 * @param usart: USART
 * @param mantissa
 * @param fraction
 */
void usart_brr_write(usart_t* usart,usart_brr_t mantissa,usart_brr_t fraction) {
    usart->usart->BRR = ((uint16_t)(mantissa << 4) & USART_BRR_DIV_Mantissa) |
            ((uint16_t)fraction & USART_BRR_DIV_Fraction);
}
/**
 * Configures BaudRateRegister by Bus Freq and baudrate
 * @param usart: USART
 * @param fpclk: Bus Freq in Hz
 * @param baud: BaudRate in Bps
 */
void usart_baud_rate_set(usart_t* usart,uint32_t fpclk,uint32_t baud) {
    uint32_t over8 = (uint32_t)usart_over8_read(usart);
    uint32_t mantissa = (fpclk/((8*(2-over8))*baud));
    uint16_t divider = (uint16_t)(fpclk/baud);
    uint16_t fraction = (uint16_t)(divider - (uint16_t)(mantissa << 4));
    if(over8) {
        usart_brr_write(usart,mantissa,(fraction & (uint16_t)0x07));
    } else {
        usart_brr_write(usart,mantissa,fraction);
    }
}
/**
 * Read bit of ControlRegister1
 * @param usart: USART
 * @param cr_bit: CR1 bit mask
 * @return: State of rc_bit
 */
bool usart_cr1_read_bit(usart_t* usart,usart_cr_t cr_bit) {
    if(CHECK_BIT_BY_MASK(usart->usart->CR1,cr_bit)) return 1;
    return 0;
}
bool usart_cr2_read_bit(usart_t* usart,usart_cr_t cr_bit) {
    if(CHECK_BIT_BY_MASK(usart->usart->CR2,cr_bit)) return 1;
    return 0;
}
bool usart_cr3_read_bit(usart_t* usart,usart_cr_t cr_bit) {
    if(CHECK_BIT_BY_MASK(usart->usart->CR3,cr_bit)) return 1;
    return 0;
}
/**
 * Set bit of ControlRegister1
 * @param usart: USART
 * @param cr_bit: CR1 bit mask
 */
void usart_cr1_set_bit(usart_t* usart,usart_cr_t cr_bit) {
    SET_BIT(usart->usart->CR1,cr_bit);
}
void usart_cr2_set_bit(usart_t* usart,usart_cr_t cr_bit) {
    SET_BIT(usart->usart->CR2,cr_bit);
}
void usart_cr3_set_bit(usart_t* usart,usart_cr_t cr_bit) {
    SET_BIT(usart->usart->CR3,cr_bit);
}
/**
 * Reset bit of ControlRegister1
 * @param usart: USART
 * @param cr_bit: CR1 bit mask
 */
void usart_cr1_reset_bit(usart_t* usart,usart_cr_t cr_bit) {
    RESET_BIT(usart->usart->CR1,cr_bit);
}
void usart_cr2_reset_bit(usart_t* usart,usart_cr_t cr_bit) {
    RESET_BIT(usart->usart->CR2,cr_bit);
}
void usart_cr3_reset_bit(usart_t* usart,usart_cr_t cr_bit) {
    RESET_BIT(usart->usart->CR3,cr_bit);
}
/**
 * Read state "oversampling by 8"
 * @param usart: USART
 * @return: 1 if "oversampling by 8" ,else return 0 - "oversampling by 16" 
 */
bool usart_over8_read(usart_t* usart) {
    return usart_cr1_read_bit(usart,USART_CR1_OVER8);
}
/*************NEW**************/
void usart_over8_set(usart_t* usart) {
    usart_cr1_set_bit(usart,USART_CR1_OVER8);
}
void usart_over8_reset(usart_t* usart) {
    usart_cr1_reset_bit(usart,USART_CR1_OVER8);
}

bool usart_rwu_read(usart_t* usart) {
    return usart_cr1_read_bit(usart,USART_CR1_RWU);
}
void usart_rwu_set(usart_t* usart) {
    usart_cr1_set_bit(usart,USART_CR1_RWU);
}
void usart_rwu_reset(usart_t* usart) {
    usart_cr1_reset_bit(usart,USART_CR1_RWU);
}

bool usart_sbk_read(usart_t* usart) {
    return usart_cr1_read_bit(usart,USART_CR1_SBK);
}
void usart_sbk_set(usart_t* usart) {
    usart_cr1_set_bit(usart,USART_CR1_SBK);
}
void usart_skb_reset(usart_t* usart) {
    usart_cr1_reset_bit(usart,USART_CR1_SBK);
}
/*************END NEW**********/

/**
 * Write Guard time and prescaler register
 * @param usart
 * @param guard_time
 * @param prescaler
 */
void usart_gtpr_write(usart_t* usart,usart_brr_t guard_time,usart_brr_t prescaler) {
    usart->usart->BRR = ((uint16_t)guard_time & USART_GTPR_GT) |
            ((uint16_t)prescaler & USART_GTPR_PSC);
}
/**
 * Initial BaudRate 9600,Enable TX,RX and USART
 * @param usart: USART
 */
void usart_std_init(usart_t* usart) {
    usart_baud_rate_set(usart,SystemCoreClock/2,9600);
    usart_cr1_set_bit(usart,USART_CR1_TE); //TX Enable
    usart_cr1_set_bit(usart,USART_CR1_RE); //RX Enable
    usart_cr1_set_bit(usart,USART_CR1_UE); //USART Enable
}
/**
 * Software send usart.transmit.data by usart.transmit.data_index
 * @param usart
 */
void usart_send_poll(usart_t* usart) {
    usart->transmit.data_index = 0;
    usart->transmit.data_size = (uint16_t)strnlen((const char*)usart->transmit.data,usart->transmit.index_max);
    while(usart->transmit.data_index!=usart->transmit.data_size) {
        while(!usart_txe_stat_read(usart));
        usart_data_write(usart,usart->transmit.data,usart->transmit.data_index);
        usart->transmit.data_index++;
    }
}