/*!
 * @file        qpm32f4xx_qspi.c
 *
 * @brief       This file contains all the functions for the QSPI peripheral
 *
 * @version     V1.0.1
 *
 * @date        2025-02-15
 *
 * @attention
 *
 *  Copyright (C) 2024-2025 Geehy Semiconductor
 *
 *  You may not use this file except in compliance with the
 *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
 *
 *  The program is only for reference, which is distributed in the hope
 *  that it will be useful and instructional for customers to develop
 *  their software. Unless required by applicable law or agreed to in
 *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
 *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
 *  and limitations under the License.
 */

/* Includes */
#include "apm32f4xx_qspi.h"
#include "apm32f4xx_rcm.h"

/** @addtogroup APM32F4xx_StdPeriphDriver
  @{
*/

#if defined (QSPI)

/** @addtogroup QSPI_Driver QSPI Driver
  @{
*/

/** @defgroup QSPI_Functions Functions
  @{
*/

/*!
 * @brief       Reset QSPI peripheral registers to their default values
 *
 * @param       None
 *
 * @retval      None
 */
void QSPI_Reset(void)
{
#if defined (APM32F411xx)
    RCM_EnableAHB2PeriphReset(RCM_AHB2_PERIPH_QSPI);
    RCM_DisableAHB2PeriphReset(RCM_AHB2_PERIPH_QSPI);
#else
    /* APM32F425xx, APM32F427xx */
    RCM_EnableAHB3PeriphReset(RCM_AHB3_PERIPH_QSPI);
    RCM_DisableAHB3PeriphReset(RCM_AHB3_PERIPH_QSPI);
#endif /* APM32F411xx */
}

/*!
 * @brief       Config the QSPI peripheral according to the specified parameters in the qspiConfig
 *
 * @param       qspiConfig: Pointer to a QSPI_Config_T structure that contains the configuration information
 *
 * @retval      None
 */
void QSPI_Config(QSPI_Config_T* qspiConfig)
{
#if defined (APM32F411xx)
    QSPI->CTRL1_B.CPHA = qspiConfig->clockPhase;
    QSPI->CTRL1_B.CPOL = qspiConfig->clockPolarity;
#endif /* APM32F411xx */
    QSPI->CTRL1_B.FRF = qspiConfig->frameFormat;
    QSPI->CTRL1_B.DFS = qspiConfig->dataFrameSize;;
    QSPI->CTRL1_B.SSTEN = qspiConfig->selectSlaveToggle;

    QSPI->BR = qspiConfig->clockDiv;
}

/*!
 * @brief       Fills each qspiConfig member with its default value
 *
 * @param       qspiConfig: Pointer to a QSPI_Config_T structure which will be initialized
 *
 * @retval      None
 */
void QSPI_ConfigStructInit(QSPI_Config_T* qspiConfig)
{
#if defined (APM32F411xx)
    qspiConfig->clockPhase = QSPI_CLKPHA_2EDGE;
    qspiConfig->clockPolarity = QSPI_CLKPOL_LOW;
#endif /* APM32F411xx */
    qspiConfig->clockDiv = 0;

    qspiConfig->frameFormat = QSPI_FRF_STANDARD;
    qspiConfig->dataFrameSize = QSPI_DFS_8BIT;
    qspiConfig->selectSlaveToggle = QSPI_SST_DISABLE;
}

/*!
 * @brief       Configs frame number
 *
 * @param       num: Configs a 16bit frame number
 *
 * @retval      None
 */
void QSPI_ConfigFrameNum(uint16_t num)
{
    QSPI->CTRL2_B.NDF = num;
}

