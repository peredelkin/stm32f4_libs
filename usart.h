/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   usart.h
 * Author: ruslan
 *
 * Created on 11 апреля 2018 г., 3:33
 */

#ifndef USART_H
#define USART_H

#include <stm32f4xx.h>
#include <cstring>

namespace usart {

    enum stat_t {
        CTS = USART_SR_CTS,
        LBD = USART_SR_LBD,
        TXE = USART_SR_TXE,
        TC = USART_SR_TC,
        RXNE = USART_SR_RXNE,
        IDLE = USART_SR_IDLE,
        ORE = USART_SR_ORE,
        NF = USART_SR_NE,
        FE = USART_SR_FE,
        PE = USART_SR_PE
    };

    enum dmask_t {
        DR = USART_DR_DR
    };

    enum brmask_t {
        DIV_Mantissa = USART_BRR_DIV_Mantissa,
        DIV_Fraction = USART_BRR_DIV_Fraction
    };

    enum ctrl_1_t {
        OVER_8 = USART_CR1_OVER8,
        UE = USART_CR1_UE,
        M = USART_CR1_M,
        WAKE = USART_CR1_WAKE,
        PCE = USART_CR1_PCE,
        PS = USART_CR1_PS,
        PEIE = USART_CR1_PEIE,
        TXEIE = USART_CR1_TXEIE,
        TCIE = USART_CR1_TCIE,
        RXNEIE = USART_CR1_RXNEIE,
        IDLEIE = USART_CR1_IDLEIE,
        TE = USART_CR1_TE,
        RE = USART_CR1_RE,
        RWU = USART_CR1_RWU,
        SBK = USART_CR1_SBK,

        OVER_16 = 0,

        USART_ENABLE = UE,
        USART_DISABLE = 0,

        LENGTH_8 = 0,
        LENGTH_9 = M,

        IDLE_LINE = 0,
        ADDR_MARK = WAKE,

        PARITY_ENABLE = PCE,
        PARITY_DISABLE = 0,

        EVEN_PAR = 0,
        ODD_PAR = PS,
    };

    enum ctrl_2_t {
        LINEN = USART_CR2_LINEN,
        STOP01 = USART_CR2_STOP_0,
        STOP10 = USART_CR2_STOP_1,
        STOP11 = USART_CR2_STOP,
        CLKEN = USART_CR2_CLKEN,
        CPOL = USART_CR2_CPOL,
        CPHA = USART_CR2_CPHA,
        LBCL = USART_CR2_LBCL,
        LBDIE = USART_CR2_LBDIE,
        LBDL = USART_CR2_LBDL,
        ADD = USART_CR2_ADD,

        STOP_10 = 0,
        STOP_05 = STOP01,
        STOP_20 = STOP10,
        STOP_15 = STOP11,
        
        LOW = 0,
        HIGH = CPOL,
        
        FIRST = 0,
        SECOND = 0,
    };

    enum ctrl_3_t {
        ONE_BIT = USART_CR3_ONEBIT,
        CTSIE = USART_CR3_CTSIE,
        CTSE = USART_CR3_CTSE,
        RTSE = USART_CR3_RTSE,
        DMAT = USART_CR3_DMAT,
        DMAR = USART_CR3_DMAR,
        SCEN = USART_CR3_SCEN,
        NACK = USART_CR3_NACK,
        HDSEL = USART_CR3_HDSEL,
        IRLP = USART_CR3_IRLP,
        IREN = USART_CR3_IREN,
        EIE = USART_CR3_EIE,

        THREE_BIT = 0,
    };

    enum gptmask_t {
        GT = USART_GTPR_GT,
        PSC = USART_GTPR_PSC
    };

    class bus {
    private:
        bool tx_busy;

        typedef struct {
            void* data;
            uint16_t data_index;
            uint16_t data_size;
        } usart_trx_t;

        usart_trx_t receive;
        usart_trx_t transmit;

        USART_TypeDef* usart_bus_port;

        bool status_register_read(stat_t status);

        void status_register_reset(stat_t status);

        void baud_rate_register_set(uint16_t mantissa, uint16_t fraction);

        void control_register_set(ctrl_1_t ctrl);

        void control_register_set(ctrl_2_t ctrl);

        void control_register_set(ctrl_3_t ctrl);

        void control_register_reset(ctrl_1_t ctrl);

        void control_register_reset(ctrl_2_t ctrl);

        void control_register_reset(ctrl_3_t ctrl);

        bool control_register_read(ctrl_1_t ctrl);

        bool control_register_read(ctrl_2_t ctrl);

        bool control_register_read(ctrl_3_t ctrl);

        void guard_time_register_set(uint16_t guart_time);

        void prescaler_register_set(uint16_t prescaler);
    public:

        void flag_tc_reset();

        bool flag_tc_read();

        bool flag_txe_read();

        bool oversampling_mode_read();

        void interrupt_txe_enable();

        void interrupt_txe_disable();

        uint32_t data_register_addr();

        void dma_tx_enable();

        void dma_tx_disable();

        void dma_rx_enable();

        void dma_rx_diwable();

        void data_read(void* data, uint16_t index);

        void data_write(void* data, uint16_t index);

        void baud_rate_set(uint32_t fpclk, uint32_t baud);

        void write_poll(void* data, uint16_t size);

        bool write_int(void* data, uint16_t size);

        void interrupt_txe_handler();

        void init(uint32_t fpclk, uint32_t baud, bool te, bool re);

        bus(USART_TypeDef* port);
    };
};

#endif /* USART_H */

