set(CHIP_NAME STM32F429ZI)

include(${CMAKE_CURRENT_LIST_DIR}/../stm32f429xx.cmake)

list(APPEND TARGET_COMPILE_DEFINITIONS
    -D${CHIP_NAME}
)

list(APPEND TARGET_LINK_OPTIONS 
    -T${CMAKE_CURRENT_LIST_DIR}/STM32F429ZITx_FLASH.ld
)

list(APPEND TARGET_INCLUDE_DIRECTORIES 
    ${CMAKE_CURRENT_LIST_DIR}/inc
)

list(APPEND TARGET_SOURCE_FILES
    ${CMAKE_CURRENT_LIST_DIR}/src/startup.S
    ${CMAKE_CURRENT_LIST_DIR}/src/syscalls.c
    ${CMAKE_CURRENT_LIST_DIR}/src/sysmem.c
    ${CMAKE_CURRENT_LIST_DIR}/src/stm32f429zi_system.cpp
)