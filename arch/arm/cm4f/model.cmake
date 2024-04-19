include(${CMAKE_CURRENT_LIST_DIR}/../arch.cmake)

list(APPEND TARGET_COMPILE_OPTIONS
    -mcpu=cortex-m4 
    -mfpu=fpv4-sp-d16
    -mfloat-abi=hard
    -mthumb
)

list(APPEND TARGET_LINK_OPTIONS 
    -mcpu=cortex-m4 
    -mfpu=fpv4-sp-d16
    -mfloat-abi=hard
    -mthumb
)