/*!
 * @brief       Configs data frame size
 *
 * @param       dfs: Specifies the data frame size
 *                   The parameter can be one of following values:
 *                   @arg QSPI_DFS_4BIT  : Specifies data frame size to 4bit
 *                   @arg QSPI_DFS_5BIT  : Specifies data frame size to 5bit
 *                   @arg QSPI_DFS_6BIT  : Specifies data frame size to 6bit
 *                   @arg QSPI_DFS_7BIT  : Specifies data frame size to 7bit
 *                   @arg QSPI_DFS_8BIT  : Specifies data frame size to 8bit
 *                   @arg QSPI_DFS_9BIT  : Specifies data frame size to 9bit
 *                   @arg QSPI_DFS_10BIT : Specifies data frame size to 10bit
 *                   @arg QSPI_DFS_11BIT : Specifies data frame size to 11bit
 *                   @arg QSPI_DFS_12BIT : Specifies data frame size to 12bit
 *                   @arg QSPI_DFS_13BIT : Specifies data frame size to 13bit
 *                   @arg QSPI_DFS_14BIT : Specifies data frame size to 14bit
 *                   @arg QSPI_DFS_15BIT : Specifies data frame size to 15bit
 *                   @arg QSPI_DFS_16BIT : Specifies data frame size to 16bit
 *                   @arg QSPI_DFS_17BIT : Specifies data frame size to 17bit
 *                   @arg QSPI_DFS_18BIT : Specifies data frame size to 18bit
 *                   @arg QSPI_DFS_19BIT : Specifies data frame size to 19bit
 *                   @arg QSPI_DFS_20BIT : Specifies data frame size to 20bit
 *                   @arg QSPI_DFS_21BIT : Specifies data frame size to 21bit
 *                   @arg QSPI_DFS_22BIT : Specifies data frame size to 22bit
 *                   @arg QSPI_DFS_23BIT : Specifies data frame size to 23bit
 *                   @arg QSPI_DFS_24BIT : Specifies data frame size to 24bit
 *                   @arg QSPI_DFS_25BIT : Specifies data frame size to 25bit
 *                   @arg QSPI_DFS_26BIT : Specifies data frame size to 26bit
 *                   @arg QSPI_DFS_27BIT : Specifies data frame size to 27bit
 *                   @arg QSPI_DFS_28BIT : Specifies data frame size to 28bit
 *                   @arg QSPI_DFS_29BIT : Specifies data frame size to 29bit
 *                   @arg QSPI_DFS_30BIT : Specifies data frame size to 30bit
 *                   @arg QSPI_DFS_31BIT : Specifies data frame size to 31bit
 *                   @arg QSPI_DFS_32BIT : Specifies data frame size to 32bit
 *
 * @retval      None
 */
void QSPI_ConfigDataFrameSize(QSPI_DFS_T dfs)
{
    QSPI->CTRL1_B.DFS = dfs;
}

/*!
 * @brief       Configs frame format
 *
 * @param       frameFormat
 *
 * @retval      None
 */
void QSPI_ConfigFrameFormat(QSPI_FRF_T frameFormat)
{
    QSPI->CTRL1_B.FRF = frameFormat;
}

/*!
 * @brief       Enable QSPI
 *
 * @param       None
 *
 * @retval      None
 */
void QSPI_Enable(void)
{
    QSPI->SSIEN_B.EN = BIT_SET;
}

/*!
 * @brief       Disable QSPI
 *
 * @param       None
 *
 * @retval      None
 */
void QSPI_Disable(void)
{
    QSPI->SSIEN_B.EN = BIT_RESET;
}

#if defined (APM32F425xx) || defined (APM32F427xx)

/*!
 * @brief       Enable QSPI access for external memory address space
 *
 * @param       None
 * 
 * @retval      None
 */
void QSPI_EnableExtMemAccess(void)
{
    QSPI->SWITCH_B.SWITCH = BIT_SET;
}

/*!
 * @brief       Disable QSPI access for external memory address space
 *
 * @param       None
 * 
 * @retval      None
 */
void QSPI_DisableExtMemAccess(void)
{
    QSPI->SWITCH_B.SWITCH = BIT_RESET;
}

