/*
 * Copyright (c) 2024 Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * -----------------------------------------------------------------------------
 *
 * $Date:       26. September 2024
 * $Revision:   V3.0
 *
 * Project:     Ethernet MAC Driver for STMicroelectronics STM32 devices
 *
 * -----------------------------------------------------------------------------
 */

/*! \page eth_mac_stm32 Ethernet MAC

# Revision History

- Version 3.0
  - Initial release

# Requirements

This driver requires the STM32 device specific **HAL** and **STM32CubeMX** (CubeMX) initialization code generator.
The driver instance is mapped to hardware as shown in the table below:

  CMSIS Driver Instance | STM32 Hardware Resource
  :---------------------|:-----------------------
  Driver_ETH_MAC0       | EMAC

# Deviations

This driver has the following deviations from the CMSIS-Driver specification:

__Conceptual__ deviations:
  - CubeMX generated initialization code (function MX_ETH_Init) already configures
    the peripheral. Power, clocks, pins, and interrupts are enabled after execution
    of initialization that executes in `main.c`.

__Functional__ deviations:
  - GetCapabilities:
    - depends on the code generated by CubeMX.
  - Initialize:
    - depends on the code generated by CubeMX.
    - does not initialize the pins.
  - Uninitialize:
    - does not de-initialize the pins.
  - PowerControl:
    - depends on the code generated by CubeMX.
    - low-power mode is not supported by HAL.
  - SetAddressFilter:
    - not supported by HAL.
  - GetRxFrameTime:
    - not supported by HAL.
  - GetTxFrameTime:
    - not supported by HAL.
  - Control:
    - not supported control codes: ARM_ETH_MAC_CONTROL_TX, ARM_ETH_MAC_FLUSH, and ARM_ETH_MAC_SLEEP.
    - for control code ARM_ETH_MAC_VLAN_FILTER the VLAN filter disable is not supported.
  - ControlTimer:
    - not supported by HAL.

# CubeMX Configuration

This driver requires the following configuration in CubeMX:

  - **clock**: appropriate **AHB clock** on which Ethernet MAC controller is connected.
  - **peripheral**: **ETH** peripheral configured as **MII** or **RMII** mode
    and **Parameter Settings** configured as desired.
  - **pins**:
    - for **RMII** mode: **ETH_CRS_DV**, **ETH_MDC**, **ETH_MDIO**, **ETH_REF_CLK**, **ETH_RXD0**
      , **ETH_RXD1**, **ETH_TXD0**, **ETH_TXD1** and **ETH_TX_EN pins**.
    - for **MII** mode: **ETH_COL**, **ETH_CRS**, **ETH_MDC**, **ETH_MDIO**, **ETH_RXD0**
      , **ETH_RXD1**, **ETH_RXD2**, **ETH_RXD3**, **ETH_RX_CLK**, **ETH_RX_DV**, **ETH_TXD0**
      , **ETH_TXD1**, **ETH_TXD2**, **ETH_TXD3**, **ETH_TX_CLK** and **ETH_TX_EN pins**.
  - **interrupts**: enabled **Ethernet global interrupt** and **IRQ handlers** that **Call HAL handlers**.

> **Notes**
>
> - configuration information in the **MX_Device.h** file is based on CubeMX configuration.
> - for devices with cache, ensure that ETH DMA descriptors (**DMARxDscrTab** and **DMATxDscrTab**)
>   are located in **non-cacheable** and **non-shareable device memory**.
> - for devices with cache, ensure that ETH data buffers (**eth_mac0_rx_buf** and **eth_mac0_tx_buf**)
>   are located in **non-cacheable** and **non-shareable normal memory**.

## Example

### Pinout & Configuration tab

  1. In the **Pinout view** window click on a pin and select it's functionality:
       Pin      | Functionality
       :--------|:--------------------:
       PA1      | **ETH_REF_CLK**
       PA2      | **ETH_MDIO**
       PA7      | **ETH_CRS_DV**
       PC1      | **ETH_MDC**
       PC4      | **ETH_RXD0**
       PC5      | **ETH_RXD1**
       PG11     | **ETH_TX_EN**
       PG12     | **ETH_TXD1**
       PG13     | **ETH_TXD0**
     \n

  2. Under **Categories**: **Connectivity** select **ETH**:

     __Mode__:
       - Mode: **RMII**

     __Configuration__:
       - Parameter Settings:
           General: Ethernet Configuration | Value
           :-------------------------------|:---------------:
           Ethernet MAC Address            | unused
           Tx Descriptor Length            | **4**
           First Tx Descriptor Address     | **0x30040060**
           Rx Descriptor Length            | **4**
           First Rx Descriptor Address     | **0x30040000**
           Rx Buffers Length               | **1524**
         \n
       - GPIO Settings:
           Pin Name | Signal on Pin | Pin Context..| GPIO output..| GPIO mode                     | GPIO Pull-up/Pull..| Maximum out..| Fast Mode | User Label
           :--------|:-------------:|:------------:|:------------:|:-----------------------------:|:------------------:|:------------:|:---------:|:----------:
           PA1      | ETH_REF_CLK   | n/a          | n/a          | Alternate Function Push Pull  | No pull-up and no..| **High**     | n/a       |.
           PA2      | ETH_MDIO      | n/a          | n/a          | Alternate Function Push Pull  | No pull-up and no..| **High**     | n/a       |.
           PA7      | ETH_CRS_DV    | n/a          | n/a          | Alternate Function Push Pull  | No pull-up and no..| **High**     | n/a       |.
           PC1      | ETH_MDC       | n/a          | n/a          | Alternate Function Push Pull  | No pull-up and no..| **High**     | n/a       |.
           PC4      | ETH_RXD0      | n/a          | n/a          | Alternate Function Push Pull  | No pull-up and no..| **High**     | n/a       |.
           PC5      | ETH_RXD1      | n/a          | n/a          | Alternate Function Push Pull  | No pull-up and no..| **High**     | n/a       |.
           PG11     | ETH_TX_EN     | n/a          | n/a          | Alternate Function Push Pull  | No pull-up and no..| **High**     | n/a       |.
           PG12     | ETH_TXD1      | n/a          | n/a          | Alternate Function Push Pull  | No pull-up and no..| **High**     | n/a       |.
           PG13     | ETH_TXD0      | n/a          | n/a          | Alternate Function Push Pull  | No pull-up and no..| **High**     | n/a       |.
         \n

  3. Under **Categories**: **System Core** select **NVIC**:

     __Configuration__:
       - NVIC:
           NVIC Interrupt Table              | Enabled     | Preemption Priority | Sub Priority
           :---------------------------------|:-----------:|:-------------------:|:------------:
           Ethernet global interrupt         | **checked** | 0                   | 0
       - Code generation:
           Enabled interrupt table           | Select for..| Generate Enable in..| Generate IRQ h.. | Call HAL handler
           :---------------------------------|:-----------:|:-------------------:|:----------------:|:----------------:
           Ethernet global interrupt         | unchecked   | checked             | checked          | checked
       \n


  4. Under **Categories**: **System Core** select **CORTEX_M7**:

     __Configuration__:
       - Parameter Settings:
           Speculation default mode Settings               | Value
           :-----------------------------------------------|:-------------------------:
           Speculation default mode                        | Disabled
         \n
           Cortex Interface Settings                       | Value
           :-----------------------------------------------|:-------------------------:
           CPU ICache                                      | Enabled
           CPU DCache Length                               | Enabled
         \n
           Cortex Memory Protection Unit Control Settings  | Value
           :-----------------------------------------------|:-------------------------:
           MPU Control Mode                                | Background Region Privileged accesses only + MPU disabled during hard fault
         \n
           Cortex Memory Protection Unit Region 0 Settings | Value
           :-----------------------------------------------|:-------------------------:
           MPU Region                                      | **Enabled**
           MPU Region Base Address                         | **0x24000000**
           MPU Region Size                                 | **512kB**
           MPU SubRegion Disable                           | **0x0**
           MPU TEX field level                             | **level 1**
           MPU Access Permission                           | **ALL ACCESS PERMITTED**
           MPU Instruction Access                          | **DISABLE**
           MPU Shareability Permission                     | **DISABLE**
           MPU Cacheable Permission                        | **ENABLE**
           MPU Bufferable Permission                       | **ENABLE**
         \n
           Cortex Memory Protection Unit Region 1 Settings | Value
           :-----------------------------------------------|:-------------------------:
           MPU Region                                      | **Enabled**
           MPU Region Base Address                         | **0x30000000**
           MPU Region Size                                 | **512kB**
           MPU SubRegion Disable                           | **0x0**
           MPU TEX field level                             | **level 1**
           MPU Access Permission                           | **ALL ACCESS PERMITTED**
           MPU Instruction Access                          | **DISABLE**
           MPU Shareability Permission                     | **DISABLE**
           MPU Cacheable Permission                        | **DISABLE**
           MPU Bufferable Permission                       | **DISABLE**
         \n
           Cortex Memory Protection Unit Region 2 Settings | Value
           :-----------------------------------------------|:-------------------------:
           MPU Region                                      | **Enabled**
           MPU Region Base Address                         | **0x30040000**
           MPU Region Size                                 | **256B**
           MPU SubRegion Disable                           | **0x0**
           MPU TEX field level                             | **level 0**
           MPU Access Permission                           | **ALL ACCESS PERMITTED**
           MPU Instruction Access                          | **DISABLE**
           MPU Shareability Permission                     | **DISABLE**
           MPU Cacheable Permission                        | **DISABLE**
           MPU Bufferable Permission                       | **DISABLE**
         \n

### Clock Configuration tab

  1. Configure **To AHB1,2 Peripheral Clocks (MHz)**: **200**

### Project Manager tab

  1. Under **Advanced Settings**:

     __Generated Function Calls__:
       Generate Code | Function Name               | Peripheral Inst..| Do not generate ..| Visibility (Static)
       :-------------|:---------------------------:|:----------------:|:-----------------:|:-------------------:
       checked       | MX_ETH_Init                 | ETH              | unchecked         | checked

## Source Code

Add **RxDecripSection**, **TxDecripSection**, <b>.driver.eth_mac0_rx_buf</b> and <b>.driver.eth_mac0_tx_buf</b>
sections to the Scatter file if GNU Compiler or Arm Compiler 6 is used.

Example:
~~~
RW_ETH_RX_DESC 0x30040000 0x00000060 {
  *(.RxDecripSection)
}
RW_ETH_TX_DESC 0x30040060 0x00000060 {
  *(.TxDecripSection)
}
RW_ETH_RX_BUF  0x30040100 0x00001800 {
  *(.driver.eth_mac0_rx_buf)
}
RW_ETH_TX_BUF  0x30041900 0x00001800 {
  *(.driver.eth_mac0_tx_buf)
}
~~~
*/

