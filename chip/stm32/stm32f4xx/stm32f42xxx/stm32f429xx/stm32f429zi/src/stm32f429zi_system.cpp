#include <stdint.h>
#include "stm32f429zi_system.hpp"
//#include "stm32f4_pll_calculator.hpp"
#include "stm32f429xx.h"

// Write data directly in memory. Avoid using this function
void sys::System::reg(uint_fast32_t p_addr, uint_fast32_t p_data)
{
    *((uint32_t*) p_addr) = p_data;
}

// Read data directly from memory. Avoid using this function
uint_fast32_t sys::System::reg(uint_fast32_t p_addr)
{
    return *((uint32_t*) p_addr);
}