/*!
 * @brief       Configs QSPI external memory access format
 *
 * @param       format: Specifies the external memory access format
 *                      The parameter can be one of following values:
 *                      @arg QSPI_MEM_ACCESS_BIG_ENDIAN    : Big endian
 *                      @arg QSPI_MEM_ACCESS_LITTLE_ENDIAN : Little endian
 *
 * @retval      None
 */
void QSPI_ConfigExtMemAccessFormat(QSPI_MEM_ACCESS_FORMAT_T format)
{
    QSPI->SWITCH_B.LITTLE_ENDIAN_EN = format;
}

/*!
 * @brief       Configs INCR transfer code
 *
 * @param       code: Specifies the INCR transfer code
 * 
 * @retval      None
 */
void QSPI_ConfigINCRTransferCode(uint16_t code)
{
    QSPI->XIP_INCR_INST_B.INCR_INST = code;
}

/*!
 * @brief       Configs WRAP transfer code
 *
 * @param       code: Specifies the WRAP transfer code
 * 
 * @retval      None
 */
void QSPI_ConfigWRAPTransferCode(uint16_t code)
{
    QSPI->XIP_WRAP_INST_B.WRAP_INST = code;
}

/*!
 * @brief       Configs XIP frame format
 *
 * @param       format: Specifies the XIP frame format
 *                    The parameter can be one of following values:
 *                    @arg QSPI_XIP_FRAME_DUAL : Dual XIP frame
 *                    @arg QSPI_XIP_FRAME_QUAD : Quad XIP frame
 *
 * @retval      None
 */
void QSPI_ConfigXIPFrameFormat(QSPI_XIP_FRF_T format)
{
    QSPI->XIP_CTRL_B.FRF = format;
}

/*!
 * @brief       Configs XIP instruction and address type
 *
 * @param       type: Specifies the XIP instruction and address type
 *                    The parameter can be one of following values:
 *                    @arg QSPI_XIP_INST_ADDR_TYPE_STANDARD : Tx instruction in standard SPI mode,
 *                                                          Tx address in standard SPI mode
 *                    @arg QSPI_XIP_INST_TYPE_STANDARD      : Tx instruction in standard SPI mode,
 *                                                          Tx address in mode of SPI_FRF
 *                    @arg QSPI_XIP_INST_ADDR_TYPE_FRF      : Tx instruction in mode of SPI_FRF,
 *                                                          Tx address in mode of SPI_FRF
 *
 * @retval      None
 */
void QSPI_ConfigXIPInstAddrType(QSPI_XIP_INST_ADDR_TYPE_T type)
{
    QSPI->XIP_CTRL_B.TRANS_TYPE = type;
}

/*!
 * @brief       Configs XIP address length
 *
 * @param       len: Specifies the XIP address length
 *                   The parameter can be one of following values:
 *                   @arg QSPI_XIP_ADDR_LEN_0     : no address
 *                   @arg QSPI_XIP_ADDR_LEN_4BIT  : 4-bit address length
 *                   @arg QSPI_XIP_ADDR_LEN_8BIT, : 8-bit address length
 *                   @arg QSPI_XIP_ADDR_LEN_12BIT : 12-bit address length
 *                   @arg QSPI_XIP_ADDR_LEN_16BIT : 16-bit address length
 *                   @arg QSPI_XIP_ADDR_LEN_20BIT : 20-bit address length
 *                   @arg QSPI_XIP_ADDR_LEN_24BIT : 24-bit address length
 *                   @arg QSPI_XIP_ADDR_LEN_28BIT : 28-bit address length
 *                   @arg QSPI_XIP_ADDR_LEN_32BIT : 32-bit address length
 *                   @arg QSPI_XIP_ADDR_LEN_36BIT : 36-bit address length
 *                   @arg QSPI_XIP_ADDR_LEN_40BIT : 40-bit address length
 *                   @arg QSPI_XIP_ADDR_LEN_44BIT : 44-bit address length
 *                   @arg QSPI_XIP_ADDR_LEN_48BIT : 48-bit address length
 *                   @arg QSPI_XIP_ADDR_LEN_52BIT : 52-bit address length
 *                   @arg QSPI_XIP_ADDR_LEN_56BIT : 56-bit address length
 *                   @arg QSPI_XIP_ADDR_LEN_60BIT : 60-bit address length
 *
 * @retval      None
 */
