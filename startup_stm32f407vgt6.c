/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdint.h>
#include <system_stm32f4xx.h>


#define ISR_COUNT 98 //1 (стек) + 15 (ядро) + 82 (внешние)

// Атрибуты обработчиков прерываний.
#ifndef HANDLER_ATTR
#define HANDLER_ATTR __attribute__((weak, alias("Default_Handler")))
#endif

// Секция функций начального запуска.
#ifndef STARTUP_CODE_SECTION
#endif

// Атрибуты функций начального запуска.
#ifndef STARTUP_FUNC_ATTR
#ifdef STARTUP_CODE_SECTION
#define STARTUP_FUNC_ATTR __attribute__((section(STARTUP_CODE_SECTION)))
#else
#define STARTUP_FUNC_ATTR
#endif //STARTUP_CODE_SECTION
#endif

// Стек.
extern char _estack;

// Инициализированные данные во флеш-памяти.
extern char _sidata;
// Инициализированные данные в ОЗУ.
// Начало.
extern char _sdata;
// Конец.
extern char _edata;
// Неинициализированные данные в ОЗУ.
// Начало.
extern char _sbss;
// Конец.
extern char _ebss;
// Массив инициализации.
// Начало.
extern char __init_array_start;
// Конец.
extern char __init_array_end;
// Массив деинициализации.
// Начало.
extern char __fini_array_start;
// Конец.
extern char __fini_array_end;

// Функция main.
extern int main();

// Реализация обработчика по-умолчанию.

STARTUP_FUNC_ATTR static void __Default_Handler(void) {
}

// Реализация обработчика сброса.

STARTUP_FUNC_ATTR static void __Reset_Handler(void) {
    register long* src;
    register long* dst;
    register long* end;

    src = (long*) &_sidata;
    dst = (long*) &_sdata;
    end = (long*) &_edata;
    while (dst < end) *dst++ = *src++;

    dst = (long*) &_sbss;
    end = (long*) &_ebss;
    while (dst < end) *dst++ = 0;

    src = (long*) &__init_array_start;
    end = (long*) &__init_array_end;
    while (src < end) ((void (*)()) * src++)();
    
    SystemInit();
    main();

    src = (long*) &__fini_array_start;
    end = (long*) &__fini_array_end;
    while (src < end) ((void (*)()) * src++)();
}

// Обработчик по-умолчанию.
void Default_Handler(void) __attribute__((weak, alias("__Default_Handler")));
// Значениея обработчиков по-умолчанию.
void Reset_Handler(void) __attribute__((weak, alias("__Reset_Handler")));
void NMI_Handler(void) HANDLER_ATTR;
void HardFault_Handler(void) HANDLER_ATTR;
void MemManage_Handler(void) HANDLER_ATTR;
void BusFault_Handler(void) HANDLER_ATTR;
void UsageFault_Handler(void) HANDLER_ATTR;

void SVC_Handler(void) HANDLER_ATTR;
void DebugMon_Handler(void) HANDLER_ATTR;

void PendSV_Handler(void) HANDLER_ATTR;
void SysTick_Handler(void) HANDLER_ATTR;

