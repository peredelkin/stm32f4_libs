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
/****************Attention! Not completely verified*****************/
#include "usart.h"
/**
 * Read USART Status Register
 * @param usart: USART
 * @param sr_bit: Status Bit
 * @return: Value Of Status Bit 
 */
bool usart_status_register_bit_read(usart_t* usart,usart_sr_t sr_bit) {
    if(CHECK_BIT_BY_MASK(usart->usart->SR,sr_bit)) return 1;
    return 0;
}
void usart_status_register_bit_clr(usart_t* usart,usart_sr_t sr_bit) {
    RESET_BIT(usart->usart->SR,sr_bit);
}
/**
 * Read Parity Error Flag
 * @param usart: USART
 * @return: Parity Error
 */
bool usart_stat_error_parity_read(usart_t* usart) {
    return usart_status_register_bit_read(usart,USART_SR_PE);
}
/**
 * Read Framing Error Flag
 * @param: usart
 * @return: Framing Error
 */
bool usart_stat_error_framing_read(usart_t* usart) {
    return usart_status_register_bit_read(usart,USART_SR_FE);
}
/**
 * Read Noise Error Flag
 * @param: usart
 * @return: Noise Error
 */
bool usart_stat_noise_error_read(usart_t* usart) {
    return usart_status_register_bit_read(usart,USART_SR_NE);
}
/**
 * Read OverRun Error Flag
 * @param usart: USART
 * @return: OverRun Error 
 */
bool usart_stat_overrun_error_read(usart_t* usart) {
    return usart_status_register_bit_read(usart,USART_SR_ORE);
}
/**
 * Read IDLE line detected
 * @param usart: USART
 * @return: IDLE line
 */
bool usart_stat_idle_line_read(usart_t* usart) {
    return usart_status_register_bit_read(usart,USART_SR_IDLE);
}
/**
 * Read Receive Data Register Not Empty
 * @param usart: USART
 * @return: Receive Data Register Not Empty 
 */
bool usart_stat_receive_data_register_not_empty_read(usart_t* usart) {
    return usart_status_register_bit_read(usart,USART_SR_RXNE);
}
void usart_stat_receive_data_register_not_empty_clr(usart_t* usart) {
    usart_status_register_bit_clr(usart,USART_SR_RXNE);
}
/**
 * Read Transmission Complete
 * @param usart: USART
 * @return: Transmission Complete 
 */
bool usart_stat_transmission_complete_read(usart_t* usart) {
    return usart_status_register_bit_read(usart,USART_SR_TC);
}
void usart_stat_transmission_complete_clr(usart_t* usart) {
    return usart_status_register_bit_clr(usart,USART_SR_TC);
}
/**
 * Read Transmit Data Register Empty
 * @param usart: USART
 * @return: Transmit Data Register Empty 
 */
bool usart_stat_transmit_data_register_empty_read(usart_t* usart) {
    return usart_status_register_bit_read(usart,USART_SR_TXE);
}
/**
 * Read LIN Break Detection Flag
 * @param usart: USART
 * @return: LIN Break Detected
 */
bool usart_stat_lin_break_read(usart_t* usart) {
    return usart_status_register_bit_read(usart,USART_SR_LBD);
}
void usart_stat_lin_break_clr(usart_t* usart) {
    usart_status_register_bit_clr(usart,USART_SR_LBD);
}
/**
 * Read CTS Flag
 * @param usart: USART
 * @return: CTS Flag
 */
