/*!
 * @file        apm32f4xx_usb_device.h
 *
 * @brief       USB device function handle
 *
 * @version     V1.0.4
 *
 * @date        2025-02-15
 *
 * @attention
 *
 *  Copyright (C) 2023-2025 Geehy Semiconductor
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

/* Define to prevent recursive inclusion */
#ifndef __APM32F4XX_USB_DEVICE_H
#define __APM32F4XX_USB_DEVICE_H

#ifdef __cplusplus
  extern "C" {
#endif

/* Includes */
#include "apm32f4xx.h"
#include "apm32f4xx_usb.h"
#include "apm32f4xx_eint.h"

/** @addtogroup APM32F4xx_StdPeriphDriver
  @{
*/

#if defined (USB_OTG_FS) || defined (USB_OTG_FS2) || defined (USB_OTG_HS)

/** @addtogroup USB_Device_Driver USB Device Driver
  @{
*/

/** @defgroup USB_Device_Macros Macros
  @{
*/

/* Out endpoint number */
#define USBD_OUT_EP_MAX_NUM                     8

/* In endpoint number */
#define USBD_IN_EP_MAX_NUM                      8

#define TEST_J                                 1U
#define TEST_K                                 2U
#define TEST_SE0_NAK                           3U
#define TEST_PACKET                            4U
#define TEST_FORCE_EN                          5U

/**@} end of group USB_Device_Macros*/

/** @defgroup USB_Device_Enumerates Enumerates
  @{
  */
/**
 * @brief   USB speed channel
 */
typedef enum
{
    USBD_SPEED_CH_FS,
    USBD_SPEED_CH_HS,
} USBD_SPEED_CH_T;
/**@} end of group USB_Device_Enumerates*/

/** @defgroup USB_Device_Structures Structures
  @{
*/

/**
 * @brief USB OTG device FIFO status
 */
typedef struct
{
    union
    {
        __IO uint32_t FIFO_STATUS;

        struct
        {
            __IO uint32_t epNum         : 4;
            __IO uint32_t byteCount     : 11;
            __IO uint32_t dataPid       : 2;
            __IO uint32_t packetStatus  : 4;
            __IO uint32_t frameNumber   : 4;
        } FIFO_STATUS_B;
    };
} USBD_FIFO_STA_T;

/**
 * @brief USB OTG device handle
 */
typedef struct
{
    USB_OTG_GLOBAL_T*           usbGlobal;
    USB_OTG_DEVICE_T*           usbDevice;
    USB_OTG_FIFO_T*             usbFifo;
    USB_OTG_PWRCLK_T*           usbPower;
    USB_OTG_CFG_T               usbCfg;

    USB_OTG_ENDPOINT_INFO_T     epIN[16];
    USB_OTG_ENDPOINT_INFO_T     epOUT[16];
    uint32_t                    setup[12];
    __IO uint8_t                address;

    void*                       dataPoint;
} USBD_HANDLE_T;

/**@} end of group USB_Device_Structures*/

/** @defgroup USB_Device_Functions Functions
  @{
*/

#define USB_OTG_FS_WAKEUP_EINT_LINE             EINT_LINE_18
#define USBD_OTG_FS_WAKEUP_EINT_ENABLE_IT()     EINT->IMASK |= USB_OTG_FS_WAKEUP_EINT_LINE
#define USBD_OTG_FS_WAKEUP_EINT_DISABLE_IT()    EINT->IMASK &= ~(USB_OTG_FS_WAKEUP_EINT_LINE)
#define USBD_OTG_FS_WAKEUP_EINT_GET_FLAG()      EINT->IPEND & (USB_OTG_FS_WAKEUP_EINT_LINE)
#define USBD_OTG_FS_WAKEUP_EINT_CLEAR_FLAG()    EINT->IPEND = USB_OTG_FS_WAKEUP_EINT_LINE

#define USBD_OTG_FS_WAKEUP_EINT_ENABLE_RISING_EDGE() \
                        do { \
                             EINT->FTEN &= ~(USB_OTG_FS_WAKEUP_EINT_LINE); \
                             EINT->RTEN |= USB_OTG_FS_WAKEUP_EINT_LINE; \
                           } while(0U)

#if defined (USB_OTG_FS2)
#define USB_OTG_FS2_WAKEUP_EINT_LINE            EINT_LINE_20
#define USBD_OTG_FS2_WAKEUP_EINT_ENABLE_IT()    EINT->IMASK |= USB_OTG_FS2_WAKEUP_EINT_LINE
#define USBD_OTG_FS2_WAKEUP_EINT_DISABLE_IT()   EINT->IMASK &= ~(USB_OTG_FS2_WAKEUP_EINT_LINE)
#define USBD_OTG_FS2_WAKEUP_EINT_GET_FLAG()     EINT->IPEND & (USB_OTG_FS2_WAKEUP_EINT_LINE)
#define USBD_OTG_FS2_WAKEUP_EINT_CLEAR_FLAG()   EINT->IPEND = USB_OTG_FS2_WAKEUP_EINT_LINE

#define USBD_OTG_FS2_WAKEUP_EINT_ENABLE_RISING_EDGE() \
                        do { \
                             EINT->FTEN &= ~(USB_OTG_FS2_WAKEUP_EINT_LINE); \
                             EINT->RTEN |= USB_OTG_FS2_WAKEUP_EINT_LINE; \
                           } while(0U)
#endif /* USB_OTG_FS2 */

#if defined (USB_OTG_HS)
#define USB_OTG_HS_WAKEUP_EINT_LINE             EINT_LINE_20
#define USBD_OTG_HS_WAKEUP_EINT_ENABLE_IT()     EINT->IMASK |= USB_OTG_HS_WAKEUP_EINT_LINE
#define USBD_OTG_HS_WAKEUP_EINT_DISABLE_IT()    EINT->IMASK &= ~(USB_OTG_HS_WAKEUP_EINT_LINE)
#define USBD_OTG_HS_WAKEUP_EINT_GET_FLAG()      EINT->IPEND & (USB_OTG_HS_WAKEUP_EINT_LINE)
#define USBD_OTG_HS_WAKEUP_EINT_CLEAR_FLAG()    EINT->IPEND = USB_OTG_HS_WAKEUP_EINT_LINE

#define USBD_OTG_HS_WAKEUP_EINT_ENABLE_RISING_EDGE() \
                        do { \
                             EINT->FTEN &= ~(USB_OTG_HS_WAKEUP_EINT_LINE); \
                             EINT->RTEN |= USB_OTG_HS_WAKEUP_EINT_LINE; \
                           } while(0U)
#endif /* USB_OTG_HS */

void USBD_OTG_ConfigDeviceTxFifo(USBD_HANDLE_T* usbdh, uint8_t epInNum, uint16_t depth);
void USBD_OTG_IsrHandler(USBD_HANDLE_T* usbdh);
void USBD_SetDevAddress(USBD_HANDLE_T* usbdh, uint8_t address);
void USBD_SetTestMode(USBD_HANDLE_T* usbdh, uint8_t testMode);
void USBD_Config(USBD_HANDLE_T* usbdh);
void USBD_Start(USBD_HANDLE_T* usbdh);
void USBD_Stop(USBD_HANDLE_T* usbdh);
void USBD_StopDevice(USBD_HANDLE_T* usbdh);
void USBD_EP_Open(USBD_HANDLE_T* usbdh, uint8_t epAddr, \
                  uint8_t epType, uint16_t epMps);
void USBD_EP_Close(USBD_HANDLE_T* usbdh, uint8_t epAddr);
void USBD_EP_Stall(USBD_HANDLE_T* usbdh, uint8_t epAddr);
void USBD_EP_ClearStall(USBD_HANDLE_T* usbdh, uint8_t epAddr);
uint8_t USBD_EP_ReadStallStatus(USBD_HANDLE_T* usbdh, uint8_t epAddr);
uint32_t USBD_EP_ReadRxDataLen(USBD_HANDLE_T* usbdh, uint8_t epAddr);
void USBD_EP_Flush(USBD_HANDLE_T* usbdh, uint8_t epAddr);
void USBD_EP_Receive(USBD_HANDLE_T* usbdh, uint8_t epAddr, \
                     uint8_t* buffer, uint32_t length);

void USBD_EP_Transfer(USBD_HANDLE_T* usbdh, uint8_t epAddr, \
                      uint8_t* buffer, uint32_t length);

void USBD_DisconnectCallback(USBD_HANDLE_T* usbdh);
void USBD_ConnectCallback(USBD_HANDLE_T* usbdh);
void USBD_ResumeCallback(USBD_HANDLE_T* usbdh);
void USBD_SuspendCallback(USBD_HANDLE_T* usbdh);
void USBD_EnumDoneCallback(USBD_HANDLE_T* usbdh);
void USBD_SetupStageCallback(USBD_HANDLE_T* usbdh);
void USBD_DataInStageCallback(USBD_HANDLE_T* usbdh, uint8_t epNum);
void USBD_DataOutStageCallback(USBD_HANDLE_T* usbdh, uint8_t epNum);
void USBD_SOFCallback(USBD_HANDLE_T* usbdh);
void USBD_IsoInInCompleteCallback(USBD_HANDLE_T* usbdh, uint8_t epNum);
void USBD_IsoOutInCompleteCallback(USBD_HANDLE_T* usbdh, uint8_t epNum);
void USBD_UserDelayCallback(USBD_HANDLE_T* usbdh, uint32_t nms);

/**@} end of group USB_Device_Functions*/
/**@} end of group USB_Device_Driver*/

#endif /* USB_OTG_FS || USB_OTG_FS2 || USB_OTG_HS */

/**@} end of group APM32F4xx_StdPeriphDriver*/

#ifdef __cplusplus
}
#endif

#endif /* __APM32F4XX_USB_DEVICE_H */
