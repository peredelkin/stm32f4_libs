/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   macroses.h
 * Author: ruslan
 *
 * Created on 7 февраля 2018 г., 15:41
 */

#ifndef MACROSES_H
#define MACROSES_H

#ifndef SET_BIT
#define SET_BIT(REG,BIT) ((REG)|=(BIT))
#endif /* SET_BIT */

#ifndef RESET_BIT
#define RESET_BIT(REG,BIT) ((REG) &= ~(BIT))
#endif /* RST_BIT */

#ifndef TOGGLE_BIT
#define TOGGLE_BIT(REG,BIT) ((REG) ^= (BIT))
#endif /* TOG_BIT */

#ifndef CHECK_BIT_BY_MASK
#define CHECK_BIT_BY_MASK(REG,MASK) (((REG) & (MASK)) == (MASK))
#endif /* READ_BIT_BY_MASK */

#ifndef WRITE_REG_BY_MASK
#define WRITE_REG_BY_MASK(REG,MASK,DATA) ((REG) = ((MASK) & (DATA)))
#endif

#ifndef READ_REG_BY_MASK
#define READ_REG_BY_MASK(REG,MASK,DATA) ((DATA) = ((MASK) & (REG)))
#endif

#ifndef READ_REG_RANGE
#define READ_REG_RANGE(REG,MASK,SHIFT) (((REG) & (MASK)) >> (SHIFT))
#endif /* READ_REG_RANGE */

#endif /* MACROSES_H */