/*! \cond */

#include "ETH_MAC_STM32.h"

#include "RTE_Components.h"
#include  CMSIS_device_header

#include <string.h>

// Driver Version **************************************************************
                                                //  CMSIS Driver API version           , Driver version
static  const ARM_DRIVER_VERSION driver_version = { ARM_DRIVER_VERSION_MAJOR_MINOR(2,2), ARM_DRIVER_VERSION_MAJOR_MINOR(3,0) };
// *****************************************************************************

// Compile-time configuration **************************************************

// Configuration depending on MX_Device.h

// Check if Ethernet MAC peripheral instance is configured in STM32CubeMX
#ifndef MX_ETH
#error  Ethernet MAC driver requires ETH peripheral configuration in STM32CubeMX!
#else
#define DRIVER_CONFIG_VALID             1
#endif

// *****************************************************************************

#ifdef  DRIVER_CONFIG_VALID             // Driver code is available only if configuration is valid

// Macros
// Macro for section for RW info
#ifdef  ETH_MAC_SECTION_NAME
#define ETH_MACn_SECTION_(name,n)       __attribute__((section(name #n)))
#define ETH_MACn_SECTION(n)             ETH_MACn_SECTION_(ETH_MAC_SECTION_NAME,n)
#else
#define ETH_MACn_SECTION(n)
#endif

