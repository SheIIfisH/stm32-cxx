#ifndef STM32f429ZI_CONSTANTS_H_
#define STM32f429ZI_CONSTANTS_H_

namespace sys
{
    namespace rcc
    {
        constexpr uint_fast32_t HSIfreq = 16'000'000;

        // PLL constants
        constexpr uint_fast32_t MinVcoFreq = 100'000'000;
        constexpr uint_fast32_t MaxVcoFreq = 432'000'000;
        constexpr uint_fast32_t MinInVcoFreq = 1'000'000;
        constexpr uint_fast32_t MaxInVcoFreq = 2'000'000;
        constexpr uint_fast32_t MinQ = 2;
        constexpr uint_fast32_t MaxQ = 15;
        constexpr uint_fast32_t MinM = 2;
        constexpr uint_fast32_t MaxM = 63;
        constexpr uint_fast32_t MinN = 50;
        constexpr uint_fast32_t MaxN = 432;
    }
}

#endif