void QSPI_ConfigXIPAddrLen(QSPI_XIP_ADDR_LEN_T len)
{
    QSPI->XIP_CTRL_B.ADDR_L = len;
}

/*!
 * @brief       Configs XIP instruction length
 *
 * @param       len: Specifies the XIP instruction length
 *                   The parameter can be one of following values:
 *                   @arg QSPI_XIP_INST_LEN_0     : no instruction
 *                   @arg QSPI_XIP_INST_LEN_4BIT  : 4-bit instruction
 *                   @arg QSPI_XIP_INST_LEN_8BIT  : 8-bit instruction
 *                   @arg QSPI_XIP_INST_LEN_16BIT : 16-bit instruction
 *
 * @retval      None
 */
void QSPI_ConfigXIPInstLen(QSPI_XIP_INST_LEN_T len)
{
    QSPI->XIP_CTRL_B.INST_L = len;
}

/*!
 * @brief       Configs XIP wait cycle number
 *
 * @param       cycle: Specifies the wait cycle number with a 5-bit value
 *
 * @retval      None
 */
void QSPI_ConfigXIPWaitCycle(uint8_t cycle)
{
    QSPI->XIP_CTRL_B.WAIT_CYCLES = cycle;
}

/*!
 * @brief       Enable XIP instruction
 *
 * @param       None
 *
 * @retval      None
 */
void QSPI_EnableXIPInst(void)
{
    QSPI->XIP_CTRL_B.INST_EN = BIT_SET;
}

/*!
 * @brief       Disable XIP instruction
 *
 * @param       None
 *
 * @retval      None
 */
void QSPI_DisableXIPInst(void)
{
    QSPI->XIP_CTRL_B.INST_EN = BIT_RESET;
}

/*!
 * @brief       Enable XIP continuous mode
 *
 * @param       None
 *
 * @retval      None
 */
void QSPI_EnableXIPContinuousMode(void)
{
    QSPI->XIP_CTRL_B.CONT_XFER_EN = BIT_SET;
}

/*!
 * @brief       Disable XIP continuous mode
 *
 * @param       None
 *
 * @retval      None
 */
void QSPI_DisableXIPContinuousMode(void)
{
    QSPI->XIP_CTRL_B.CONT_XFER_EN = BIT_RESET;
}

/*!
 * @brief       Enable XIP prefetch
 *
 * @param       None
 *
 * @retval      None
 */
void QSPI_EnableXIPPreFetch(void)
{
    QSPI->XIP_CTRL_B.XIP_PREFETCH_EN = BIT_SET;
}

/*!
 * @brief       Disable XIP prefetch
 *
 * @param       None
 *
 * @retval      None
 */
void QSPI_DisableXIPPreFetch(void)
{
    QSPI->XIP_CTRL_B.XIP_PREFETCH_EN = BIT_RESET;
}

/*!
 * @brief       Enable XIP
 *
 * @param       None
 *
 * @retval      None
 */
void QSPI_EnableXIP(void)
{
    QSPI->XIP_EN_B.XIP_EN = BIT_SET;
}

/*!
 * @brief       Disable XIP
 *
 * @param       None
 *
 * @retval      None
 */
void QSPI_DisableXIP(void)
{
    QSPI->XIP_EN_B.XIP_EN = BIT_RESET;
}

#endif /* APM32F425xx || APM32F427xx */

/*!
 * @brief       Read Tx FIFO number of data
 *
 * @param       None
 *
 * @retval      None
 */
uint8_t QSPI_ReadTxFifoDataNum(void)
{
    return (uint8_t)QSPI->TFL_B.TFL;
}

/*!
 * @brief       Read Rx FIFO number of data
 *
 * @param       None
 *
 * @retval      Returns Rx FIFO number of data
 */
