/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <gpio.h>

void gpio::mode_set(uint32_t mode) {
    gpio_port->MODER |= mode;
}

void gpio::mode_reset(uint32_t mode) {
    gpio_port->MODER &= ~mode;
}

void gpio::otype_set(uint32_t otype) {
    gpio_port->OTYPER |= otype;
}

void gpio::otype_reset(uint32_t otype) {
    gpio_port->OTYPER &= ~otype;
}

void gpio::ospeed_set(uint32_t ospeed) {
    gpio_port->OSPEEDR |= ospeed;
}

void gpio::ospeed_reset(uint32_t ospeed) {
    gpio_port->OSPEEDR &= ~ospeed;
}

void gpio::pupd_set(uint32_t pupd) {
    gpio_port->PUPDR |= pupd;
}

void gpio::pupd_reset(uint32_t pupd) {
    gpio_port->PUPDR &= ~pupd;
}

uint32_t gpio::idata_read() {
    return gpio_port->IDR;
}

void gpio::odata_write(uint32_t odata) {
    gpio_port->ODR = odata;
}

void gpio::odata_set(uint32_t odata) {
    gpio_port->ODR |= odata;
}

void gpio::odata_reset(uint32_t odata) {
    gpio_port->ODR &= ~odata;
}

void gpio::odata_toggle(uint32_t odata) {
    gpio_port->ODR ^= odata;
}

uint32_t gpio::odata_read() {
    return gpio_port->ODR;
}

void gpio::obit_set(uint16_t obit) {
    gpio_port->BSRRL = obit;
}

void gpio::obit_reset(uint16_t obit) {
    gpio_port->BSRRH = obit;
}

void gpio::lock_set(uint32_t lock) {
    gpio_port->LCKR |= lock;
}

void gpio::lock_reset(uint32_t lock) {
    gpio_port->LCKR &= ~lock;
}

void gpio::alt_func_set(uint32_t n_alt_func, uint32_t alt_func) {
    gpio_port->AFR[n_alt_func] |= alt_func;
}

void gpio::alt_func_reset(bool n_alt_func, uint32_t alt_func) {
    gpio_port->AFR[n_alt_func] &= ~alt_func;
}

gpio::gpio(GPIO_TypeDef* port) {
    gpio_port = port;
}