bool usart_stat_clear_to_send_read(usart_t* usart) {
    return usart_status_register_bit_read(usart,USART_SR_CTS);
}
void usart_stat_clear_to_send_clr(usart_t* usart) {
    usart_status_register_bit_clr(usart,USART_SR_CTS);
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
void usart_baud_rate_register_write(usart_t* usart,usart_brr_t mantissa,usart_brr_t fraction) {
    usart->usart->BRR = ((uint16_t)(mantissa << 4) & USART_BRR_DIV_Mantissa) |
            ((uint16_t)fraction & USART_BRR_DIV_Fraction);
}
/**
 * Read bit of ControlRegister1
 * @param usart: USART
 * @param cr_bit: CR1 bit mask
 * @return: State of rc_bit
 */
bool usart_control_register_1_bit_read(usart_t* usart,usart_cr_t cr_mask) {
    if(CHECK_BIT_BY_MASK(usart->usart->CR1,cr_mask)) return 1;
    return 0;
}
bool usart_control_register_2_bit_read(usart_t* usart,usart_cr_t cr_mask) {
    if(CHECK_BIT_BY_MASK(usart->usart->CR2,cr_mask)) return 1;
    return 0;
}
bool usart_control_register_3_bit_read(usart_t* usart,usart_cr_t cr_mask) {
    if(CHECK_BIT_BY_MASK(usart->usart->CR3,cr_mask)) return 1;
    return 0;
}
usart_cr_t usart_control_register_2_read(usart_t* usart,usart_cr_t cr_mask) {
    usart_cr_t control_register = (usart->usart->CR2 & cr_mask);
    return control_register;
}
/**
 * Set bit of Control Register 1
 * @param usart: USART
 * @param cr_bit: Control Register 1 bit mask
 */
void usart_control_register_1_bit_set(usart_t* usart,usart_cr_t cr_mask) {
    SET_BIT(usart->usart->CR1,cr_mask);
}
void usart_control_register_2_bit_set(usart_t* usart,usart_cr_t cr_mask) {
    SET_BIT(usart->usart->CR2,cr_mask);
}
void usart_control_register_3_bit_set(usart_t* usart,usart_cr_t cr_mask) {
    SET_BIT(usart->usart->CR3,cr_mask);
}
/**
 * Reset bit of Control Register 1
 * @param usart: USART
 * @param cr_bit: Control Register 1 bit mask
 */
void usart_control_register_1_bit_clr(usart_t* usart,usart_cr_t cr_mask) {
    RESET_BIT(usart->usart->CR1,cr_mask);
}
void usart_control_register_2_bit_clr(usart_t* usart,usart_cr_t cr_mask) {
    RESET_BIT(usart->usart->CR2,cr_mask);
}
void usart_control_register_3_bit_clr(usart_t* usart,usart_cr_t cr_mask) {
    RESET_BIT(usart->usart->CR3,cr_mask);
}
/**
 * Read  Oversampling mode
 * @param usart: USART
 * @return: Oversampling by 8 
 */
bool usart_ctrl_oversamp_read(usart_t* usart) {
    return usart_control_register_1_bit_read(usart,USART_CR1_OVER8);
}
void usart_ctrl_oversamp_8(usart_t* usart) {
    usart_control_register_1_bit_set(usart,USART_CR1_OVER8);
}
void usart_ctrl_oversamp_16(usart_t* usart) {
    usart_control_register_1_bit_clr(usart,USART_CR1_OVER8);
}
/**
 * Read Usart status
 * @param usart: USaRT
 * @return: Usarte Enable 
 */
bool usart_ctrl_usart_read(usart_t* usart) {
    return usart_control_register_1_bit_read(usart,USART_CR1_UE);
}
void usart_ctrl_usart_ena(usart_t* usart) {
    usart_control_register_1_bit_set(usart,USART_CR1_UE);
}
void usart_ctrl_usart_dis(usart_t* usart) {
    usart_control_register_1_bit_clr(usart,USART_CR1_UE);
}
/**
 * Read Word length
 * @param usart: Usart
 * @return: 9bit Word length (return 0 if 8bit)
 */
bool usart_ctrl_word_length_read(usart_t* usart) {
    return usart_control_register_1_bit_read(usart,USART_CR1_M);
}
void usart_ctrl_word_length_9b(usart_t* usart) {
    usart_control_register_1_bit_set(usart,USART_CR1_M);
}
void usart_ctrl_word_length_8b(usart_t* usart) {
    usart_control_register_1_bit_clr(usart,USART_CR1_M);
}
/**
 * Read Wakeup method
 * @param usart: USART
 * @return: Address Mark Wakeup method
 */
bool usart_ctrl_wakeup_method_read(usart_t* usart) {
    return usart_control_register_1_bit_read(usart,USART_CR1_WAKE);
}
void usart_ctrl_wakeup_method_address_mark(usart_t* usart) {
    usart_control_register_1_bit_set(usart,USART_CR1_WAKE);
}
void usart_ctrl_wakeup_method_idle_line(usart_t* usart) {
    usart_control_register_1_bit_clr(usart,USART_CR1_WAKE);
}
/**
 * Read Parity control
 * @param usart: USART
 * @return: Parity control enabled
 */
bool usart_ctrl_parity_control_read(usart_t* usart) {
    return usart_control_register_1_bit_read(usart,USART_CR1_PCE);
}
void usart_ctrl_parity_control_ena(usart_t* usart) {
    usart_control_register_1_bit_set(usart,USART_CR1_PCE);
}
void usart_ctrl_parity_control_dis(usart_t* usart) {
    usart_control_register_1_bit_clr(usart,USART_CR1_PCE);
}
/**
 * Read Parity selection
 * @param usart: USART
 * @return: Odd parity (return 0 if Even parity)
 */
bool usart_ctrl_parity_selection_read(usart_t* usart) {
    return usart_control_register_1_bit_read(usart,USART_CR1_PS);
}
void usart_ctrl_parity_selection_odd(usart_t* usart) {
    usart_control_register_1_bit_set(usart,USART_CR1_PS);
}
void usart_ctrl_parity_selection_even(usart_t* usart) {
    usart_control_register_1_bit_clr(usart,USART_CR1_PS);
}
/**
 * Read Parity Error interrupt
 * @param usart: USART
 * @return: Parity Error interrupt enabled
 */
bool usart_ctrl_interrupt_parity_error_read(usart_t* usart) {
    return usart_control_register_1_bit_read(usart,USART_CR1_PEIE);
}
void usart_ctrl_interrupt_parity_error_ena(usart_t* usart) {
    usart_control_register_1_bit_set(usart,USART_CR1_PEIE);
}
void usart_ctrl_interrupt_parity_error_dis(usart_t* usart) {
    usart_control_register_1_bit_clr(usart,USART_CR1_PEIE);
}
/**
 * Read Transmit Data Register Empty interrupt
 * @param usart: USART
 * @return: Transmit Data Register Empty interrupt enabled
 */
bool usart_ctrl_interrupt_tx_empty_read(usart_t* usart) {
    return usart_control_register_1_bit_read(usart,USART_CR1_TXEIE);
}
void usart_ctrl_interrupt_tx_empty_ena(usart_t* usart) {
    usart_control_register_1_bit_set(usart,USART_CR1_TXEIE);
}
void usart_ctrl_interrupt_tx_empty_dis(usart_t* usart) {
    usart_control_register_1_bit_clr(usart,USART_CR1_TXEIE);
}
/**
 * Read Transmission complete interrupt
 * @param usart: USART
 * @return: Transmission complete interrupt enabled
 */
bool usart_ctrl_interrupt_tx_complete_read(usart_t* usart) {
    return usart_control_register_1_bit_read(usart,USART_CR1_TCIE);
}
void usart_ctrl_interrupt_tx_complete_ena(usart_t* usart) {
    usart_control_register_1_bit_set(usart,USART_CR1_TCIE);
}
void usart_ctrl_interrupt_tx_complete_dis(usart_t* usart) {
    usart_control_register_1_bit_clr(usart,USART_CR1_TCIE);
}
/**
 * Receive Data Register Not Empty interrupt
 * @param usart: USART
 * @return: Receive Data Register Not Empty interrupt enabled 
 */
bool usart_ctrl_interrupt_rx_not_empty_read(usart_t* usart) {
    return usart_control_register_1_bit_read(usart,USART_CR1_RXNEIE);
}
void usart_ctrl_interrupt_rx_not_empty_ena(usart_t* usart) {
    usart_control_register_1_bit_set(usart,USART_CR1_RXNEIE);
}
void usart_ctrl_interrupt_rx_not_empty_dis(usart_t* usart) {
    usart_control_register_1_bit_clr(usart,USART_CR1_RXNEIE);
}
/**
 * Read IDLE Line interrupt
 * @param usart: USART
 * @return: IDLE interrupt enabled  
 */
bool usart_ctrl_interrupt_idle_line_read(usart_t* usart) {
    return usart_control_register_1_bit_read(usart,USART_CR1_IDLEIE);
}
void usart_ctrl_interrupt_idle_line_ena(usart_t* usart) {
    usart_control_register_1_bit_set(usart,USART_CR1_IDLEIE);
}
void usart_ctrl_interrupt_idle_line_dis(usart_t* usart) {
    usart_control_register_1_bit_clr(usart,USART_CR1_IDLEIE);
}
/**
 * Read Transmitter status
 * @param usart: USART
 * @return: Transmitter enabled 
 */
bool usart_ctrl_transmitter_read(usart_t* usart) {
    return usart_control_register_1_bit_read(usart,USART_CR1_TE);
}
void usart_ctrl_transmitter_ena(usart_t* usart) {
    usart_control_register_1_bit_set(usart,USART_CR1_TE);
}
void usart_ctrl_transmitter_dis(usart_t* usart) {
    usart_control_register_1_bit_clr(usart,USART_CR1_TE);
}
/**
 * Read Receiver status
 * @param usart: USART
 * @return: Receiver enabled 
 */
bool usart_ctrl_receiver_read(usart_t* usart) {
    return usart_control_register_1_bit_read(usart,USART_CR1_RE);
}
void usart_ctrl_receiver_ena(usart_t* usart) {
    usart_control_register_1_bit_set(usart,USART_CR1_RE);
}
void usart_ctrl_receiver_dis(usart_t* usart) {
    usart_control_register_1_bit_clr(usart,USART_CR1_RE);
}
/**
 * Read Receiver wakeup
 * @param usart: USART
 * @return: Receiver in mute mode (return 0 if Receiver in active mode)
 */
bool usart_ctrl_receiver_wakeup_read(usart_t* usart) {
    return usart_control_register_1_bit_read(usart,USART_CR1_RWU);
}
void usart_ctrl_receiver_wakeup_mute(usart_t* usart) {
    usart_control_register_1_bit_set(usart,USART_CR1_RWU);
}
void usart_ctrl_receiver_wakeup_active(usart_t* usart) {
    usart_control_register_1_bit_clr(usart,USART_CR1_RWU);
}
/**
 * Read Send Break
 * @param usart: USART
 * @return: Break character will be transmitted
 */
bool usart_ctrl_send_break_read(usart_t* usart) {
    return usart_control_register_1_bit_read(usart,USART_CR1_SBK);
}
void usart_ctrl_send_break_ena(usart_t* usart) {
    usart_control_register_1_bit_set(usart,USART_CR1_SBK);
}
void usart_ctrl_send_break_dis(usart_t* usart) {
    usart_control_register_1_bit_clr(usart,USART_CR1_SBK);
}

bool usart_ctrl_lin_mode_read(usart_t* usart) {
    return usart_control_register_2_bit_read(usart,USART_CR2_LINEN);
}
void usart_ctrl_lin_mode_ena(usart_t* usart) {
    usart_control_register_2_bit_set(usart,USART_CR2_LINEN);
}
void usart_ctrl_lin_mode_dis(usart_t* usart) {
    usart_control_register_2_bit_clr(usart,USART_CR2_LINEN);
}

void usart_ctrl_1_stop_bit_set(usart_t* usart) {
    usart_control_register_2_bit_clr(usart,USART_CR2_STOP); //00
}
void usart_ctrl_05_stop_bit_set(usart_t* usart) {
    usart_control_register_2_bit_set(usart,USART_CR2_STOP_0); //01
}
void usart_ctrl_2_stop_bit_set(usart_t* usart) {
    usart_control_register_2_bit_set(usart,USART_CR2_STOP_1); //10
}
void usart_ctrl_15_stop_bit_set(usart_t* usart) {
    usart_control_register_2_bit_set(usart,USART_CR2_STOP); //11
}

bool usart_ctrl_clock_pin_read(usart_t* usart) {
    return usart_control_register_2_bit_read(usart,USART_CR2_CLKEN);
}
void usart_ctrl_clock_pin_ena(usart_t* usart) {
    usart_control_register_2_bit_set(usart,USART_CR2_CLKEN);
}
void usart_ctrl_clock_pin_dis(usart_t* usart) {
    usart_control_register_2_bit_clr(usart,USART_CR2_CLKEN);
}

bool usart_ctrl_clock_polarity_read(usart_t* usart) {
    return usart_control_register_2_bit_read(usart,USART_CR2_CPOL);
}
void usart_ctrl_clock_polarity_high_set(usart_t* usart) {
    usart_control_register_2_bit_set(usart,USART_CR2_CPOL);
}
void usart_ctrl_clock_polarity_low_set(usart_t* usart) {
    usart_control_register_2_bit_clr(usart,USART_CR2_CPOL);
}

bool usart_ctrl_clock_phase_read(usart_t* usart) {
    return usart_control_register_2_bit_read(usart,USART_CR2_CPHA);
}
void usart_ctrl_clock_phase_second_set(usart_t* usart) {
    usart_control_register_2_bit_set(usart,USART_CR2_CPHA);
}
void usart_ctrl_clock_phase_first_set(usart_t* usart) {
    usart_control_register_2_bit_clr(usart,USART_CR2_CPHA);
}

bool usart_ctrl_clock_last_bit_pulse_read(usart_t* usart) {
    return usart_control_register_2_bit_read(usart,USART_CR2_LBCL);
}
void usart_ctrl_clock_last_bit_pulse_ena(usart_t* usart) {
    usart_control_register_2_bit_set(usart,USART_CR2_LBCL);
}
void usart_ctrl_clock_last_bit_pulse_dis(usart_t* usart) {
    usart_control_register_2_bit_clr(usart,USART_CR2_LBCL);
}

bool usart_ctrl_interrupt_lin_break_read(usart_t* usart) {
    return usart_control_register_2_bit_read(usart,USART_CR2_LBDIE);
}
void usart_ctrl_interrupt_lin_break_ena(usart_t* usart) {
    usart_control_register_2_bit_set(usart,USART_CR2_LBDIE);
}
void usart_ctrl_interrupt_lin_break_dis(usart_t* usart) {
    usart_control_register_2_bit_clr(usart,USART_CR2_LBDIE);
}

bool usart_ctrl_lin_break_detection_length_read(usart_t* usart) {
    return usart_control_register_2_bit_read(usart,USART_CR2_LBDL);
}
void usart_ctrl_lin_break_detection_length_11b(usart_t* usart) {
    usart_control_register_2_bit_set(usart,USART_CR2_LBDL);
}
void usart_ctrl_lin_break_detection_length_10b(usart_t* usart) {
    usart_control_register_2_bit_clr(usart,USART_CR2_LBDL);
}

usart_cr_t usart_ctrl_address_of_node_read(usart_t* usart) {
    return usart_control_register_2_read(usart,USART_CR2_ADD);
}
void usart_ctrl_address_of_node_set(usart_t* usart,usart_cr_t address) {
    usart_control_register_2_bit_set(usart,(USART_CR2_ADD & address));
}
void usart_ctrl_address_of_node_clr(usart_t* usart) {
    usart_control_register_2_bit_clr(usart,USART_CR2_ADD);
}

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

/***********MAIN FUNCTIONS**************/
/**
 * Configures BaudRateRegister by Bus Freq and baudrate
 * @param usart: USART
 * @param fpclk: Bus Freq in Hz
 * @param baud: BaudRate in Bps
 */
void usart_baud_rate_set(usart_t* usart,uint32_t fpclk,uint32_t baud) {
    uint32_t over8 = (uint32_t)usart_ctrl_oversamp_read(usart);
    uint32_t mantissa = (fpclk/((8*(2-over8))*baud));
    uint16_t divider = (uint16_t)(fpclk/baud);
    uint16_t fraction = (uint16_t)(divider - (uint16_t)(mantissa << 4));
    if(over8) {
        usart_baud_rate_register_write(usart,mantissa,(fraction & (uint16_t)0x07));
    } else {
        usart_baud_rate_register_write(usart,mantissa,fraction);
    }
}
/**
 * Initial BaudRate 9600,Enable TX,RX and USART
 * @param usart: USART
 */
void usart_std_init(usart_t* usart) {
    usart_baud_rate_set(usart,SystemCoreClock/2,9600);
    usart_control_register_1_bit_set(usart,USART_CR1_TE); //TX Enable
    usart_control_register_1_bit_set(usart,USART_CR1_RE); //RX Enable
    usart_control_register_1_bit_set(usart,USART_CR1_UE); //USART Enable
}
/**
 * Software send usart.transmit.data by usart.transmit.data_index
 * @param usart
 */
void usart_send_poll(usart_t* usart) {
    usart->transmit.data_index = 0;
    usart->transmit.data_size = (uint16_t)strnlen((const char*)usart->transmit.data,usart->transmit.index_max);
    while(usart->transmit.data_index!=usart->transmit.data_size) {
        while(!usart_stat_transmit_data_register_empty_read(usart));
        usart_data_write(usart,usart->transmit.data,usart->transmit.data_index);
        usart->transmit.data_index++;
    }
}