uint8_t QSPI_ReadRxFifoDataNum(void)
{
    return (uint8_t)QSPI->RFL_B.RFL;
}

/*!
 * @brief       Configs rx FIFO threshold
 *
 * @param       threshold: Speicifes rx FIFO threshold with a 3bit value
 *
 * @retval      None
 */
void QSPI_ConfigRxFifoThreshold(uint8_t threshold)
{
    QSPI->RFTL_B.RFT = threshold;
}

/*!
 * @brief       Congfigs Tx FIFO threshold
 *
 * @param       threshold: Speicifes Tx FIFO threshold with a 3bit value
 *
 * @retval      None
 */
void QSPI_ConfigTxFifoThreshold(uint8_t threshold)
{
    QSPI->TFTL_B.TFTH = threshold;
}

/*!
 * @brief       Congfigs Tx FIFO empty threshold
 *
 * @param       threshold: Speicifes Tx FIFO empty threshold with a 3bit value
 *
 * @retval      None
 */
void QSPI_ConfigTxFifoEmptyThreshold(uint8_t threshold)
{
    QSPI->TFTL_B.TFT = threshold;
}

/*!
 * @brief       Configs RX sample edge
 *
 * @param       rse: Specifies the sample edge
 *                   The parameter can be one of following values:
 *                   @arg QSPI_RSE_RISING : rising edge sample
 *                   @arg QSPI_RSE_FALLING: falling edge sample
 *
 * @retval      None
 */
void QSPI_ConfigRxSampleEdge(QSPI_RSE_T rse)
{
    QSPI->RSD_B.RSE = rse;
}

/*!
 * @brief       Set RX sample delay
 *
 * @param       delay: Specifies the sample delay with a 8-bit value
 *
 * @retval      None
 */
void QSPI_ConfigRxSampleDelay(uint8_t delay)
{
    QSPI->RSD_B.RSD = delay;
}

/*!
 * @brief       Clock stretch enable
 *
 * @param       None
 *
 * @retval      None
 */
void QSPI_EnableClockStretch(void)
{
    QSPI->CTRL3_B.CSEN = BIT_SET;
}

/*!
 * @brief       Clock stretch disable
 *
 * @param       None
 *
 * @retval      None
 */
void QSPI_DisableClockStretch(void)
{
    QSPI->CTRL3_B.CSEN = BIT_RESET;
}

/*!
 * @brief       Configs instruction length
 *
 * @param       len: Specifies the length of instruction
 *                   The parameter can be one of following values:
 *                   @arg QSPI_INST_LEN_0     : no instruction
 *                   @arg QSPI_INST_LEN_4BIT  : 4-bit instruction
 *                   @arg QSPI_INST_LEN_8BIT  : 8-bit instruction
 *                   @arg QSPI_INST_LEN_16BIT : 16-bit instruction
 *
 * @retval      None
 */
void QSPI_ConfigInstLen(QSPI_INST_LEN_T len)
{
    QSPI->CTRL3_B.INSLEN = len;
}

/*!
 * @brief       Configs address length
 *
 * @param       len: Specifies the address length
 *                   The parameter can be one of following values:
 *                   @arg QSPI_ADDR_LEN_0     : no address
 *                   @arg QSPI_ADDR_LEN_4BIT  : 4-bit address length
 *                   @arg QSPI_ADDR_LEN_8BIT, : 8-bit address length
 *                   @arg QSPI_ADDR_LEN_12BIT : 12-bit address length
 *                   @arg QSPI_ADDR_LEN_16BIT : 16-bit address length
 *                   @arg QSPI_ADDR_LEN_20BIT : 20-bit address length
 *                   @arg QSPI_ADDR_LEN_24BIT : 24-bit address length
 *                   @arg QSPI_ADDR_LEN_28BIT : 28-bit address length
 *                   @arg QSPI_ADDR_LEN_32BIT : 32-bit address length
 *                   @arg QSPI_ADDR_LEN_36BIT : 36-bit address length
 *                   @arg QSPI_ADDR_LEN_40BIT : 40-bit address length
 *                   @arg QSPI_ADDR_LEN_44BIT : 44-bit address length
 *                   @arg QSPI_ADDR_LEN_48BIT : 48-bit address length
 *                   @arg QSPI_ADDR_LEN_52BIT : 52-bit address length
 *                   @arg QSPI_ADDR_LEN_56BIT : 56-bit address length
 *                   @arg QSPI_ADDR_LEN_60BIT : 60-bit address length
 *
 * @retval      None
 */