/* External Interrupts */
void WWDG_IRQHandler(void) HANDLER_ATTR; /* Window WatchDog              */
void PVD_IRQHandler(void) HANDLER_ATTR; /* PVD through EXTI Line detection */
void TAMP_STAMP_IRQHandler(void) HANDLER_ATTR; /* Tamper and TimeStamps through the EXTI line */
void RTC_WKUP_IRQHandler(void) HANDLER_ATTR; /* RTC Wakeup through the EXTI line */
void FLASH_IRQHandler(void) HANDLER_ATTR; /* FLASH                        */
void RCC_IRQHandler(void) HANDLER_ATTR; /* RCC                          */
void EXTI0_IRQHandler(void) HANDLER_ATTR; /* EXTI Line0                   */
void EXTI1_IRQHandler(void) HANDLER_ATTR; /* EXTI Line1                   */
void EXTI2_IRQHandler(void) HANDLER_ATTR; /* EXTI Line2                   */
void EXTI3_IRQHandler(void) HANDLER_ATTR; /* EXTI Line3                   */
void EXTI4_IRQHandler(void) HANDLER_ATTR; /* EXTI Line4                   */
void DMA1_Stream0_IRQHandler(void) HANDLER_ATTR; /* DMA1 Stream 0                */
void DMA1_Stream1_IRQHandler(void) HANDLER_ATTR; /* DMA1 Stream 1                */
void DMA1_Stream2_IRQHandler(void) HANDLER_ATTR; /* DMA1 Stream 2                */
void DMA1_Stream3_IRQHandler(void) HANDLER_ATTR; /* DMA1 Stream 3                */
void DMA1_Stream4_IRQHandler(void) HANDLER_ATTR; /* DMA1 Stream 4                */
void DMA1_Stream5_IRQHandler(void) HANDLER_ATTR; /* DMA1 Stream 5                */
void DMA1_Stream6_IRQHandler(void) HANDLER_ATTR; /* DMA1 Stream 6                */
void ADC_IRQHandler(void) HANDLER_ATTR; /* ADC1, ADC2 and ADC3s         */
void CAN1_TX_IRQHandler(void) HANDLER_ATTR; /* CAN1 TX                      */
void CAN1_RX0_IRQHandler(void) HANDLER_ATTR; /* CAN1 RX0                     */
void CAN1_RX1_IRQHandler(void) HANDLER_ATTR; /* CAN1 RX1                     */
void CAN1_SCE_IRQHandler(void) HANDLER_ATTR; /* CAN1 SCE                     */
void EXTI9_5_IRQHandler(void) HANDLER_ATTR; /* External Line[9:5]s          */
void TIM1_BRK_TIM9_IRQHandler(void) HANDLER_ATTR; /* TIM1 Break and TIM9          */
void TIM1_UP_TIM10_IRQHandler(void) HANDLER_ATTR; /* TIM1 Update and TIM10        */
void TIM1_TRG_COM_TIM11_IRQHandler(void) HANDLER_ATTR; /* TIM1 Trigger and Commutation and TIM11 */
void TIM1_CC_IRQHandler(void) HANDLER_ATTR; /* TIM1 Capture Compare         */
void TIM2_IRQHandler(void) HANDLER_ATTR; /* TIM2                         */
void TIM3_IRQHandler(void) HANDLER_ATTR; /* TIM3                         */
void TIM4_IRQHandler(void) HANDLER_ATTR; /* TIM4                         */
void I2C1_EV_IRQHandler(void) HANDLER_ATTR; /* I2C1 Event                   */
void I2C1_ER_IRQHandler(void) HANDLER_ATTR; /* I2C1 Error                   */
void I2C2_EV_IRQHandler(void) HANDLER_ATTR; /* I2C2 Event                   */
void I2C2_ER_IRQHandler(void) HANDLER_ATTR; /* I2C2 Error                   */
void SPI1_IRQHandler(void) HANDLER_ATTR; /* SPI1                         */
void SPI2_IRQHandler(void) HANDLER_ATTR; /* SPI2                         */
void USART1_IRQHandler(void) HANDLER_ATTR; /* USART1                       */
void USART2_IRQHandler(void) HANDLER_ATTR; /* USART2                       */
void USART3_IRQHandler(void) HANDLER_ATTR; /* USART3                       */
void EXTI15_10_IRQHandler(void) HANDLER_ATTR; /* External Line[15:10]s        */
void RTC_Alarm_IRQHandler(void) HANDLER_ATTR; /* RTC Alarm (A and B) through EXTI Line */
void OTG_FS_WKUP_IRQHandler(void) HANDLER_ATTR; /* USB OTG FS Wakeup through EXTI line */
void TIM8_BRK_TIM12_IRQHandler(void) HANDLER_ATTR; /* TIM8 Break and TIM12         */
void TIM8_UP_TIM13_IRQHandler(void) HANDLER_ATTR; /* TIM8 Update and TIM13        */
void TIM8_TRG_COM_TIM14_IRQHandler(void) HANDLER_ATTR; /* TIM8 Trigger and Commutation and TIM14 */
void TIM8_CC_IRQHandler(void) HANDLER_ATTR; /* TIM8 Capture Compare         */
void DMA1_Stream7_IRQHandler(void) HANDLER_ATTR; /* DMA1 Stream7                 */
void FSMC_IRQHandler(void) HANDLER_ATTR; /* FSMC                         */
void SDIO_IRQHandler(void) HANDLER_ATTR; /* SDIO                         */
void TIM5_IRQHandler(void) HANDLER_ATTR; /* TIM5                         */
void SPI3_IRQHandler(void) HANDLER_ATTR; /* SPI3                         */
void UART4_IRQHandler(void) HANDLER_ATTR; /* UART4                        */
void UART5_IRQHandler(void) HANDLER_ATTR; /* UART5                        */
void TIM6_DAC_IRQHandler(void) HANDLER_ATTR; /* TIM6 and DAC1&2 underrun errors */
void TIM7_IRQHandler(void) HANDLER_ATTR; /* TIM7                         */
void DMA2_Stream0_IRQHandler(void) HANDLER_ATTR; /* DMA2 Stream 0                */
void DMA2_Stream1_IRQHandler(void) HANDLER_ATTR; /* DMA2 Stream 1                */
void DMA2_Stream2_IRQHandler(void) HANDLER_ATTR; /* DMA2 Stream 2                */
void DMA2_Stream3_IRQHandler(void) HANDLER_ATTR; /* DMA2 Stream 3                */
void DMA2_Stream4_IRQHandler(void) HANDLER_ATTR; /* DMA2 Stream 4                */
void ETH_IRQHandler(void) HANDLER_ATTR; /* Ethernet                     */
void ETH_WKUP_IRQHandler(void) HANDLER_ATTR; /* Ethernet Wakeup through EXTI line */
void CAN2_TX_IRQHandler(void) HANDLER_ATTR; /* CAN2 TX                      */
void CAN2_RX0_IRQHandler(void) HANDLER_ATTR; /* CAN2 RX0                     */
void CAN2_RX1_IRQHandler(void) HANDLER_ATTR; /* CAN2 RX1                     */
void CAN2_SCE_IRQHandler(void) HANDLER_ATTR; /* CAN2 SCE                     */
void OTG_FS_IRQHandler(void) HANDLER_ATTR; /* USB OTG FS                   */
void DMA2_Stream5_IRQHandler(void) HANDLER_ATTR; /* DMA2 Stream 5                */
void DMA2_Stream6_IRQHandler(void) HANDLER_ATTR; /* DMA2 Stream 6                */
void DMA2_Stream7_IRQHandler(void) HANDLER_ATTR; /* DMA2 Stream 7                */
void USART6_IRQHandler(void) HANDLER_ATTR; /* USART6                       */
void I2C3_EV_IRQHandler(void) HANDLER_ATTR; /* I2C3 event                   */
void I2C3_ER_IRQHandler(void) HANDLER_ATTR; /* I2C3 error                   */
void OTG_HS_EP1_OUT_IRQHandler(void) HANDLER_ATTR; /* USB OTG HS End Point 1 Out   */
void OTG_HS_EP1_IN_IRQHandler(void) HANDLER_ATTR; /* USB OTG HS End Point 1 In    */
void OTG_HS_WKUP_IRQHandler(void) HANDLER_ATTR; /* USB OTG HS Wakeup through EXTI */
void OTG_HS_IRQHandler(void) HANDLER_ATTR; /* USB OTG HS                   */
void DCMI_IRQHandler(void) HANDLER_ATTR; /* DCMI                         */
void CRYP_IRQHandler(void) HANDLER_ATTR; /* CRYP crypto                  */
void HASH_RNG_IRQHandler(void) HANDLER_ATTR; /* Hash and Rng                 */
void FPU_IRQHandler(void) HANDLER_ATTR; /* FPU                          */