// Driver status
typedef struct {
  uint8_t                       initialized  : 1;       // Initialized status: 0 - not initialized, 1 - initialized
  uint8_t                       powered      : 1;       // Power status:       0 - not powered,     1 - powered
  uint8_t                       reserved     : 6;       // Reserved (for padding)
} DriverStatus_t;

// Run-time information (RW)
typedef struct {
  ARM_ETH_MAC_SignalEvent_t     cb_event;               // Event callback
  DriverStatus_t                drv_status;             // Driver status
  uint8_t                       alloc_idx;              // Buffer allocation index
  uint16_t                      reserved;               // Reserved (for padding)
  ETH_BufferTypeDef             tx_buf;                 // Transmit buffer pointers
  ETH_BufferTypeDef             rx_buf;                 // Receive buffer pointers
  ETH_MACConfigTypeDef          mac_config;             // ETH MAC configuration structure
  ETH_MACFilterConfigTypeDef    mac_filter;             // ETH MAC filter structure
} RW_Info_t;

// Compile-time Information (RO)
// also contains pointer to run-time information
typedef struct {
  ETH_HandleTypeDef            *ptr_heth;               // Pointer to Ethernet handle
  ETH_TxPacketConfig           *ptr_TxConfig;           // Pointer to transmit packet configuration structure
  RW_Info_t                    *ptr_rw_info;            // Pointer to run-time information (RW)
} RO_Info_t;

// Ethernet communication data buffers that need to be positioned in non-cacheable and non-shareable normal memory
static uint8_t                  eth_mac0_rx_buf[ETH_RX_DESC_CNT][ETH_MAX_PACKET_SIZE] __attribute__((section(".driver.eth_mac0_rx_buf")));
static uint8_t                  eth_mac0_tx_buf[ETH_TX_DESC_CNT][ETH_MAX_PACKET_SIZE] __attribute__((section(".driver.eth_mac0_tx_buf")));

// Information definitions
extern ETH_HandleTypeDef        heth;
extern ETH_TxPacketConfig       TxConfig;
static       RW_Info_t          eth_mac0_rw_info ETH_MACn_SECTION(0);
static const RO_Info_t          eth_mac0_ro_info = { &heth,
                                                     &TxConfig,
                                                     &eth_mac0_rw_info
                                                   };

// Local functions prototypes
static ARM_DRIVER_VERSION       ETH_MAC_GetVersion       (void);
static ARM_ETH_MAC_CAPABILITIES ETH_MAC_GetCapabilities  (void);
static int32_t                  ETH_MAC_Initialize       (ARM_ETH_MAC_SignalEvent_t cb_event);
static int32_t                  ETH_MAC_Uninitialize     (void);
static int32_t                  ETH_MAC_PowerControl     (ARM_POWER_STATE state);
static int32_t                  ETH_MAC_GetMacAddress    (ARM_ETH_MAC_ADDR *ptr_addr);
static int32_t                  ETH_MAC_SetMacAddress    (const ARM_ETH_MAC_ADDR *ptr_addr);
static int32_t                  ETH_MAC_SetAddressFilter (const ARM_ETH_MAC_ADDR *ptr_addr, uint32_t num_addr);
static int32_t                  ETH_MAC_SendFrame        (const uint8_t *frame, uint32_t len, uint32_t flags);
static int32_t                  ETH_MAC_ReadFrame        (uint8_t *frame, uint32_t len);
static uint32_t                 ETH_MAC_GetRxFrameSize   (void);
static int32_t                  ETH_MAC_GetRxFrameTime   (ARM_ETH_MAC_TIME *time);
static int32_t                  ETH_MAC_GetTxFrameTime   (ARM_ETH_MAC_TIME *time);
static int32_t                  ETH_MAC_Control          (uint32_t control, uint32_t arg);
static int32_t                  ETH_MAC_ControlTimer     (uint32_t control, ARM_ETH_MAC_TIME *time);
static int32_t                  ETH_MAC_PHY_Read         (uint8_t phy_addr, uint8_t reg_addr, uint16_t *data);
static int32_t                  ETH_MAC_PHY_Write        (uint8_t phy_addr, uint8_t reg_addr, uint16_t data);

