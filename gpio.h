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
#include "stdbool.h"

typedef uint16_t gpio_t;

typedef struct {
    GPIO_TypeDef* gpio;
    const gpio_t gpio_mask;
    const uint8_t shift;
    bool pin_state;
} gpio_TypeDef;


extern void gpo_pin_bset(gpio_TypeDef* port);

extern void gpo_pin_brst(gpio_TypeDef* port);

extern void gpo_pin_set(gpio_TypeDef* port);

extern void gpo_pin_rst(gpio_TypeDef* port);

extern void gpo_pin_tog(gpio_TypeDef* port);

extern bool gpo_pin_read(gpio_TypeDef* port);

extern bool gpi_pin_read(gpio_TypeDef* port);

extern bool gpi_pin_srd(gpio_TypeDef* port);

extern bool gpi_pin_sfd(gpio_TypeDef* port);

extern void gpo_port_bset_by_mask(gpio_TypeDef* port, const gpio_t data);

extern void gpo_port_brst_by_mask(gpio_TypeDef* port, const gpio_t data);

extern void gpo_port_write_by_mask(gpio_TypeDef* port, const gpio_t data);

extern void gpo_port_range_write(gpio_TypeDef* port, const gpio_t data);

extern gpio_t gpo_port_range_read(gpio_TypeDef* port);

extern gpio_t gpi_port_range_read(gpio_TypeDef* port);

#endif /* GPIO_H */
