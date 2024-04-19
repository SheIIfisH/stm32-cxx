#ifndef STM32f429ZI_SYSTEM_H_
#define STM32f429ZI_SYSTEM_H_

#include <stdint.h>
#include "stm32f429zi_constants.hpp"
#include "stm32f429zi_sysconfig.hpp"

namespace sys
{
    class System
    {
    public:
        System(): System::System(SystemConfig()) {}
        System(SystemConfig p_config){}
        ~System() {}

        void reg(uint_fast32_t p_addr, uint_fast32_t p_data);
        uint_fast32_t reg(uint_fast32_t p_addr);
    };
}

#endif