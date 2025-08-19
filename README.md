# APM32F407xG_Template

CMake-based template for APM32F407xGxx MCU.

Created on APM32F4xx_SDK_V1.5.0 (30-04-2025).

## Software

* CMake 3.15 or later (https://cmake.org)
    * Ninja generator is recommended
* ARM none EABI toolchain (https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads)
    * For example: https://developer.arm.com/-/media/Files/downloads/gnu/14.3.rel1/binrel/arm-gnu-toolchain-14.3.rel1-mingw-w64-i686-arm-none-eabi.exe
* OpenOCD with APM32F4xx support (https://github.com/GeehySemi/Openocd)
* VS Code with the following extensions:
    * C/C++
    * CMake Tools
* GeehyProg for standalone programming (https://global.geehy.com/design/software)

## Hardware

* For OpenOCD (SWD) programming, any of:
    * DapLink CMSIS-DAP
    * LinkMini with DapLink firmware
    * LinkPlus with DapLink firmware
* For GeehyProg ISP programming:
    * Any USB-to-serial converter (USART)
    * Direct USB connection

To program with ISP, the chip must be in bootloader mode (pull BOOT0 high while resetting).

*NOTE:* There are other programming methods available, including GEEHY-LINK, APM32 PROG and other tools.

## Usage

Workflow is based on VS Code and CMake:

1. CMake toolchain is configured automatically through VS Code project settings (set `GCC_ARM_NONE_EABI_PATH` environment variable to customize path)
2. Configure CMake (command palette)
3. Build with CMake (*F7*) or rebuild with preliminary clean (*rebuild* task, may be bound to *Shift+F7*)
4. Connect a target board with DapLink programmer (SWD)
5. Program (CMake custom task, may be bound to *F8*)
