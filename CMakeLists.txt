cmake_minimum_required(VERSION 3.15)
project(APM32F407IGT6_Template C ASM)

# Paths
set(SOURCE_ROOT ${CMAKE_SOURCE_DIR})

# Sources (ASM)
file(GLOB_RECURSE ASM_SOURCES
    ${SOURCE_ROOT}/Device/Source/*.S
)

# Sources (C)
file(GLOB_RECURSE C_SOURCES
    ${SOURCE_ROOT}/APM32F4xx_StdPeriphDriver/src/*.c
    ${SOURCE_ROOT}/Device/Source/*.c
    ${SOURCE_ROOT}/User/*.c    
)

# Headers
file(GLOB_RECURSE HEADERS
    ${SOURCE_ROOT}/APM32F4xx_StdPeriphDriver/inc/*.h
    ${SOURCE_ROOT}/CMSIS/Include/*.h
    ${SOURCE_ROOT}/Device/Include/*.h
    ${SOURCE_ROOT}/User/*.h
)

# Include directories
include_directories(
    APM32F4xx_StdPeriphDriver/inc
    CMSIS/Include
    Device/Include
    User
)

# Executable
add_executable(${PROJECT_NAME}.elf ${ASM_SOURCES} ${C_SOURCES} ${HEADERS})

# Compile definitions (macros)
target_compile_definitions(${PROJECT_NAME}.elf PRIVATE
    APM32F407xx
    DEBUG=DEBUG_USART1
)

# Target processor
set(TARGET_PROCESSOR
    -mcpu=cortex-m4
    -mthumb
)

# Optimization
set(OPTIMIZATION
    -O0
    -fmessage-length=0
    -fsigned-char
    -ffunction-sections
    -fdata-sections
)

# Warnings
set(WARNINGS
    -Wall
    -Wextra
)

# Debugging
set(DEBUGGING
    -g
)

# GNU Arm Cross Assembler Flags
set(ASSEMBLER_FLAGS
    "-x assembler-with-cpp"
)

# GNU Arm Cross C Compiler Flags
set(C_COMPILER_FLAGS
    -std=gnu17
)

# GNU Arm Cross C Linker
set(LINKER_FLAGS
    -Wl,--gc-sections,-Map=${PROJECT_NAME}.map,-u,_printf_float
    --specs=nano.specs
    --specs=nosys.specs
)

# Set assembly flags
set_source_files_properties(${ASM_SOURCES} PROPERTIES
    COMPILE_FLAGS "${ASSEMBLER_FLAGS}"
)

# Set C flags
set_source_files_properties(${C_SOURCES} PROPERTIES
    COMPILE_FLAGS "${C_COMPILER_FLAGS}"
)

# Common compiler flags
target_compile_options(${PROJECT_NAME}.elf PRIVATE
    ${TARGET_PROCESSOR}
    ${OPTIMIZATION}
    ${WARNINGS}
    ${DEBUGGING}
)

# Linker script
set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/Link/apm32f407xg_flash.ld)

# Linker flags
target_link_options(${PROJECT_NAME}.elf PRIVATE
    -T${LINKER_SCRIPT}
    ${TARGET_PROCESSOR}
    ${LINKER_FLAGS}
)

# GNU Arm Cross Create Flash Image
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex ${PROJECT_NAME}.elf ${PROJECT_NAME}.hex
    COMMENT "Generating HEX"
)

# GNU Arm Cross Print Size
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND ${CMAKE_SIZE} --format=berkeley ${PROJECT_NAME}.elf
    COMMENT "Print size"
)

# Object dump
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary "${PROJECT_NAME}.elf" "${PROJECT_NAME}.bin"
    COMMAND ${CMAKE_OBJDUMP} -D "${PROJECT_NAME}.elf" > "${PROJECT_NAME}.dump"
    COMMENT "Object dump"
)

# OpenOCD path
if(DEFINED ENV{OPENOCD_PATH})
    set(OPENOCD_PATH "$ENV{OPENOCD_PATH}")
else()
    set(OPENOCD_PATH "D:/Github/GeehySemi/Openocd/openocd-v0.12.0-rc2-i686-w64-mingw32.tar_wkl")
endif()

# Flash program
add_custom_target(prog
    COMMAND ${OPENOCD_PATH}/bin/openocd.exe
        -f ${OPENOCD_PATH}/share/openocd/scripts/interface/cmsis-dap.cfg
        -f ${OPENOCD_PATH}/share/openocd/scripts/target/apm32f4x.cfg
        -c "program ${PROJECT_NAME}.elf verify reset exit"
    DEPENDS ${PROJECT_NAME}.elf
    COMMENT "Flashing firmware via OpenOCD"
)