void QSPI_ConfigAddrLen(QSPI_ADDR_LEN_T len)
{
    QSPI->CTRL3_B.ADDRLEN = len;
}

/*!
 * @brief       Configs instruction and address type
 *
 * @param       type: Specifies the instruction and address type
 *                    The parameter can be one of following values:
 *                    @arg QSPI_INST_ADDR_TYPE_STANDARD : Tx instruction in standard SPI mode,
 *                                                        Tx address in standard SPI mode
 *                    @arg QSPI_INST_TYPE_STANDARD      : Tx instruction in standard SPI mode,
 *                                                        Tx address in mode of SPI_FRF
 *                    @arg QSPI_INST_ADDR_TYPE_FRF      : Tx instruction in mode of SPI_FRF,
 *                                                        Tx address in mode of SPI_FRF
 *
 * @retval      None
 */
void QSPI_ConfigInstAddrType(QSPI_INST_ADDR_TYPE_T type)
{
    QSPI->CTRL3_B.IAT = type;
}

/*!
 * @brief       Configs wait cycle number
 *
 * @param       cycle: Specifies the wait cycle number with a 5-bit value
 *
 * @retval      None
 */
void QSPI_ConfigWaitCycle(uint8_t cycle)
{
    QSPI->CTRL3_B.WAITCYC = cycle;
}

#if defined (APM32F411xx)
/*!
 * @brief       Open QSPI GPIO
 *
 * @param       None
 *
 * @retval      None
 */
void QSPI_OpenIO(void)
{
    QSPI->IOSW_B.IOSW = BIT_SET;
}

/*!
 * @brief       Close QSPI GPIO
 *
 * @param       None
 *
 * @retval      None
 */
void QSPI_CloseIO(void)
{
    QSPI->IOSW_B.IOSW = BIT_RESET;
}
#endif /* APM32F411xx */

/*!
 * @brief       Set transmission mode
 *
 * @param       mode: Specifies the transmission mode
 *                    The parameter can be one of following values:
 *                    @arg QSPI_TRANS_MODE_TX_RX       : TX and RX mode
 *                    @arg QSPI_TRANS_MODE_TX          : TX mode only
 *                    @arg QSPI_TRANS_MODE_RX          : RX mode only
 *                    @arg QSPI_TRANS_MODE_EEPROM_READ : EEPROM read mode
 *
 * @retval      None
 */
void QSPI_ConfigTansMode(QSPI_TRANS_MODE_T mode)
{
    QSPI->CTRL1_B.TXMODE = mode;
}

/*!
 * @brief     Enables the QSPI DMA interface
 *
 * @param     dmaReq:  Specifies the DMA request
 *                     This parameter can be one of the following values:
 *                     @arg QSPI_DMA_TX    : QSPI DMA receive request
 *                     @arg QSPI_DMA_RX    : QSPI DMA transmit request
 *                     @arg QSPI_DMA_TX_RX : QSPI DMA transmit/receive request
 *
 * @retval    None
 */
void QSPI_EnableDMA(QSPI_DMA_T dmaReq)
{
    QSPI->DMACTRL |= dmaReq;
}

