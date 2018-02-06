/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   gpio.c
 * Author: ruslan
 * 
 * Created on 31 января 2018 г., 12:37
 */

#include "gpio.h"

/**
 * Устанавливает бит порта по маске
 * @param port Settable pin
 */
void gpo_pin_bset(gpio_TypeDef* port) {
    port->gpio->BSRRL = port->gpio_mask;
    port->pin_state = true;
}

/**
 * Сбрасывает бит порта по маске
 * @param port Resetable pin
 */
void gpo_pin_brst(gpio_TypeDef* port) {
    port->gpio->BSRRH = port->gpio_mask;
    port->pin_state = false;
}

/**
 * Устанавливает бит порта маске
 * @param port Settable pin
 */
void gpo_pin_set(gpio_TypeDef* port) {
    port->gpio->ODR |= port->gpio_mask;
    port->pin_state = true;
}

/**
 * Сбрасывает бит порта по маске
 * @param port Resetable pin
 */
void gpo_pin_rst(gpio_TypeDef* port) {
    port->gpio->ODR &=~ port->gpio_mask;
    port->pin_state = false;
}

/**
 * Меняет бит порта на противоположный по маске
 * @param port Invertible pin
 */
void gpo_pin_tog(gpio_TypeDef* port) {
    port->gpio->ODR ^= port->gpio_mask;
    port->pin_state = gpo_pin_read(port);
}

/**
 * Возвращает состояние бита выхода по маске
 * @param port Readable out pin
 * @return Pin state
 */
bool gpo_pin_read(gpio_TypeDef* port) {
    if((port->gpio->ODR & port->gpio_mask) == port->gpio_mask) return true;
    return false;
}

/**
 * Возвращает состояние бита входа по маске
 * @param port Readable in pin
 * @return Pin state
 */
bool gpi_pin_read(gpio_TypeDef* port) {
    if((port->gpio->IDR & port->gpio_mask) == port->gpio_mask) return true;
    return false;
}

/**
 * Программное обнаружение переднего фронта бита входа по маске
 * @param port Readable in pin
 * @return Rise
 */
bool gpi_pin_srd(gpio_TypeDef* port) { //soft rise detecting
    bool cur_state = gpi_pin_read(port);
    if(cur_state & ~port->pin_state) {
        port->pin_state = cur_state;
        return true;
    }
    port->pin_state = cur_state;
    return false;
}

/**
 * Программное обнаружение заднего фронта бита входа по маске
 * @param port Readable in pin
 * @return Fall
 */
bool gpi_pin_sfd(gpio_TypeDef* port) { //soft fall detectig
    bool cur_state = gpi_pin_read(port);
    if(~cur_state & port->pin_state) {
        port->pin_state = cur_state;
        return true;
    }
    port->pin_state = cur_state;
    return false;
}

/**
 * 
 * @param port
 * @param data
 */
void gpo_port_bset_by_mask(gpio_TypeDef* port,const gpio_t data) {
    port->gpio->BSRRL = (port->gpio_mask & data);
}
/**
 * 
 * @param port
 * @param data
 */
void gpo_port_brst_by_mask(gpio_TypeDef* port,const gpio_t data) {
    port->gpio->BSRRH = (port->gpio_mask & data);
}
/**
 * 
 * @param port
 * @param data
 */
void gpo_port_write_by_mask(gpio_TypeDef* port,const gpio_t data) {
    gpo_port_brst_by_mask(port,~data);
    gpo_port_bset_by_mask(port,data);
}
/**
 * 
 * @param port
 * @param data
 */
void gpo_port_range_write(gpio_TypeDef* port,const gpio_t data) {
    gpio_t range_data = (data << port->shift);
    gpo_port_write_by_mask(port,range_data);
}

/**
 * 
 * @param port
 * @return 
 */
gpio_t gpo_port_range_read(gpio_TypeDef* port) {
    gpio_t data = (port->gpio_mask & (port->gpio->ODR >> port->shift));
    return data;
}

/**
 * 
 * @param port
 * @return 
 */
gpio_t gpi_port_range_read(gpio_TypeDef* port) {
    gpio_t data = (port->gpio_mask & (port->gpio->IDR >> port->shift));
    return data;
}