// Driver functions ************************************************************

/**
  \fn          ARM_DRIVER_VERSION ETH_MAC_GetVersion (void)
  \brief       Get driver version.
  \return      \ref ARM_DRIVER_VERSION
*/
static ARM_DRIVER_VERSION ETH_MAC_GetVersion (void) {
  return driver_version;
}

/**
  \fn          ARM_ETH_MAC_CAPABILITIES ETH_MAC_GetCapabilities (void)
  \brief       Get driver capabilities.
  \return      \ref ARM_ETH_MAC_CAPABILITIES
*/
static ARM_ETH_MAC_CAPABILITIES ETH_MAC_GetCapabilities (void) {
  ARM_ETH_MAC_CAPABILITIES driver_capabilities;

  // Clear capabilities structure
  memset(&driver_capabilities, 0, sizeof(ARM_ETH_MAC_CAPABILITIES));

  // Load capability fields different than 0
  driver_capabilities.checksum_offload_rx_ip4  = 1U;
  driver_capabilities.checksum_offload_rx_ip6  = 1U;
  driver_capabilities.checksum_offload_rx_udp  = 1U;
  driver_capabilities.checksum_offload_rx_tcp  = 1U;
  driver_capabilities.checksum_offload_rx_icmp = 1U;
  driver_capabilities.checksum_offload_tx_ip4  = 1U;
  driver_capabilities.checksum_offload_tx_ip6  = 1U;
  driver_capabilities.checksum_offload_tx_udp  = 1U;
  driver_capabilities.checksum_offload_tx_tcp  = 1U;
  driver_capabilities.checksum_offload_tx_icmp = 1U;

  if (eth_mac0_ro_info.ptr_heth->Init.MediaInterface == HAL_ETH_MII_MODE) {
    driver_capabilities.media_interface = ARM_ETH_INTERFACE_MII;
  } else {
    driver_capabilities.media_interface = ARM_ETH_INTERFACE_RMII;
  }

  driver_capabilities.event_rx_frame = 1U;
  driver_capabilities.event_tx_frame = 1U;
  driver_capabilities.event_wakeup   = 1U;

  return driver_capabilities;
}

/**
  \fn          int32_t ETH_MAC_Initialize (ARM_ETH_MAC_SignalEvent_t cb_event)
  \brief       Initialize Ethernet MAC Device.
  \param[in]   cb_event  Pointer to \ref ARM_ETH_MAC_SignalEvent
  \return      \ref execution_status
*/
static int32_t ETH_MAC_Initialize (ARM_ETH_MAC_SignalEvent_t cb_event) {

  // Clear run-time info
  memset((void *)&eth_mac0_rw_info, 0, sizeof(RW_Info_t));

  // Register callback function
  eth_mac0_rw_info.cb_event = cb_event;

  // Set driver status to initialized
  eth_mac0_rw_info.drv_status.initialized = 1U;

  return ARM_DRIVER_OK;
}

/**
  \fn          int32_t ETH_MAC_Uninitialize (void)
  \brief       De-initialize Ethernet MAC Device.
  \return      \ref execution_status
*/
static int32_t ETH_MAC_Uninitialize (void) {

  if (eth_mac0_rw_info.drv_status.powered != 0U) {
    // If peripheral is powered, power off the peripheral
    (void)ETH_MAC_PowerControl(ARM_POWER_OFF);
  }

  // Clear run-time info
  memset((void *)&eth_mac0_rw_info, 0, sizeof(RW_Info_t));

  return ARM_DRIVER_OK;
}

/**
  \fn          int32_t ETH_MAC_PowerControl (ARM_POWER_STATE state)
  \brief       Control Ethernet MAC Device Power.
  \param[in]   state  Power state
  \return      \ref execution_status
*/
static int32_t ETH_MAC_PowerControl (ARM_POWER_STATE state) {

  switch (state) {
    case ARM_POWER_FULL:
      if (eth_mac0_rw_info.drv_status.initialized == 0U) {
        return ARM_DRIVER_ERROR;
      }

      // Initialize pins, clocks, interrupts and peripheral
      if (HAL_ETH_Init(eth_mac0_ro_info.ptr_heth) != HAL_OK) {
        return ARM_DRIVER_ERROR;
      }

      eth_mac0_rw_info.tx_buf.len = 0;

      // Set driver status to powered
      eth_mac0_rw_info.drv_status.powered = 1U;
      break;

    case ARM_POWER_OFF:

      // De-initialize pins, clocks, interrupts and peripheral
      (void)HAL_ETH_DeInit(eth_mac0_ro_info.ptr_heth);

      // Set driver status to not powered
      eth_mac0_rw_info.drv_status.powered = 0U;
      break;

    case ARM_POWER_LOW:
      return ARM_DRIVER_ERROR_UNSUPPORTED;

    default:
      return ARM_DRIVER_ERROR_PARAMETER;
  }

  return ARM_DRIVER_OK;
}