/*!
 * @brief     Enables the QSPI DMA interface
 *
 * @param     dmaReq:  Specifies the DMA request
 *                     This parameter can be one of the following values:
 *                     @arg QSPI_DMA_TX    : QSPI DMA receive request
 *                     @arg QSPI_DMA_RX    : QSPI DMA transmit request
 *                     @arg QSPI_DMA_TX_RX : QSPI DMA transmit/receive request
 *
 * @retval    None
 */
void QSPI_DisableDMA(QSPI_DMA_T dmaReq)
{
    QSPI->DMACTRL &= (uint32_t)~dmaReq;
}

/*!
 * @brief       Configs DMA transmit data level
 *
 * @param       level: Speicifes transmit data level with a 3bit value
 *
 * @retval      None
 */
void QSPI_ConfigDMATDL(uint8_t level)
{
    QSPI->DMATDL = level;
}

/*!
 * @brief       Read DMA transmit data level
 *
 * @param       None
 *
 * @retval      level: Speicifes transmit data level with a 3bit value
 */
uint8_t QSPI_ReadDMATDL(void)
{
    return (uint8_t)QSPI->DMATDL;
}

/*!
 * @brief       Configs DMA receive data level
 *
 * @param       level: Speicifes receive data level with a 3bit value
 *
 * @retval      None
 */
void QSPI_ConfigDMARDL(uint8_t level)
{
    QSPI->DMARDL = (uint32_t)level;
}

/*!
 * @brief       Read DMA receive data level
 *
 * @param       None
 *
 * @retval      level: Speicifes receive data level with a 3bit value
 */
uint8_t QSPI_ReadDMARDL(void)
{
    return (uint8_t)QSPI->DMARDL;
}

/*!
 * @brief       Transmit data
 *
 * @param       data: Data to be transmited
 *
 * @retval      None
 */
void QSPI_TxData(uint32_t data)
{
    QSPI->DATA = data;
}

/*!
 * @brief       Returns the most recent received data
 *
 * @param       None
 *
 * @retval      The received data
 */
uint32_t QSPI_RxData(void)
{
    return (uint32_t)QSPI->DATA;
}

/*!
 * @brief       Enable Slave
 *
 * @param       None
 *
 * @retval      None
 */
void QSPI_EnableSlave(void)
{
    QSPI->SLAEN_B.SLAEN = BIT_SET;
}

/*!
 * @brief       Disable slave
 *
 * @param       None
 *
 * @retval      None
 */
void QSPI_DisableSlave(void)
{
    QSPI->SLAEN_B.SLAEN = BIT_RESET;
}

/*!
 * @brief       Enable the specified QSPI interrupts
 *
 * @param       interrupt:  Specifies the QSPI interrupt sources
 *                          The parameter can be combination of following values:
 *                          @arg QSPI_INT_TFE:      TX FIFO empty interrupt
 *                          @arg QSPI_INT_TFO:      TX FIFO overflow interrupt
 *                          @arg QSPI_INT_RFU:      RX FIFO underflow interrupt
 *                          @arg QSPI_INT_RFO:      RX FIFO overflow interrupt
 *                          @arg QSPI_INT_RFF:      RX FIFO full interrupt
 *                          @arg QSPI_INT_MST:      Master interrupt (*)
 *
 * @retval      None
 */
void QSPI_EnableInterrupt(uint32_t interrupt)
{
    QSPI->INTEN |= interrupt;
}

/*!
 * @brief       Disable the specified QSPI interrupts
 *
 * @param       interrupt:  Specifies the QSPI interrupt sources
 *                          The parameter can be combination of following values:
 *                          @arg QSPI_INT_TFE:      TX FIFO empty interrupt
 *                          @arg QSPI_INT_TFO:      TX FIFO overflow interrupt
 *                          @arg QSPI_INT_RFU:      RX FIFO underflow interrupt
 *                          @arg QSPI_INT_RFO:      RX FIFO overflow interrupt
 *                          @arg QSPI_INT_RFF:      RX FIFO full interrupt
 *                          @arg QSPI_INT_MST:      Master interrupt (*)
 *
 * @retval      None
 */
