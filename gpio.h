/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   gpio.h
 * Author: ruslan
 *
 * Created on 31 января 2018 г., 12:37
 */

#ifndef GPIO_H
#define GPIO_H

#include <stm32f4xx.h>
#include <stdbool.h>
#include "macroses.h"

typedef uint16_t port_t;

typedef struct {
    GPIO_TypeDef* gpio;
    const port_t gpio_mask;
    const uint8_t shift;
    bool pin_state;
} gpio_t;


extern void gpio_pin_state_write(gpio_t* port,bool state);

extern bool gpio_pin_state_read(gpio_t* port);

extern void gpio_pin_state_set(gpio_t* port);

extern void gpio_pin_state_rst(gpio_t* port);

extern void gpo_pin_bset(gpio_t* port);

extern void gpo_pin_brst(gpio_t* port);

extern void gpo_pin_set(gpio_t* port);

extern void gpo_pin_rst(gpio_t* port);

extern void gpo_pin_tog(gpio_t* port);

extern bool gpo_pin_read(gpio_t* port);

extern bool gpi_pin_read(gpio_t* port);

extern bool gpi_pin_srd(gpio_t* port);

extern bool gpi_pin_sfd(gpio_t* port);

extern void gpo_port_bset_by_mask(gpio_t* port, const port_t data);

extern void gpo_port_brst_by_mask(gpio_t* port, const port_t data);

extern void gpo_port_write_by_mask(gpio_t* port, const port_t data);

extern void gpo_port_range_write(gpio_t* port, const port_t data);

extern port_t gpo_port_range_read(gpio_t* port);

extern port_t gpi_port_range_read(gpio_t* port);

#endif /* GPIO_H */
