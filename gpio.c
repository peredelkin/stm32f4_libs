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

#include <gpio.h>

/**
 * Запись состояния
 * @param port
 * @param state
 */
void gpio_pin_state_write(gpio_t* port,bool state) {
    port->pin_state = state;
}

/**
 * Чтение состояния
 * @param port
 * @return 
 */
bool gpio_pin_state_read(gpio_t* port) {
    bool state = port->pin_state;
    return state;
}

/**
 * Установка состояния
 * @param port
 */
void gpio_pin_state_set(gpio_t* port) {
    gpio_pin_state_write(port,true);
}

/**
 * Сброс состояния
 * @param port
 */
void gpio_pin_state_rst(gpio_t* port) {
    gpio_pin_state_write(port,false);
}

/**
 * Устанавливает бит порта по маске
 * @param port Settable pin
 */
void gpo_pin_bset(gpio_t* port) {
    port->gpio->BSRRL = port->gpio_mask;
    port->pin_state = true;
}

/**
 * Сбрасывает бит порта по маске
 * @param port Resetable pin
 */
void gpo_pin_brst(gpio_t* port) {
    port->gpio->BSRRH = port->gpio_mask;
    port->pin_state = false;
}

/**
 * Устанавливает бит порта маске
 * @param port Settable pin
 */
void gpo_pin_set(gpio_t* port) {
    SET_BIT(port->gpio->ODR,port->gpio_mask);
    //port->gpio->ODR |= port->gpio_mask;
    port->pin_state = true;
}

/**
 * Сбрасывает бит порта по маске
 * @param port Resetable pin
 */
void gpo_pin_rst(gpio_t* port) {
    RESET_BIT(port->gpio->ODR,port->gpio_mask);
    //port->gpio->ODR &=~ port->gpio_mask;
    port->pin_state = false;
}

/**
 * Меняет бит порта на противоположный по маске
 * @param port Invertible pin
 */
void gpo_pin_tog(gpio_t* port) {
    TOGGLE_BIT(port->gpio->ODR,port->gpio_mask);
    //port->gpio->ODR ^= port->gpio_mask;
    port->pin_state = gpo_pin_read(port);
}

/**
 * Возвращает состояние бита выхода по маске
 * @param port Readable out pin
 * @return Pin state
 */
bool gpo_pin_read(gpio_t* port) {
    if(CHECK_BIT_BY_MASK(port->gpio->ODR,port->gpio_mask)) return true;
    //if((port->gpio->ODR & port->gpio_mask) == port->gpio_mask) return true;
    return false;
}

/**
 * Возвращает состояние бита входа по маске
 * @param port Readable in pin
 * @return Pin state
 */
bool gpi_pin_read(gpio_t* port) {
    if(CHECK_BIT_BY_MASK(port->gpio->IDR,port->gpio_mask)) return true;
    //if((port->gpio->IDR & port->gpio_mask) == port->gpio_mask) return true;
    return false;
}

/**
 * Программное обнаружение переднего фронта бита входа по маске
 * @param port Readable in pin
 * @return Rise
 */
bool gpi_pin_srd(gpio_t* port) { //soft rise detecting
    bool cur_state = gpi_pin_read(port);
    if(cur_state & ~gpio_pin_state_read(port)) {
        gpio_pin_state_write(port,cur_state);
        return true;
    }
    gpio_pin_state_write(port,cur_state);
    return false;
}

/**
 * Программное обнаружение заднего фронта бита входа по маске
 * @param port Readable in pin
 * @return Fall
 */
bool gpi_pin_sfd(gpio_t* port) { //soft fall detectig
    bool cur_state = gpi_pin_read(port);
    if(~cur_state & gpio_pin_state_read(port)) {
        gpio_pin_state_write(port,cur_state);
        return true;
    }
    gpio_pin_state_write(port,cur_state);
    return false;
}

/**
 * Запись в регистр установки по маске
 * @param port
 * @param data
 */
void gpo_port_bset_by_mask(gpio_t* port,const port_t data) {
    WRITE_REG_BY_MASK(port->gpio->BSRRL,port->gpio_mask,data);
    //port->gpio->BSRRL = (port->gpio_mask & data);
}

/**
 * Запись в регистр сброса по маске
 * @param port
 * @param data
 */
void gpo_port_brst_by_mask(gpio_t* port,const port_t data) {
    WRITE_REG_BY_MASK(port->gpio->BSRRH,port->gpio_mask,data);
    //port->gpio->BSRRH = (port->gpio_mask & data);
}

/**
 * Запись в регистры сброса и установки по маске
 * @param port
 * @param data
 */
void gpo_port_write_by_mask(gpio_t* port,const port_t data) {
    gpo_port_brst_by_mask(port,~data);
    gpo_port_bset_by_mask(port,data);
}

/**
 * Запись в область регистров сброса и установки
 * @param port
 * @param data
 */
void gpo_port_range_write(gpio_t* port,const port_t data) {
    port_t range_data = (data << port->shift);
    gpo_port_write_by_mask(port,range_data);
}

/**
 * Чтение области выходного регистра
 * @param port
 * @return 
 */
port_t gpo_port_range_read(gpio_t* port) {
    port_t data = READ_REG_RANGE(port->gpio->ODR,port->gpio_mask,port->shift);
    //port_t data = ((port->gpio->ODR & port->gpio_mask) >> port->shift);
    return data;
}

/**
 * Чтение области входного регистра
 * @param port
 * @return 
 */
port_t gpi_port_range_read(gpio_t* port) {
    port_t data = READ_REG_RANGE(port->gpio->IDR,port->gpio_mask,port->shift);
    //port_t data = ((port->gpio->IDR & port->gpio_mask) >> port->shift);
    return data;
}