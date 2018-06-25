/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   newfile.h
 * Author: ruslan
 *
 * Created on 8 апреля 2018 г., 22:18
 */

#ifndef NEWFILE_H
#define NEWFILE_H

#include <gpio.h>

class pin : public gpio {
private:
    uint8_t pin_number;
    uint16_t base_mask;
public:
    void mode(uint32_t mode);
    void mode();
    void otype(uint32_t otype);
    void otype();
    void ospeed(uint32_t ospeed);
    void ospeed();
    void pupd(uint32_t opupd);
    void pupd();
    bool read_in();
    void write_out(bool state);
    bool read_out();
    void set();
    void reset();
    void toggle();
    void alternate(uint32_t altfunc);
    void alternate();
    pin(GPIO_TypeDef* port, uint8_t pin_n);
};

#endif /* NEWFILE_H */

