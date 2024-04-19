#ifndef STM32f429ZI_SYSCONFIG_H_
#define STM32f429ZI_SYSCONFIG_H_

#include <stdint.h>

namespace sys
{
    struct SystemConfig
    {
        struct mainclk_t
        {
            enum class clksrc_t
            {
                HSI,
                HSE,
                PLL
            };
            
            clksrc_t source = SystemConfig::mainclk_t::clksrc_t::HSI;
            uint_fast32_t Sysclkfreq = 180'000'000;
            uint_fast32_t HSEfreq = 0;
            uint_fast16_t AHBprsc  = 1;
            bool HSEbypass = false;
            bool CSS_en = false;
            bool DMA1_en = false;
            bool DMA2_en = false; 
            bool DMA3_en = false;
        } mainclk;
        
        struct perclk_t
        {
            static constexpr uint_fast16_t GPIOA = 1 << 0;
            static constexpr uint_fast16_t GPIOB = 1 << 1;
            static constexpr uint_fast16_t GPIOC = 1 << 2;
            static constexpr uint_fast16_t GPIOD = 1 << 3;
            static constexpr uint_fast16_t GPIOE = 1 << 4;
            static constexpr uint_fast16_t GPIOF = 1 << 5;
            static constexpr uint_fast16_t GPIOG = 1 << 6;
            static constexpr uint_fast16_t GPIOH = 1 << 7;
            static constexpr uint_fast16_t GPIOI = 1 << 8;
            static constexpr uint_fast16_t GPIOJ = 1 << 9;
            static constexpr uint_fast16_t GPIOK = 1 << 10;

            static constexpr uint_fast16_t TIM1 = 1 << 0;
            static constexpr uint_fast16_t TIM2 = 1 << 1;
            static constexpr uint_fast16_t TIM3 = 1 << 2;
            static constexpr uint_fast16_t TIM4 = 1 << 3;
            static constexpr uint_fast16_t TIM5 = 1 << 4;
            static constexpr uint_fast16_t TIM6 = 1 << 5;
            static constexpr uint_fast16_t TIM7 = 1 << 6;
            static constexpr uint_fast16_t TIM8 = 1 << 7;
            static constexpr uint_fast16_t TIM9 = 1 << 8;
            static constexpr uint_fast16_t TIM10 = 1 << 9;
            static constexpr uint_fast16_t TIM11 = 1 << 10;
            static constexpr uint_fast16_t TIM12 = 1 << 11;
            static constexpr uint_fast16_t TIM13 = 1 << 12;
            
            uint_fast8_t  APB1prsc = 4;
            uint_fast8_t  APB2prsc = 2;
            bool TIM1x4 = false;
            bool TIM2x4 = false;
            uint_fast16_t GPIO_en = 0;
            uint_fast16_t TIM_en  = 0;
            bool CRC_en  = false;
            bool CAN1_en = false;
            bool CAN2_en = false;
            bool USART1_en = false;
            bool USART2_en = false;
            bool USART3_en = false;
            bool USART6_en = false;
            bool UART4_en = false;
            bool UART5_en = false;
            bool UART7_en = false;
            bool UART8_en = false;
            bool I2C1_en = false;
            bool I2C2_en = false;
            bool I2C3_en = false;
            bool SPI1_en = false;
            bool SPI2_en = false;
            bool SPI3_en = false;
            bool SPI4_en = false;
            bool SPI5_en = false;
            bool SPI6_en = false;
            bool ADC1_en = false;
            bool ADC2_en = false;
            bool ADC3_en = false;
            bool DAC_en = false;
            bool PWRinterface_en = false;
            bool windowWatchdog_en = false;
            bool CCMDATARAM_en = false;
            bool backupSRAMinterface_en = false;
            bool HASH_en = false;
            bool cryptomodule_en = false;
            bool DCMI_en = false;
            bool flexibleMemoryController_en = false;
            bool systemConfigurationController_en = false;
        } perclk;

        struct lowspeedclk_t
        {
            bool LSI_on = false;
            bool LSE_on = false;
            bool LSEbypass = false;
        } lowspeedclk;

        struct per48clk_t
        {
            uint_fast32_t Per48freq = 30'000'000;
            bool USB_OTG_HSULP_en = false;
            bool USB_OTG_HS_en = false;
            bool USB_OTG_FS_en = false;
            bool RNG_en  = false;
            bool SDIO_en = false;
        } per48clk;

        struct I2Sclk_t
        {
            bool PLLI2S_on = false;
            bool I2S_external = false;
        } I2Sclk;
        
        struct SAIclk_t
        {
            bool PLLSAI_on = false;
            bool SAI1_en = false;
        } SAIclk;

        struct LTDC_t
        {
            bool LTDCclk_en = false;
        } LTDC;

        struct Ethernet_t
        {
            bool EthernetPTPclk_en = false;
            bool EthernetReceptionclk_en = false;
            bool EthernetTransmissionclk_en = false;
        } Ethernet;   
    };
}

#endif