/**
  \fn          int32_t ETH_MAC_GetMacAddress (ARM_ETH_MAC_ADDR *ptr_addr)
  \brief       Get Ethernet MAC Address.
  \param[in]   ptr_addr  Pointer to address
  \return      \ref execution_status
*/
static int32_t ETH_MAC_GetMacAddress (ARM_ETH_MAC_ADDR *ptr_addr) {

  if (ptr_addr == NULL) {
    return ARM_DRIVER_ERROR_PARAMETER;
  }

  if (eth_mac0_rw_info.drv_status.powered == 0U) {
    return ARM_DRIVER_ERROR;
  }

  memcpy(ptr_addr, eth_mac0_ro_info.ptr_heth->Init.MACAddr, 6);

  return ARM_DRIVER_OK;
}

/**
  \fn          int32_t ETH_MAC_SetMacAddress (const ARM_ETH_MAC_ADDR *ptr_addr)
  \brief       Set Ethernet MAC Address.
  \param[in]   ptr_addr  Pointer to address
  \return      \ref execution_status
*/
static int32_t ETH_MAC_SetMacAddress (const ARM_ETH_MAC_ADDR *ptr_addr) {

  if (ptr_addr == NULL) {
    return ARM_DRIVER_ERROR_PARAMETER;
  }

  if (eth_mac0_rw_info.drv_status.powered == 0U) {
    return ARM_DRIVER_ERROR;
  }

  memcpy(eth_mac0_ro_info.ptr_heth->Init.MACAddr, ptr_addr, 6);

  // Reinitialize ETH to change the MAC address
  if (HAL_ETH_Init(eth_mac0_ro_info.ptr_heth) != HAL_OK) {
    return ARM_DRIVER_ERROR;
  }

  return ARM_DRIVER_OK;
}

/**
  \fn          int32_t ETH_MAC_SetAddressFilter (const ARM_ETH_MAC_ADDR *ptr_addr,
                                                       uint32_t          num_addr)
  \brief       Configure Address Filter.
  \param[in]   ptr_addr  Pointer to addresses
  \param[in]   num_addr  Number of addresses to configure
  \return      \ref execution_status
*/
static int32_t ETH_MAC_SetAddressFilter (const ARM_ETH_MAC_ADDR *ptr_addr, uint32_t num_addr) {
  (void)ptr_addr;
  (void)num_addr;

  // Not supported by HAL
  return ARM_DRIVER_ERROR_UNSUPPORTED;
}

