#include <stdio.h>
#include "stm32f4_pll_calculator.hpp"

int main(void){
    constexpr unsigned SysClockFreq = 96'000'000; 

	using pll_calc = stm32f4_pll_calculator<
		SysClockFreq
	>;

    while (1){}
    return 0;
}