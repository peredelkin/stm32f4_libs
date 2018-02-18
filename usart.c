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
/**
 * Reset USART Status Register
 * @param usart: USART
 * @param sr_bit: Status Bit
 */
void usart_sr_reset_bit(usart_t* usart,usart_sr_t sr_bit) {
    RESET_BIT(usart->usart->SR,sr_bit);
}
/**
 * Read Parity Error Flag
 * @param usart: USART
 * @return: Parity Error
 */
bool usart_sr_pe_read(usart_t* usart) {
    return usart_sr_read_bit(usart,USART_SR_PE);
}
/**
 * Read Framing Error Flag
 * @param: usart
 * @return: Framing Error
 */
bool usart_sr_fe_read(usart_t* usart) {
    return usart_sr_read_bit(usart,USART_SR_FE);
}
/**
 * Read Noise Error Flag
 * @param: usart
 * @return: Noise Error Flag
 */
bool usart_sr_ne_read(usart_t* usart) {
    return usart_sr_read_bit(usart,USART_SR_NE);
}
/**
 * Read OverRun Error Flag
 * @param usart: USART
 * @return: OverRun Error 
 */
bool usart_sr_ore_read(usart_t* usart) {
    return usart_sr_read_bit(usart,USART_SR_ORE);
}
/**
 * Read IDLE line detected
 * @param usart: USART
 * @return: IDLE line detected
 */
bool usart_sr_idle_read(usart_t* usart) {
    return usart_sr_read_bit(usart,USART_SR_IDLE);
}
/**
 * Read Data Register Not Empty
 * @param usart: USART
 * @return: Read Data Register Not Empty 
 */
bool usart_sr_rxne_read(usart_t* usart) {
    return usart_sr_read_bit(usart,USART_SR_RXNE);
}
/**
 * Reset Data Register Not Empty
 * @param usart: USART
 */
void usart_sr_rxne_reset(usart_t* usart) {
    usart_sr_reset_bit(usart,USART_SR_RXNE);
}
/**
 * Read Transmission Complete
 * @param usart: USART
 * @return: Transmission Complete 
 */
bool usart_sr_tc_read(usart_t* usart) {
    return usart_sr_read_bit(usart,USART_SR_TC);
}
/**
 * Reset Transmission Complete
 * @param usart: USART
 */
void usart_sr_tc_reset(usart_t* usart) {
    return usart_sr_reset_bit(usart,USART_SR_TC);
}
/**
 * Read Transmit Data Register Empty
 * @param usart: USART
 * @return: Transmit Data Register Empty 
 */
bool usart_sr_txe_read(usart_t* usart) {
    return usart_sr_read_bit(usart,USART_SR_TXE);
}
/**
 * Read LIN Break Detection Flag
 * @param usart: USART
 * @return: LIN Break Detection Flag
 */
bool usart_sr_lbd_read(usart_t* usart) {
    return usart_sr_read_bit(usart,USART_SR_LBD);
}
/**
 * Reset LIN Break Detection Flag
 * @param usart: USART
 */
void usart_sr_lbd_reset(usart_t* usart) {
    usart_sr_reset_bit(usart,USART_SR_LBD);
}
/**
 * Read CTS Flag
 * @param usart: USART
 * @return: CTS Flag
 */
bool usart_sr_cts_read(usart_t* usart) {
    return usart_sr_read_bit(usart,USART_SR_CTS);
}
/**
 * Reset CTS Flag
 * @param usart: USART
 */
void usart_sr_cts_reset(usart_t* usart) {
    usart_sr_reset_bit(usart,USART_SR_CTS);
}
/**
 * Wrtite "data" by "index" into USART Data Register
 * @param usart: USART
 * @param data: Data
 * @param index: Data Index
 */
void usart_dr_write(usart_t* usart,void* data,usart_dr_t index) {
     usart->usart->DR = ((uint16_t)((uint8_t*)data)[index] & USART_DR_DR);
}
/**
 * Read from USART Data Register into "data" by "index"
 * @param usart: USART
 * @param data: Data
 * @param index: Data index
 */
void usart_dr_read(usart_t* usart,void* data,usart_dr_t index) {
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

void usart_brr_set(usart_t* usart,uint32_t fpclk,uint32_t baud) {
    uint32_t over8 = (uint32_t)usart_cr1_over8_read(usart);
    uint32_t mantissa = (fpclk/((8*(2-over8))*baud));
    uint16_t divider = (uint16_t)(fpclk/baud);
    uint16_t fraction = (uint16_t)(divider - (uint16_t)(mantissa << 4));
    if(over8) {
        usart_brr_write(usart,mantissa,(fraction & (uint16_t)0x07));
    } else {
        usart_brr_write(usart,mantissa,fraction);
    }
}

bool usart_cr1_read_bit(usart_t* usart,usart_cr_t cr_bit) {
    if(CHECK_BIT_BY_MASK(usart->usart->CR1,cr_bit)) return 1;
    return 0;
}
void usart_cr1_set_bit(usart_t* usart,usart_cr_t cr_bit) {
    SET_BIT(usart->usart->CR1,cr_bit);
}
void usart_cr1_reset_bit(usart_t* usart,usart_cr_t cr_bit) {
    RESET_BIT(usart->usart->CR1,cr_bit);
}
bool usart_cr1_over8_read(usart_t* usart) {
    return usart_cr1_read_bit(usart,USART_CR1_OVER8);
}

bool usart_cr2_read_bit(usart_t* usart,usart_cr_t cr_bit) {
    if(CHECK_BIT_BY_MASK(usart->usart->CR2,cr_bit)) return 1;
    return 0;
}
void usart_cr2_set_bit(usart_t* usart,usart_cr_t cr_bit) {
    SET_BIT(usart->usart->CR2,cr_bit);
}
void usart_cr2_reset_bit(usart_t* usart,usart_cr_t cr_bit) {
    RESET_BIT(usart->usart->CR2,cr_bit);
}

bool usart_cr3_read_bit(usart_t* usart,usart_cr_t cr_bit) {
    if(CHECK_BIT_BY_MASK(usart->usart->CR3,cr_bit)) return 1;
    return 0;
}
void usart_cr3_set_bit(usart_t* usart,usart_cr_t cr_bit) {
    SET_BIT(usart->usart->CR3,cr_bit);
}
void usart_cr3_reset_bit(usart_t* usart,usart_cr_t cr_bit) {
    RESET_BIT(usart->usart->CR3,cr_bit);
}

void usart_gtpr_write(usart_t* usart,usart_brr_t guard_time,usart_brr_t prescaler) {
    usart->usart->BRR = ((uint16_t)guard_time & USART_GTPR_GT) |
            ((uint16_t)prescaler & USART_GTPR_PSC);
}

void usart_standard_init(usart_t* usart) {
    usart_brr_set(usart,SystemCoreClock/2,9600);
    usart_cr1_set_bit(usart,USART_CR1_TE); //TX Enable
    usart_cr1_set_bit(usart,USART_CR1_RE); //RX Enable
    usart_cr1_set_bit(usart,USART_CR1_UE); //USART Enable
}
