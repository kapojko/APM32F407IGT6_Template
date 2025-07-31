#include "apm32f4xx_conf.h"
#include "Debug.h"

#ifdef DEBUG

#if DEBUG == DEBUG_USART1
#define DEBUG_USART USART1
#endif

void DebugInit(void) {
#if DEBUG == DEBUG_USART1
    /* Enable GPIO clock */
    RCM_EnableAHB1PeriphClock(RCM_AHB1_PERIPH_GPIOA);

    /* Enable USART clock */
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_USART1);

    GPIO_Config_T GPIO_configStruct;
    GPIO_ConfigStructInit(&GPIO_configStruct);

    /* Connect PXx to USARTx_Tx */
    GPIO_ConfigPinAF(GPIOA, GPIO_PIN_SOURCE_9, GPIO_AF_USART1);

    /* Connect PXx to USARTx_Rx */
    GPIO_ConfigPinAF(GPIOA, GPIO_PIN_SOURCE_10, GPIO_AF_USART1);

    /* Configure USART Tx as alternate function push-pull */
    GPIO_configStruct.mode = GPIO_MODE_AF;
    GPIO_configStruct.pin = GPIO_PIN_9;
    GPIO_configStruct.speed = GPIO_SPEED_50MHz;
    GPIO_Config(GPIOA, &GPIO_configStruct);

    /* Configure USART Rx as input floating */
    GPIO_configStruct.mode = GPIO_MODE_AF;
    GPIO_configStruct.pin = GPIO_PIN_10;
    GPIO_Config(GPIOA, &GPIO_configStruct);

    /* USART configuration */
    USART_Config_T usartConfig;
    usartConfig.baudRate = 115200;
    usartConfig.hardwareFlow = USART_HARDWARE_FLOW_NONE;
    usartConfig.mode = USART_MODE_TX;
    usartConfig.parity = USART_PARITY_NONE;
    usartConfig.stopBits = USART_STOP_BIT_1;
    usartConfig.wordLength = USART_WORD_LEN_8B;
    USART_Config(USART1, &usartConfig);

    /* Enable USART */
    USART_Enable(USART1);
#endif
}

#if defined (__CC_ARM) || defined (__ICCARM__) || (defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050))

/*!
* @brief       Redirect C Library function printf to serial port.
*              After Redirection, you can use printf function.
*
* @param       ch:  The characters that need to be send.
*
* @param       *f:  pointer to a FILE that can recording all information
*              needed to control a stream
*
* @retval      The characters that need to be send.
*
* @note
*/
int fputc(int ch, FILE* f)
{
    /* send a byte of data to the serial port */
    USART_TxData(DEBUG_USART, (uint8_t)ch);

    /* wait for the data to be send  */
    while (USART_ReadStatusFlag(DEBUG_USART, USART_FLAG_TXBE) == RESET);

    return (ch);
}

#elif defined (__GNUC__)

/*!
* @brief       Redirect C Library function printf to serial port.
*              After Redirection, you can use printf function.
*
* @param       ch:  The characters that need to be send.
*
* @retval      The characters that need to be send.
*
* @note
*/
int __io_putchar(int ch)
{
    /* send a byte of data to the serial port */
    USART_TxData(DEBUG_USART, ch);

    /* wait for the data to be send  */
    while (USART_ReadStatusFlag(DEBUG_USART, USART_FLAG_TXBE) == RESET);

    return ch;
}

/*!
* @brief       Redirect C Library function printf to serial port.
*              After Redirection, you can use printf function.
*
* @param       file:  Meaningless in this function.
*
* @param       *ptr:  Buffer pointer for data to be sent.
*
* @param       len:  Length of data to be sent.
*
* @retval      The characters that need to be send.
*
* @note
*/
int _write(int file, char* ptr, int len)
{
    int i;

    UNUSED(file);

    for (i = 0; i < len; i++)
    {
        __io_putchar(*ptr++);
    }

    return len;
}

int _close(int file) { (void)file; return -1; }
int _fstat(int file, void *st) { (void)file; (void)st; return 0; }
int _isatty(int file) { (void)file; return 1; }
int _lseek(int file, int offset, int whence) { (void)file; (void)offset; (void)whence; return 0; }
int _read(int file, char *ptr, int len) { (void)file; (void)ptr; (void)len; return 0; }
int _getpid(void) { return 1; }
int _kill(int pid, int sig) { (void)pid; (void)sig; return -1; }

#else
#warning Not supported compiler type
#endif

#endif