/**
  \fn          int32_t ETH_MAC_SendFrame (const uint8_t *frame, uint32_t len, uint32_t flags)
  \brief       Send Ethernet frame.
  \param[in]   frame  Pointer to frame buffer with data to send
  \param[in]   len    Frame buffer length in bytes
  \param[in]   flags  Frame transmit flags (see ARM_ETH_MAC_TX_FRAME_...)
  \return      \ref execution_status
*/
static int32_t ETH_MAC_SendFrame (const uint8_t *frame, uint32_t len, uint32_t flags) {
  ETH_DMADescTypeDef *tx_desc;
  uint32_t            tx_index;

  if ((frame == NULL) || (len == 0U)) {
    // If any parameter is invalid
    return ARM_DRIVER_ERROR_PARAMETER;
  }

  if (eth_mac0_rw_info.drv_status.powered == 0U) {
    return ARM_DRIVER_ERROR;
  }

  if (eth_mac0_rw_info.tx_buf.len == 0) {
    // Start of a new transmit frame
    tx_index = eth_mac0_ro_info.ptr_heth->TxDescList.CurTxDesc;
    tx_desc  = (ETH_DMADescTypeDef *)eth_mac0_ro_info.ptr_heth->TxDescList.TxDesc[tx_index];

#ifdef ETH_DMATXDESC_OWN
    if ((*((volatile uint32_t *)tx_desc) & ETH_DMATXDESC_OWN) != 0U) {
#else
    if ((tx_desc->DESC3 & ETH_DMATXNDESCWBF_OWN) != 0U) {
#endif
      // If Transmitter is busy
      return ARM_DRIVER_ERROR_BUSY;
    }

    eth_mac0_rw_info.tx_buf.buffer = eth_mac0_tx_buf[tx_index];
    eth_mac0_rw_info.tx_buf.next   = NULL;
  }

  // Copy data fragments to ETH-DMA buffer
  memcpy(eth_mac0_rw_info.tx_buf.buffer + eth_mac0_rw_info.tx_buf.len, frame, len);
  eth_mac0_rw_info.tx_buf.len += len;

  if ((flags & ARM_ETH_MAC_TX_FRAME_FRAGMENT) != 0U) {
    // More data to come, remember current write position
    return ARM_DRIVER_OK;
  }

  // Last fragment, send the packet now
  eth_mac0_ro_info.ptr_TxConfig->TxBuffer = &eth_mac0_rw_info.tx_buf;
  eth_mac0_ro_info.ptr_TxConfig->Length   =  eth_mac0_rw_info.tx_buf.len;

  if (HAL_ETH_Transmit_IT(eth_mac0_ro_info.ptr_heth, eth_mac0_ro_info.ptr_TxConfig) != HAL_OK) {
    return ARM_DRIVER_ERROR;
  }

  eth_mac0_rw_info.tx_buf.len = 0;

  return ARM_DRIVER_OK;
}

/**
  \fn          int32_t ETH_MAC_ReadFrame (uint8_t *frame, uint32_t len)
  \brief       Read data of received Ethernet frame.
  \param[in]   frame  Pointer to frame buffer for data to read into
  \param[in]   len    Frame buffer length in bytes
  \return      number of data bytes read or execution status
                 - value >= 0: number of data bytes read
                 - value < 0: error occurred, value is execution status as defined with \ref execution_status
*/
static int32_t ETH_MAC_ReadFrame (uint8_t *frame, uint32_t len) {
  int32_t ret;

  if ((frame == NULL) && (len != 0U)) {
    // If parameter combination is invalid
    return ARM_DRIVER_ERROR_PARAMETER;
  }

  if (eth_mac0_rw_info.drv_status.powered == 0U) {
    return ARM_DRIVER_ERROR;
  }

  ret = 0;

  if ((frame != NULL) && (eth_mac0_rw_info.rx_buf.buffer != NULL)) {
    memcpy(frame, eth_mac0_rw_info.rx_buf.buffer, len);
    eth_mac0_rw_info.rx_buf.buffer = NULL;
    ret = (int32_t)len;
  }

  return ret;
}

/**
  \fn          uint32_t ETH_MAC_GetRxFrameSize (void)
  \brief       Get size of received Ethernet frame.
  \return      number of bytes in received frame
*/
static uint32_t ETH_MAC_GetRxFrameSize (void) {
  void *dummy;

  if (HAL_ETH_ReadData(eth_mac0_ro_info.ptr_heth, &dummy) == HAL_OK) {
    // Length returned in a Link callback function
    return ((volatile uint32_t)eth_mac0_rw_info.rx_buf.len);
  }

  // If no data is available
  return 0U;
}

/**
  \fn          int32_t ETH_MAC_GetRxFrameTime (ARM_ETH_MAC_TIME *time)
  \brief       Get time of received Ethernet frame.
  \param[in]   time  Pointer to time structure for data to read into
  \return      \ref execution_status
*/
static int32_t ETH_MAC_GetRxFrameTime (ARM_ETH_MAC_TIME *time) {
  (void)time;

  // Not supported by HAL
  return ARM_DRIVER_ERROR_UNSUPPORTED;
}

/**
  \fn          int32_t ETH_MAC_GetTxFrameTime (ARM_ETH_MAC_TIME *time)
  \brief       Get time of transmitted Ethernet frame.
  \param[in]   time  Pointer to time structure for data to read into
  \return      \ref execution_status
*/
static int32_t ETH_MAC_GetTxFrameTime (ARM_ETH_MAC_TIME *time) {
  (void)time;

  // Not supported by HAL
  return ARM_DRIVER_ERROR_UNSUPPORTED;
}

/**
  \fn          int32_t ETH_MAC_Control (uint32_t control, uint32_t arg)
  \brief       Control Ethernet Interface.
  \param[in]   control  Operation
  \param[in]   arg      Argument of operation (optional)
  \return      \ref execution_status
*/
static int32_t ETH_MAC_Control (uint32_t control, uint32_t arg) {
  HAL_StatusTypeDef g_state;

  if (eth_mac0_rw_info.drv_status.powered == 0U) {
    return ARM_DRIVER_ERROR;
  }

  switch (control) {
    case ARM_ETH_MAC_CONFIGURE:
      break;                                    // Continue configuring parameters after this switch block

    case ARM_ETH_MAC_CONTROL_TX:                // Enable or disable the transmitter; arg : 0=disable; 1=enable
      // Not supported by HAL, return OK anyways
      return ARM_DRIVER_OK;

    case ARM_ETH_MAC_CONTROL_RX:                // Enable or disable the receiver; arg : 0=disable; 1=enable
      if (arg != 0U) {
        // Enable MAC receiver
        if (HAL_ETH_Start_IT(eth_mac0_ro_info.ptr_heth) != HAL_OK) {
          return ARM_DRIVER_ERROR;
        }
      } else {
        // Disable MAC receiver
        if (HAL_ETH_Stop_IT (eth_mac0_ro_info.ptr_heth) != HAL_OK) {
          return ARM_DRIVER_ERROR;
        }
      }
      return ARM_DRIVER_OK;

    case ARM_ETH_MAC_FLUSH:                     // Flush a buffer
      // Not supported by HAL, return OK anyways
      return ARM_DRIVER_OK;

    case ARM_ETH_MAC_VLAN_FILTER:               // Configure VLAN Filter for received frames
      // Configure VLAN filter
      if (arg != 0) {
        // arg bits [0-15] are VLAN tag value
        if ((arg & ARM_ETH_MAC_VLAN_FILTER_ID_ONLY) != 0U) {
          // Compare only the 12-bit VLAN identifier
          HAL_ETH_SetRxVLANIdentifier(eth_mac0_ro_info.ptr_heth, ETH_VLANTAGCOMPARISON_12BIT, (arg & 0xFFFF));
        } else {
          // Compare the complete 16-bit VLAN tag value
          HAL_ETH_SetRxVLANIdentifier(eth_mac0_ro_info.ptr_heth, ETH_VLANTAGCOMPARISON_16BIT, (arg & 0xFFFF));
        }
      }
      // Disable VLAN filter is not supported by HAL
      return ARM_DRIVER_OK;

    case ARM_ETH_MAC_SLEEP:
      return ARM_DRIVER_ERROR_UNSUPPORTED;

    default:                                    // Unknown Control
      return ARM_DRIVER_ERROR_PARAMETER;
  }

  // Configure all other parameters if command was to Configure (ARM_ETH_MAC_CONFIGURE)

  // Read device configuration first
  if (HAL_ETH_GetMACConfig(eth_mac0_ro_info.ptr_heth, &eth_mac0_rw_info.mac_config) != HAL_OK) {
    return ARM_DRIVER_ERROR;
  }
  if (HAL_ETH_GetMACFilterConfig(eth_mac0_ro_info.ptr_heth, &eth_mac0_rw_info.mac_filter) != HAL_OK) {
    return ARM_DRIVER_ERROR;
  }

  switch (arg & ARM_ETH_MAC_SPEED_Msk) {                        // --- Link Speed
    case ARM_ETH_MAC_SPEED_10M:
      eth_mac0_rw_info.mac_config.Speed = ETH_SPEED_10M;
      break;

    case ARM_ETH_SPEED_100M:
      eth_mac0_rw_info.mac_config.Speed = ETH_SPEED_100M;
      break;

    default:
      return ARM_DRIVER_ERROR_UNSUPPORTED;
  }

  switch (arg & ARM_ETH_MAC_DUPLEX_Msk) {                       // --- Link Mode
    case ARM_ETH_MAC_DUPLEX_FULL:
      eth_mac0_rw_info.mac_config.DuplexMode = ETH_FULLDUPLEX_MODE;
      break;

    case ARM_ETH_MAC_DUPLEX_HALF:
      eth_mac0_rw_info.mac_config.DuplexMode = ETH_HALFDUPLEX_MODE;
      break;

    default:
      return ARM_DRIVER_ERROR;
  }

  if ((arg & ARM_ETH_MAC_LOOPBACK) != 0U) {     // --- Loopback
    eth_mac0_rw_info.mac_config.LoopbackMode = ENABLE;
  } else {
    eth_mac0_rw_info.mac_config.LoopbackMode = DISABLE;
  }

  if (((arg & ARM_ETH_MAC_CHECKSUM_OFFLOAD_RX) != 0U) &&        // --- Receiver Checksum offload and
      ((arg & ARM_ETH_MAC_CHECKSUM_OFFLOAD_TX) != 0U)) {        // --- Transmitter Checksum offload and
    eth_mac0_rw_info.mac_config.ChecksumOffload = ENABLE;
  } else {
    eth_mac0_rw_info.mac_config.ChecksumOffload = DISABLE;
  }

  if ((arg & ARM_ETH_MAC_ADDRESS_BROADCAST) != 0U) {            // --- Broadcast Frame address
    eth_mac0_rw_info.mac_filter.BroadcastFilter = ENABLE;
  } else {
    eth_mac0_rw_info.mac_filter.BroadcastFilter = DISABLE;
  }

  if ((arg & ARM_ETH_MAC_ADDRESS_MULTICAST) != 0U) {            // --- Multicast Frame address
    eth_mac0_rw_info.mac_filter.PassAllMulticast = ENABLE;
  } else {
    eth_mac0_rw_info.mac_filter.PassAllMulticast = DISABLE;
  }

  if ((arg & ARM_ETH_MAC_ADDRESS_ALL) != 0U) {                  // --- Promiscuous Mode
    eth_mac0_rw_info.mac_filter.PromiscuousMode = ENABLE;
  } else {
    eth_mac0_rw_info.mac_filter.PromiscuousMode = DISABLE;
  }

  if (eth_mac0_ro_info.ptr_heth->gState == HAL_ETH_STATE_STARTED) {
    (void)HAL_ETH_Stop_IT (eth_mac0_ro_info.ptr_heth);
    g_state = HAL_ETH_SetMACConfig(eth_mac0_ro_info.ptr_heth, &eth_mac0_rw_info.mac_config);
    (void)HAL_ETH_Start_IT(eth_mac0_ro_info.ptr_heth);
  } else {
    g_state = HAL_ETH_SetMACConfig(eth_mac0_ro_info.ptr_heth, &eth_mac0_rw_info.mac_config);
  }
  if (g_state != HAL_OK) {
    return ARM_DRIVER_ERROR;
  }
  if (HAL_ETH_SetMACFilterConfig(eth_mac0_ro_info.ptr_heth, &eth_mac0_rw_info.mac_filter) != HAL_OK) {
    return ARM_DRIVER_ERROR;
  }

  return ARM_DRIVER_OK;
}

/**
  \fn          int32_t ETH_MAC_ControlTimer (uint32_t control, ARM_ETH_MAC_TIME *time)
  \brief       Control Precision Timer.
  \param[in]   control  Operation
  \param[in]   time     Pointer to time structure
  \return      \ref execution_status
*/
static int32_t ETH_MAC_ControlTimer (uint32_t control, ARM_ETH_MAC_TIME *time) {
  (void)control;
  (void)time;

  // Not supported by HAL
  return ARM_DRIVER_ERROR_UNSUPPORTED;
}

/**
  \fn          int32_t ETH_MAC_PHY_Read (uint8_t phy_addr, uint8_t reg_addr, uint16_t *data)
  \brief       Read Ethernet PHY Register through Management Interface.
  \param[in]   phy_addr  5-bit device address
  \param[in]   reg_addr  5-bit register address
  \param[out]  data      Pointer where the result is written to
  \return      \ref execution_status
*/
static int32_t ETH_MAC_PHY_Read (uint8_t phy_addr, uint8_t reg_addr, uint16_t *data) {
  uint32_t val;

  if (HAL_ETH_ReadPHYRegister(eth_mac0_ro_info.ptr_heth, phy_addr, reg_addr, &val) != HAL_OK) {
    return ARM_DRIVER_ERROR;
  }
  *data = (uint16_t)val;

  return ARM_DRIVER_OK;
}


/**
  \fn          int32_t ETH_MAC_PHY_Write (uint8_t phy_addr, uint8_t reg_addr, uint16_t data)
  \brief       Write Ethernet PHY Register through Management Interface.
  \param[in]   phy_addr  5-bit device address
  \param[in]   reg_addr  5-bit register address
  \param[in]   data      16-bit data to write
  \return      \ref execution_status
*/
static int32_t ETH_MAC_PHY_Write (uint8_t phy_addr, uint8_t reg_addr, uint16_t data) {

  if (HAL_ETH_WritePHYRegister(eth_mac0_ro_info.ptr_heth, phy_addr, reg_addr, data) != HAL_OK) {
    return ARM_DRIVER_ERROR;
  }

  return ARM_DRIVER_OK;
}

// HAL callback functions ******************************************************

/**
  * @brief  Rx Allocate callback.
  * @param  buff: pointer to allocated buffer
  * @retval None
  */
void HAL_ETH_RxAllocateCallback(uint8_t **buff) {

  // Allocate one of the RX-DMA buffers sequentially
  *buff = eth_mac0_rx_buf[eth_mac0_rw_info.alloc_idx];
  eth_mac0_rw_info.alloc_idx += 1U;
  if (eth_mac0_rw_info.alloc_idx >= ETH_RX_DESC_CNT) {
    eth_mac0_rw_info.alloc_idx = 0U;
  }
}

/**
  * @brief  Rx Link callback.
  * @param  pStart: pointer to packet start
  * @param  pStart: pointer to packet end
  * @param  buff: pointer to received data
  * @param  Length: received data length
  * @retval None
  */
void HAL_ETH_RxLinkCallback(void **pStart, void **pEnd, uint8_t *buff, uint16_t Length) {
  (void)pStart;
  (void)pEnd;

  eth_mac0_rw_info.rx_buf.buffer = buff;
  eth_mac0_rw_info.rx_buf.len    = Length;
}

/**
  * @brief  Tx Transfer completed callbacks.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @retval None
  */
void HAL_ETH_TxCpltCallback(ETH_HandleTypeDef *h_eth) {
  (void)h_eth;

  if (eth_mac0_rw_info.cb_event != NULL) {
    eth_mac0_rw_info.cb_event(ARM_ETH_MAC_EVENT_TX_FRAME);
  }
}

/**
  * @brief  Rx Transfer completed callbacks.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @retval None
  */
void HAL_ETH_RxCpltCallback(ETH_HandleTypeDef *h_eth) {
  (void)h_eth;

  if (eth_mac0_rw_info.cb_event != NULL) {
    eth_mac0_rw_info.cb_event(ARM_ETH_MAC_EVENT_RX_FRAME);
  }
}

/**
  * @brief  Ethernet Power Management module IT callback
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @retval None
  */
void HAL_ETH_PMTCallback(ETH_HandleTypeDef *h_eth) {
  (void)h_eth;

  if (eth_mac0_rw_info.cb_event != NULL) {
    eth_mac0_rw_info.cb_event(ARM_ETH_MAC_EVENT_WAKEUP);
  }
}

// Global driver structures ****************************************************

ARM_DRIVER_ETH_MAC Driver_ETH_MAC0 = {
  ETH_MAC_GetVersion,
  ETH_MAC_GetCapabilities,
  ETH_MAC_Initialize,
  ETH_MAC_Uninitialize,
  ETH_MAC_PowerControl,
  ETH_MAC_GetMacAddress,
  ETH_MAC_SetMacAddress,
  ETH_MAC_SetAddressFilter,
  ETH_MAC_SendFrame,
  ETH_MAC_ReadFrame,
  ETH_MAC_GetRxFrameSize,
  ETH_MAC_GetRxFrameTime,
  ETH_MAC_GetTxFrameTime,
  ETH_MAC_ControlTimer,
  ETH_MAC_Control,
  ETH_MAC_PHY_Read,
  ETH_MAC_PHY_Write
};

#endif  // DRIVER_CONFIG_VALID

/*! \endcond */
