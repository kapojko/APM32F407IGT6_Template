#ifndef DEBUG_H
#define DEBUG_H

#define DEBUG_USART1 1
#define DEBUG_USART2 2
#define DEBUG_USART3 3

#ifdef DEBUG
#include <stdio.h>

void DebugInit(void);

#define PRINT(...) printf(__VA_ARGS__)
#else
#define PRINT(...)
#endif

#endif // DEBUG_H
