cmake_minimum_required(VERSION 3.11)

set(CMAKE_GENERATOR "Ninja")

if (NOT DEFINED APPNAME) 
	message(FATAL_ERROR "APPNAME not defined")
endif()

if (NOT DEFINED BOARDNAME)
	message(FATAL_ERROR "BOARDNAME not defined")
endif()

if (NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Debug)
	message(WARNING "CMAKE_BUILD_TYPE not specified, set '${CMAKE_BUILD_TYPE}' by default")
endif()
string(TOUPPER ${CMAKE_BUILD_TYPE} CMAKE_BUILD_TYPE_UPPERCASE)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(NOT CMAKE_TOOLCHAIN_FILE)
	set(CMAKE_TOOLCHAIN_FILE  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/toolchain.cmake")
	message(WARNING "CMAKE_TOOLCHAIN_FILE not specified")
endif() 

project(${APPNAME}-${BOARDNAME})
enable_language(CXX ASM)
set(_TARGET ${APPNAME}-${BOARDNAME})

set(PROD_DIR ${CMAKE_SOURCE_DIR}/prod)
set(BOARD_DIR ${CMAKE_SOURCE_DIR}/board)

set(TARGET_COMPILE_DEFENITIONS -D${CMAKE_BUILD_TYPE} -D${CMAKE_BUILD_TYPE_UPPERCASE})
set(TARGET_INCLUDE_DIRECTORIES ${PROD_DIR}/inc)
set(TARGET_COMPILE_OPTIONS -fmessage-length=0 -ffunction-sections -fdata-sections -fno-common -fstack-usage -funsigned-char -fsingle-precision-constant)
set(TARGET_COMPILE_OPTIONS ${TARGET_COMPILE_OPTIONS} -Wall -Wextra -Wdouble-promotion -Wformat=2 -Wconversion -Wlogical-op -Wduplicated-cond) 
set(TARGET_COMPILE_OPTIONS ${TARGET_COMPILE_OPTIONS} -pipe -static)
set(TARGET_LINK_OPTIONS -Wl,-Map=${PROJECT_NAME}.map,--cref,--gc-sections)
set(TARGET_SOURCE_FILES )
set(TARGET_LINK_LIBRARIES)
set(TARGET_LINK_DIRECTORIES)

include("${CMAKE_TOOLCHAIN_FILE}")

include(${PROD_DIR}/prod.cmake)

add_executable("${_TARGET}" ${TARGET_SOURCE_FILES})
target_compile_definitions(${_TARGET} PRIVATE ${TARGET_COMPILE_DEFENITIONS})
target_include_directories(${_TARGET} PRIVATE ${TARGET_INCLUDE_DIRECTORIES})
target_compile_options(${_TARGET} PRIVATE ${TARGET_COMPILE_OPTIONS})
target_link_directories(${_TARGET} PRIVATE ${TARGET_LINK_DIRECTORIES})
target_link_options(${_TARGET} PRIVATE ${TARGET_LINK_OPTIONS})
target_link_libraries(${_TARGET} ${TARGET_LINK_LIBRARIES})

set_TARGET_properties(${_TARGET} PROPERTIES OUTPUT_NAME ${_TARGET}.elf)

add_custom_command(TARGET ${_TARGET} POST_BUILD 
	COMMAND ${CMAKE_OBJCOPY} --gap-fill 0xff -O ihex $<TARGET_FILE:${_TARGET}> ${_TARGET}.hex
	COMMAND ${CMAKE_OBJCOPY} --gap-fill 0xff -O binary $<TARGET_FILE:${_TARGET}> ${_TARGET}.bin
)
