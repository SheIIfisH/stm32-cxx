#ifndef STM32f4_PLL_CALCULATOR_H_
#define STM32f4_PLL_CALCULATOR_H_

#include <stdint.h>

#if defined(STM32F42xxx) || defined(STM32F43xxx)
namespace sys
{
    class stm32_pll_calculator
	{
        uint_fast16_t M = 0, N = 0, P = 0, Q = rcc::MinQ;

        inline stm32_pll_calculator()
        {
            
        }
    };
}
#endif

#endif