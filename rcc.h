/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   rcc.h
 * Author: ruslan
 *
 * Created on 10 февраля 2018 г., 22:59
 */

#ifndef RCC_H
#define RCC_H

#include <stm32f4xx.h>
#include <stdbool.h>
#include <macroses.h>

typedef struct {
    RCC_TypeDef* rcc;
}rcc_t;

#endif /* RCC_H */
