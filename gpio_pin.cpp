/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <gpio_pin.h>

void pin::mode(uint32_t mode) {
    uint32_t mode_mask = (0b11 << (pin_number * 2));
    mode_reset(mode_mask);
    mode_set(mode & mode_mask);
}

void pin::mode() {
    uint32_t mode_mask = (0b11 << (pin_number * 2));
    mode_reset(mode_mask);
}

void pin::otype(uint32_t otype) {
    uint32_t otype_mask = (0b1 << pin_number);
    otype_reset(otype_mask);
    otype_set(otype & otype_mask);
}

void pin::otype() {
    uint32_t otype_mask = (0b1 << pin_number);
    otype_reset(otype_mask);
}

void pin::ospeed(uint32_t ospeed) {
    uint32_t ospeed_mask = (0b11 << (pin_number * 2));
    ospeed_reset(ospeed_mask);
    ospeed_set(ospeed & ospeed_mask);
}

void pin::ospeed() {
    uint32_t ospeed_mask = (0b11 << (pin_number * 2));
    ospeed_reset(ospeed_mask);
}

void pin::pupd(uint32_t pupd) {
    uint32_t pupd_mask = (0b11 << (pin_number * 2));
    pupd_reset(pupd_mask);
    pupd_set(pupd & pupd_mask);
}

void pin::pupd() {
    uint32_t pupd_mask = (0b11 << (pin_number * 2));
    pupd_reset(pupd_mask);
}

bool pin::read_in() {
    if (((idata_read() & base_mask) == base_mask)) return 1;
    else return 0;
}

void pin::write_out(bool state) {
    uint16_t state_mask = (state << pin_number);
    obit_reset((~state_mask) & base_mask);
    obit_set(state_mask & base_mask);
}

bool pin::read_out() {
    if (((odata_read() & base_mask) == base_mask)) return 1;
    else return 0;
}

void pin::toggle() {
    odata_toggle(base_mask);
}

void pin::alternate(uint32_t altfunc) {
    bool altfunc_n = (pin_number / 8);
    uint32_t altfunc_mask = (0b111 << ((pin_number % 8)*4));
    alt_func_reset(altfunc_n, altfunc_mask);
    alt_func_set(altfunc_n, altfunc & altfunc_mask);
}

void pin::alternate() {
    bool altfunc_n = (pin_number / 8);
    uint32_t altfunc_mask = (0b111 << ((pin_number % 8)*4));
    alt_func_reset(altfunc_n, altfunc_mask);
}

pin::pin(GPIO_TypeDef* port, uint8_t pin_n) : gpio(port) {
    pin_number = pin_n;
    base_mask = (1 << pin_number);
    mode();
    ospeed();
    pupd();
    alternate();
}