void QSPI_DisableInterrupt(uint32_t interrupt)
{
    QSPI->INTEN &= (uint32_t)~interrupt;
}

/*!
 * @brief       Read specified QSPI flag
 *
 * @param       flag:   Specifies the flag to be checked
 *                      The parameter can be one of following values:
 *                      @arg QSPI_FLAG_BUSY:    Busy flag
 *                      @arg QSPI_FLAG_TFNF:    TX FIFO not full flag
 *                      @arg QSPI_FLAG_TFE:     TX FIFO empty flag
 *                      @arg QSPI_FLAG_RFNE:    RX FIFO not empty flag
 *                      @arg QSPI_FLAG_RFF:     RX FIFO full flag
 *                      @arg QSPI_FLAG_DCE:     Data collision error (*)
 *
 * @retval      The new state of flag (SET or RESET)
 */
uint8_t QSPI_ReadStatusFlag(QSPI_FLAG_T flag)
{
    uint8_t ret = RESET;

    ret = QSPI->STS & flag ? SET : RESET;

    return ret;
}

/*!
 * @brief       Clear specified QSPI flag
 *
 * @param       None
 *
 * @retval      None
 *
 * @note        This funtion only clear Data collision error flag(QSPI_FLAG_DCE)
 */
void QSPI_ClearStatusFlag(void)
{
    volatile uint32_t dummy = 0;

    dummy = QSPI->STS;

    (void)dummy;
}

/*!
 * @brief       Read specified QSPI interrupt flag
 *
 * @param       flag:   Specifies the interrupt flag to be checked
 *                      The parameter can be one of following values:
 *                      @arg QSPI_INT_FLAG_TFE:     TX FIFO empty interrupt flag
 *                      @arg QSPI_INT_FLAG_TFO:     TX FIFO overflow interrupt flag
 *                      @arg QSPI_INT_FLAG_RFU:     RX FIFO underflow interrupt flag
 *                      @arg QSPI_INT_FLAG_RFO:     RX FIFO overflow interrupt flag
 *                      @arg QSPI_INT_FLAG_RFF:     RX FIFO full interrupt flag
 *                      @arg QSPI_INT_FLAG_MST:     Master interrupt flag (*)
 *
 * @retval      The new state of flag (SET or RESET)
 */
uint8_t QSPI_ReadIntFlag(QSPI_INT_FLAG_T flag)
{
    uint8_t ret = RESET;

    ret = QSPI->ISTS & flag ? SET : RESET;

    return ret;
}

/*!
 * @brief       Clear specified QSPI interrupt flag
 *
 * @param       flag:   Specifies the interrupt flag to be checked
 *                      The parameter can be one of following values:
 *                      @arg QSPI_INT_FLAG_TFO:     TX FIFO overflow interrupt flag
 *                      @arg QSPI_INT_FLAG_RFU:     RX FIFO underflow interrupt flag
 *                      @arg QSPI_INT_FLAG_RFO:     RX FIFO overflow interrupt flag
 *                      @arg QSPI_INT_FLAG_MST:     Master interrupt flag (*)
 *
 * @retval      None
 */
void QSPI_ClearIntFlag(uint32_t flag)
{
    volatile uint32_t dummy = 0;

    if (flag & QSPI_INT_FLAG_TFO)
    {
        dummy = QSPI->TFOIC;
    }
    else if (flag & QSPI_INT_FLAG_RFO)
    {
        dummy = QSPI->RFOIC;
    }
    else if (flag & QSPI_INT_FLAG_RFU)
    {
        dummy = QSPI->RFUIC;
    }
#if defined (APM32F411xx)
    else if (flag & QSPI_INT_FLAG_MST)
    {
        dummy = QSPI->MIC;
    }
#endif /* APM32F411xx */
    else
    {
        (void)dummy;
    }
}

/**@} end of group QSPI_Functions*/
/**@} end of group QSPI_Driver */

#endif /* QSPI */

/**@} end of group APM32F4xx_StdPeriphDriver*/

