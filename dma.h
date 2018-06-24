/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   newfile.h
 * Author: ruslan
 *
 * Created on 24 июня 2018 г., 17:56
 */

#ifndef DMA_H
#define DMA_H

#include <stm32f4xx.h>

namespace dma {

    enum sxcr_t {
        CHSEL_0 = 0,
        CHSEL_1 = DMA_SxCR_CHSEL_0,
        CHSEL_2 = DMA_SxCR_CHSEL_1,
        CHSEL_3 = DMA_SxCR_CHSEL_1 | DMA_SxCR_CHSEL_0,
        CHSEL_4 = DMA_SxCR_CHSEL_2,
        CHSEL_5 = DMA_SxCR_CHSEL_2 | DMA_SxCR_CHSEL_0,
        CHSEL_6 = DMA_SxCR_CHSEL_2 | DMA_SxCR_CHSEL_1,
        CHSEL_7 = DMA_SxCR_CHSEL,
        MBURST_0 = 0,
        MBURST_4 = DMA_SxCR_MBURST_0,
        MBURST_8 = DMA_SxCR_MBURST_1,
        MBURST_16 = DMA_SxCR_MBURST,
        PBURST_0 = 0,
        PBURST_4 = DMA_SxCR_PBURST_0,
        PBURST_8 = DMA_SxCR_PBURST_1,
        PBURST_16 = DMA_SxCR_PBURST,
        CT = DMA_SxCR_CT,
        DBM = DMA_SxCR_DBM,
        PL_LOW = 0,
        PL_MEDIUM = DMA_SxCR_PL_0,
        PL_HIGH = DMA_SxCR_PL_1,
        PL_V_HIGH = DMA_SxCR_PL,
        PINCOS = DMA_SxCR_PINCOS,
        MSIZE_8 = 0,
        MSIZE_16 = DMA_SxCR_MSIZE_0,
        MSIZE_32 = DMA_SxCR_MSIZE_1,
        MSIZE_R = DMA_SxCR_MSIZE,
        PSIZE_8 = 0,
        PSIZE_16 = DMA_SxCR_PSIZE_0,
        PSIZE_32 = DMA_SxCR_PSIZE_1,
        PSIZE_R = DMA_SxCR_PSIZE,
        MINC = DMA_SxCR_MINC,
        PINC = DMA_SxCR_PINC,
        CIRC = DMA_SxCR_CIRC,
        DIR_P_M = 0,
        DIR_M_P = DMA_SxCR_DIR_0,
        DIR_M_M = DMA_SxCR_DIR_1,
        DIR_R = DMA_SxCR_DIR,
        PFCTRL = DMA_SxCR_PFCTRL,
        TCIE = DMA_SxCR_TCIE,
        HTIE = DMA_SxCR_HTIE,
        TEIE = DMA_SxCR_TEIE,
        DMEIE = DMA_SxCR_DMEIE,
        EN = DMA_SxCR_EN
    };

    class stream {
    private:
        DMA_Stream_TypeDef* dma_stream;
        
        void configuration_register_set(sxcr_t sxcr) {
            dma_stream->CR |= (uint32_t) sxcr;
        }

        void configuration_register_reset(sxcr_t sxcr) {
            dma_stream->CR &= ~((uint32_t) sxcr);
        }

        bool configuration_register_read(sxcr_t sxcr) {
            if ((dma_stream->CR & (uint32_t) sxcr) == (uint32_t) sxcr) return 1;
            else return 0;
        }
        
    public:
        void minc_enable() {
            configuration_register_set(MINC);
        }
        
        void minc_disable() {
            configuration_register_reset(MINC);
        }
        
        void enable() {
            configuration_register_set(EN);
        }
        
        void disable() {
            configuration_register_reset(EN);
        }
        
        void ch_sel(sxcr_t sxcr) {
            configuration_register_reset(CHSEL_7);
            configuration_register_set(sxcr);
        }

        void mburst_set(sxcr_t sxcr) {
            configuration_register_reset(MBURST_16);
            configuration_register_set(sxcr);
        }

        void pburst_set(sxcr_t sxcr) {
            configuration_register_reset(PBURST_16);
            configuration_register_set(sxcr);
        }

        void priority_set(sxcr_t sxcr) {
            configuration_register_reset(PL_V_HIGH);
            configuration_register_set(sxcr);
        }

        void msize_set(sxcr_t sxcr) {
            configuration_register_reset(MSIZE_R);
            configuration_register_set(sxcr);
        }

        void psize_set(sxcr_t sxcr) {
            configuration_register_reset(PSIZE_R);
            configuration_register_set(sxcr);
        }

        void dir_set(sxcr_t sxcr) {
            configuration_register_reset(DIR_R);
            configuration_register_set(sxcr);
        }

        void numb_of_data_set(uint16_t ndt) {
            dma_stream->NDTR = ndt;
        }
        void periph_addr_set(uint32_t par) {
            dma_stream->PAR = par;
        }

        void mem_0_addr_set(uint32_t mar) {
            dma_stream->M0AR = mar;
        }

        void mem_1_addr_set(uint32_t mar) {
            dma_stream->M1AR = mar;
        }

        stream(DMA_Stream_TypeDef* n_stream) {
            dma_stream = n_stream;
        }
    };
};

#endif /* NEWFILE_H */