__attribute__((section(".isr_vector"))) static void* g_pfnVectors [ISR_COUNT] = {
    // Указатель стека.
    (void*) &_estack, //1
    // Обработчики прерываний ядра.
    (void*) Reset_Handler, //2
    (void*) NMI_Handler, //3
    (void*) HardFault_Handler, //4
    (void*) MemManage_Handler, //5
    (void*) BusFault_Handler, //6
    (void*) UsageFault_Handler, //7
    (void*) 0, //8
    (void*) 0, //9
    (void*) 0, //10
    (void*) 0, //11
    (void*) SVC_Handler, //12
    (void*) DebugMon_Handler, //13
    (void*) 0, //14
    (void*) PendSV_Handler, //15
    (void*) SysTick_Handler, //16
    /* External Interrupts */
    (void*) WWDG_IRQHandler, /* Window WatchDog              */
    (void*) PVD_IRQHandler, /* PVD through EXTI Line detection */
    (void*) TAMP_STAMP_IRQHandler, /* Tamper and TimeStamps through the EXTI line */
    (void*) RTC_WKUP_IRQHandler, /* RTC Wakeup through the EXTI line */
    (void*) FLASH_IRQHandler, /* FLASH                        */
    (void*) RCC_IRQHandler, /* RCC                          */
    (void*) EXTI0_IRQHandler, /* EXTI Line0                   */
    (void*) EXTI1_IRQHandler, /* EXTI Line1                   */
    (void*) EXTI2_IRQHandler, /* EXTI Line2                   */
    (void*) EXTI3_IRQHandler, /* EXTI Line3                   */
    (void*) EXTI4_IRQHandler, /* EXTI Line4                   */
    (void*) DMA1_Stream0_IRQHandler, /* DMA1 Stream 0                */
    (void*) DMA1_Stream1_IRQHandler, /* DMA1 Stream 1                */
    (void*) DMA1_Stream2_IRQHandler, /* DMA1 Stream 2                */
    (void*) DMA1_Stream3_IRQHandler, /* DMA1 Stream 3                */
    (void*) DMA1_Stream4_IRQHandler, /* DMA1 Stream 4                */
    (void*) DMA1_Stream5_IRQHandler, /* DMA1 Stream 5                */
    (void*) DMA1_Stream6_IRQHandler, /* DMA1 Stream 6                */
    (void*) ADC_IRQHandler, /* ADC1, ADC2 and ADC3s         */
    (void*) CAN1_TX_IRQHandler, /* CAN1 TX                      */
    (void*) CAN1_RX0_IRQHandler, /* CAN1 RX0                     */
    (void*) CAN1_RX1_IRQHandler, /* CAN1 RX1                     */
    (void*) CAN1_SCE_IRQHandler, /* CAN1 SCE                     */
    (void*) EXTI9_5_IRQHandler, /* External Line[9:5]s          */
    (void*) TIM1_BRK_TIM9_IRQHandler, /* TIM1 Break and TIM9          */
    (void*) TIM1_UP_TIM10_IRQHandler, /* TIM1 Update and TIM10        */
    (void*) TIM1_TRG_COM_TIM11_IRQHandler, /* TIM1 Trigger and Commutation and TIM11 */
    (void*) TIM1_CC_IRQHandler, /* TIM1 Capture Compare         */
    (void*) TIM2_IRQHandler, /* TIM2                         */
    (void*) TIM3_IRQHandler, /* TIM3                         */
    (void*) TIM4_IRQHandler, /* TIM4                         */
    (void*) I2C1_EV_IRQHandler, /* I2C1 Event                   */
    (void*) I2C1_ER_IRQHandler, /* I2C1 Error                   */
    (void*) I2C2_EV_IRQHandler, /* I2C2 Event                   */
    (void*) I2C2_ER_IRQHandler, /* I2C2 Error                   */
    (void*) SPI1_IRQHandler, /* SPI1                         */
    (void*) SPI2_IRQHandler, /* SPI2                         */
    (void*) USART1_IRQHandler, /* USART1                       */
    (void*) USART2_IRQHandler, /* USART2                       */
    (void*) USART3_IRQHandler, /* USART3                       */
    (void*) EXTI15_10_IRQHandler, /* External Line[15:10]s        */
    (void*) RTC_Alarm_IRQHandler, /* RTC Alarm (A and B) through EXTI Line */
    (void*) OTG_FS_WKUP_IRQHandler, /* USB OTG FS Wakeup through EXTI line */
    (void*) TIM8_BRK_TIM12_IRQHandler, /* TIM8 Break and TIM12         */
    (void*) TIM8_UP_TIM13_IRQHandler, /* TIM8 Update and TIM13        */
    (void*) TIM8_TRG_COM_TIM14_IRQHandler, /* TIM8 Trigger and Commutation and TIM14 */
    (void*) TIM8_CC_IRQHandler, /* TIM8 Capture Compare         */
    (void*) DMA1_Stream7_IRQHandler, /* DMA1 Stream7                 */
    (void*) FSMC_IRQHandler, /* FSMC                         */
    (void*) SDIO_IRQHandler, /* SDIO                         */
    (void*) TIM5_IRQHandler, /* TIM5                         */
    (void*) SPI3_IRQHandler, /* SPI3                         */
    (void*) UART4_IRQHandler, /* UART4                        */
    (void*) UART5_IRQHandler, /* UART5                        */
    (void*) TIM6_DAC_IRQHandler, /* TIM6 and DAC1&2 underrun errors */
    (void*) TIM7_IRQHandler, /* TIM7                         */
    (void*) DMA2_Stream0_IRQHandler, /* DMA2 Stream 0                */
    (void*) DMA2_Stream1_IRQHandler, /* DMA2 Stream 1                */
    (void*) DMA2_Stream2_IRQHandler, /* DMA2 Stream 2                */
    (void*) DMA2_Stream3_IRQHandler, /* DMA2 Stream 3                */
    (void*) DMA2_Stream4_IRQHandler, /* DMA2 Stream 4                */
    (void*) ETH_IRQHandler, /* Ethernet                     */
    (void*) ETH_WKUP_IRQHandler, /* Ethernet Wakeup through EXTI line */
    (void*) CAN2_TX_IRQHandler, /* CAN2 TX                      */
    (void*) CAN2_RX0_IRQHandler, /* CAN2 RX0                     */
    (void*) CAN2_RX1_IRQHandler, /* CAN2 RX1                     */
    (void*) CAN2_SCE_IRQHandler, /* CAN2 SCE                     */
    (void*) OTG_FS_IRQHandler, /* USB OTG FS                   */
    (void*) DMA2_Stream5_IRQHandler, /* DMA2 Stream 5                */
    (void*) DMA2_Stream6_IRQHandler, /* DMA2 Stream 6                */
    (void*) DMA2_Stream7_IRQHandler, /* DMA2 Stream 7                */
    (void*) USART6_IRQHandler, /* USART6                       */
    (void*) I2C3_EV_IRQHandler, /* I2C3 event                   */
    (void*) I2C3_ER_IRQHandler, /* I2C3 error                   */
    (void*) OTG_HS_EP1_OUT_IRQHandler, /* USB OTG HS End Point 1 Out   */
    (void*) OTG_HS_EP1_IN_IRQHandler, /* USB OTG HS End Point 1 In    */
    (void*) OTG_HS_WKUP_IRQHandler, /* USB OTG HS Wakeup through EXTI */
    (void*) OTG_HS_IRQHandler, /* USB OTG HS                   */
    (void*) DCMI_IRQHandler, /* DCMI                         */
    (void*) CRYP_IRQHandler, /* CRYP crypto                  */
    (void*) HASH_RNG_IRQHandler, /* Hash and Rng                 */
    (void*) FPU_IRQHandler, /* FPU                          */
};