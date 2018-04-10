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
        SBK = USART_CR1_SBK
    };
    ctrl_1_t OVER_16 = (ctrl_1_t) 0;

    ctrl_1_t USART_ENABLE = UE;
    ctrl_1_t USART_DISABLE = (ctrl_1_t) 0;

    ctrl_1_t LENGTH_8 = (ctrl_1_t) 0;
    ctrl_1_t LENGTH_9 = M;

    ctrl_1_t IDLE_LINE = (ctrl_1_t) 0;
    ctrl_1_t ADDR_MARK = WAKE;

    ctrl_1_t PARITY_ENABLE = PCE;
    ctrl_1_t PARITY_DISABLE = (ctrl_1_t) 0;

    ctrl_1_t EVEN_PAR = (ctrl_1_t) 0;
    ctrl_1_t ODD_PAR = PS;

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
        ADD = USART_CR2_ADD
    };
    ctrl_2_t STOP_10 = (ctrl_2_t) 0;
    ctrl_2_t STOP_05 = STOP01;
    ctrl_2_t STOP_20 = STOP10;
    ctrl_2_t STOP_15 = STOP11;
    ctrl_2_t LOW = (ctrl_2_t) 0;
    ctrl_2_t HIGH = CPOL;
    ctrl_2_t FIRST = (ctrl_2_t) 0;
    ctrl_2_t SECOND = (ctrl_2_t) 0;

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
        EIE = USART_CR3_EIE
    };
    ctrl_3_t THREE_BIT = (ctrl_3_t) 0;

    enum gptmask_t {
        GT = USART_GTPR_GT,
        PSC = USART_GTPR_PSC
    };

    class bus {
    private:

        typedef struct {
            void* data;
            uint16_t data_index;
            uint16_t data_size;
            uint16_t index_max;
        } usart_trx_t;

        USART_TypeDef* usart_bus_port;

        bool status_register_read(stat_t status) {
            if ((usart_bus_port->SR & (uint16_t) status) == (uint16_t) status) return 1;
            else return 0;
        }

        void status_register_reset(stat_t status) {
            usart_bus_port->SR &= ~((uint16_t) status);
        }

        void baud_rate_register_set(uint16_t mantissa, uint16_t fraction) {
            usart_bus_port->BRR = ((uint16_t) (mantissa << 4) & (uint16_t) DIV_Mantissa) |
                    ((uint16_t) fraction & (uint16_t) DIV_Fraction);
        }

        void control_register_set(ctrl_1_t ctrl) {
            usart_bus_port->CR1 |= (uint16_t) ctrl;
        }

        void control_register_set(ctrl_2_t ctrl) {
            usart_bus_port->CR2 |= (uint16_t) ctrl;
        }

        void control_register_set(ctrl_3_t ctrl) {
            usart_bus_port->CR3 |= (uint16_t) ctrl;
        }

        void control_register_reset(ctrl_1_t ctrl) {
            usart_bus_port->CR1 &= ~((uint16_t) ctrl);
        }

        void control_register_reset(ctrl_2_t ctrl) {
            usart_bus_port->CR2 &= ~((uint16_t) ctrl);
        }

        void control_register_reset(ctrl_3_t ctrl) {
            usart_bus_port->CR3 &= ~((uint16_t) ctrl);
        }

        bool control_register_read(ctrl_1_t ctrl) {
            if ((usart_bus_port->CR1 & (uint16_t) ctrl) == (uint16_t) ctrl) return 1;
            else return 0;
        }

        bool control_register_read(ctrl_2_t ctrl) {
            if ((usart_bus_port->CR2 & (uint16_t) ctrl) == (uint16_t) ctrl) return 1;
            else return 0;
        }

        bool control_register_read(ctrl_3_t ctrl) {
            if ((usart_bus_port->CR3 & (uint16_t) ctrl) == (uint16_t) ctrl) return 1;
            else return 0;
        }

        void guard_time_register_set(uint16_t guart_time) {
            usart_bus_port->GTPR &= ~((uint16_t) GT);
            usart_bus_port->GTPR |= (guart_time & (uint16_t) GT);
        }

        void prescaler_register_set(uint16_t prescaler) {
            usart_bus_port->GTPR &= ~((uint16_t) PSC);
            usart_bus_port->GTPR |= (prescaler & (uint16_t) PSC);
        }
    public:

        usart_trx_t receive;
        usart_trx_t transmit;

        bool oversampling_mode_read() {
            return control_register_read(OVER_8);
        }

        void data_read(void* data, uint16_t index) {
            ((uint8_t*) data)[index] = (uint8_t) (usart_bus_port->DR & (uint16_t) DR);
        }

        void data_write(void* data, uint16_t index) {
            usart_bus_port->DR = ((uint16_t) ((uint8_t*) data)[index] & (uint16_t) DR);
        }

        void baud_rate_set(uint32_t fpclk, uint32_t baud) {
            uint32_t over8 = (uint32_t) oversampling_mode_read();
            uint32_t mantissa = (fpclk / ((8 * (2 - over8)) * baud));
            uint16_t divider = (uint16_t) (fpclk / baud);
            uint16_t fraction = (uint16_t) (divider - (uint16_t) (mantissa << 4));
            if (over8) {
                baud_rate_set(mantissa, (fraction & (uint16_t) 0x07));
            } else {
                baud_rate_register_set(mantissa, fraction);
            }
        }

        void send_poll() {
            transmit.data_index = 0;
            /* transmit.data_size = (uint16_t) strnlen((const char*) transmit.data,transmit.index_max); */
            transmit.data_size = (uint16_t) strlen((const char*) transmit.data);
            while (transmit.data_index != transmit.data_size) {
                while (!status_register_read(TXE));
                data_write(transmit.data, transmit.data_index);
                transmit.data_index++;
            }
        }

        void std_init() {
            baud_rate_set(SystemCoreClock / 4, 9600);
            control_register_set(TE); //TX Enable
            //control_register_set(RE); //RX Enable
            control_register_set(UE); //USART Enable
            transmit.data = (void*)"STM32F407VGT6\r\n";
        }

        bus(USART_TypeDef* port) {
            usart_bus_port = port;
        }
    };
};

#endif /* USART_H */

