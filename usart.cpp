/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <usart.h>

bool usart::bus::status_register_read(stat_t status) {
    if ((usart_bus_port->SR & (uint16_t) status) == (uint16_t) status) return 1;
    else return 0;
}

void usart::bus::status_register_reset(stat_t status) {
    usart_bus_port->SR &= ~((uint16_t) status);
}

void usart::bus::baud_rate_register_set(uint16_t mantissa, uint16_t fraction) {
    usart_bus_port->BRR = ((uint16_t) (mantissa << 4) & (uint16_t) DIV_Mantissa) |
            ((uint16_t) fraction & (uint16_t) DIV_Fraction);
}

void usart::bus::control_register_set(ctrl_1_t ctrl) {
    usart_bus_port->CR1 |= (uint16_t) ctrl;
}

void usart::bus::control_register_set(ctrl_2_t ctrl) {
    usart_bus_port->CR2 |= (uint16_t) ctrl;
}

void usart::bus::control_register_set(ctrl_3_t ctrl) {
    usart_bus_port->CR3 |= (uint16_t) ctrl;
}

void usart::bus::control_register_reset(ctrl_1_t ctrl) {
    usart_bus_port->CR1 &= ~((uint16_t) ctrl);
}

void usart::bus::control_register_reset(ctrl_2_t ctrl) {
    usart_bus_port->CR2 &= ~((uint16_t) ctrl);
}

void usart::bus::control_register_reset(ctrl_3_t ctrl) {
    usart_bus_port->CR3 &= ~((uint16_t) ctrl);
}

bool usart::bus::control_register_read(ctrl_1_t ctrl) {
    if ((usart_bus_port->CR1 & (uint16_t) ctrl) == (uint16_t) ctrl) return 1;
    else return 0;
}

bool usart::bus::control_register_read(ctrl_2_t ctrl) {
    if ((usart_bus_port->CR2 & (uint16_t) ctrl) == (uint16_t) ctrl) return 1;
    else return 0;
}

bool usart::bus::control_register_read(ctrl_3_t ctrl) {
    if ((usart_bus_port->CR3 & (uint16_t) ctrl) == (uint16_t) ctrl) return 1;
    else return 0;
}

void usart::bus::guard_time_register_set(uint16_t guart_time) {
    usart_bus_port->GTPR &= ~((uint16_t) GT);
    usart_bus_port->GTPR |= (guart_time & (uint16_t) GT);
}

void usart::bus::prescaler_register_set(uint16_t prescaler) {
    usart_bus_port->GTPR &= ~((uint16_t) PSC);
    usart_bus_port->GTPR |= (prescaler & (uint16_t) PSC);
}

void usart::bus::flag_tc_reset() {
    status_register_reset(TC);
}

bool usart::bus::flag_tc_read() {
    return status_register_read(TC);
}

bool usart::bus::flag_txe_read() {
    return status_register_read(TXE);
}

bool usart::bus::oversampling_mode_read() {
    return control_register_read(OVER_8);
}

void usart::bus::interrupt_txe_enable() {
    control_register_set(TXEIE);
}

void usart::bus::interrupt_txe_disable() {
    control_register_reset(TXEIE);
}

uint32_t usart::bus::data_register_addr() {
    return (uint32_t)&(usart_bus_port->DR);
}

void usart::bus::dma_tx_enable() {
    control_register_set(DMAT);
}

void usart::bus::dma_tx_disable() {
    control_register_reset(DMAT);
}

void usart::bus::dma_rx_enable() {
    control_register_set(DMAR);
}

void usart::bus::dma_rx_diwable() {
    control_register_reset(DMAR);
}

void usart::bus::data_read(void* data, uint16_t index) {
    ((uint8_t*) data)[index] = (uint8_t) (usart_bus_port->DR & (uint16_t) DR);
}

void usart::bus::data_write(void* data, uint16_t index) {
    usart_bus_port->DR = ((uint16_t) ((uint8_t*) data)[index] & (uint16_t) DR);
}

void usart::bus::baud_rate_set(uint32_t fpclk, uint32_t baud) {
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

void usart::bus::write_poll(void* data, uint16_t size) {
    transmit.data = data;
    transmit.data_index = 0;
    transmit.data_size = size;
    while (transmit.data_index != transmit.data_size) {
        while (!flag_txe_read());
        data_write(transmit.data, transmit.data_index);
        transmit.data_index++;
    }
}

bool usart::bus::write_int(void* data, uint16_t size) {
    if (tx_busy) {
        return tx_busy;
    } else {
        tx_busy = 1;
        transmit.data = data;
        transmit.data_index = 0;
        transmit.data_size = size;
        interrupt_txe_enable();
    }
}

void usart::bus::interrupt_txe_handler() {
    if (flag_txe_read()) {
        data_write(transmit.data, transmit.data_index);
        transmit.data_index++;
        if (transmit.data_index >= transmit.data_size) {
            tx_busy = 0;
            interrupt_txe_disable();
        }
    }
}

void usart::bus::init(uint32_t fpclk, uint32_t baud, bool te, bool re) {
    baud_rate_set(fpclk, baud);
    if (te) {
        control_register_set(TE); //TX Enable
    } else {
        control_register_reset(TE); //TX Disable
    }

    if (re) {
        control_register_set(RE); //RX Enable
    } else {
        control_register_reset(RE); //RX Disable
    }

    if (te || re) {
        control_register_set(UE); //USART Enable
    } else {
        control_register_reset(UE); //USART Disable
    }
}

usart::bus::bus(USART_TypeDef* port) {
    usart_bus_port = port;
}