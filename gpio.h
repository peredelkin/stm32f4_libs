/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   gpio.h
 * Author: ruslan
 *
 * Created on 8 апреля 2018 г., 21:50
 */

#ifndef GPIO_H
#define GPIO_H

#include <stm32f4xx.h>

class gpio {
private:
    GPIO_TypeDef* gpio_port;
public:
    void mode_set(uint32_t mode);
    void mode_reset(uint32_t mode);
    void otype_set(uint32_t otype);
    void otype_reset(uint32_t otype);
    void ospeed_set(uint32_t ospeed);
    void ospeed_reset(uint32_t ospeed);
    void pupd_set(uint32_t pupd);
    void pupd_reset(uint32_t pupd);
    uint32_t idata_read();
    void odata_write(uint32_t odata);
    void odata_set(uint32_t odata);
    void odata_reset(uint32_t odata);
    void odata_toggle(uint32_t odata);
    uint32_t odata_read();
    void obit_set(uint16_t obit);
    void obit_reset(uint16_t obit);
    void lock_set(uint32_t lock);
    void lock_reset(uint32_t lock);
    void alt_func_set(uint32_t n_alt_func, uint32_t alt_func);
    void alt_func_reset(bool n_alt_func, uint32_t alt_func);
    gpio(GPIO_TypeDef* port);
};

#endif /* GPIO_H */

