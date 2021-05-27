/*
 * ke_spi_slave.h
 *
 *  Created on: 26 мая 2021 г.
 *      Author: rukarlie
 */

#ifndef KESPI_KE_SPI_SLAVE_H_
#define KESPI_KE_SPI_SLAVE_H_

#include "eusci_a_spi.h"
#include "dma.h"
#include "inc/hw_memmap.h"
#include "gpio.h"


//*****************************************************************************
//
//! The following are values that select EUSCI and DMA channels
//
//*****************************************************************************
#define KE_SPI_BASE_ADDR    EUSCI_A2_BASE             // Выбрали порт А2 для SPI ||  Select EUSCI_A2
#define KE_SPI_TX_DMA_CH    DMA_CHANNEL_5            //Select DMA channel (ref. Table 9-11 s.86 slaseb7d)
#define KE_SPI_TX_DMA_TRG   DMA_TRIGGERSOURCE_15    // Select DMA trigger (ref. Table 9-11 s.86 slaseb7d)
#define KE_SPI_VECTOR       USCI_A2_VECTOR         //Select EUSCI_A2 Interrupt vector


#define KE_SPI_PIN_PORT     GPIO_PORT_P7        //For select PORT and PINs see Chapter 7  slaseb7d.pdf
#define KE_SPI_PIN0         GPIO_PIN0          // Конфигурация пинов 0-3 на порту 7 для работы с SPI на порту А2 || Configure Port 7 Pins 0-3 for work with EUSCI_A2 SPI (slaseb7d.pdf)
#define KE_SPI_PIN1         GPIO_PIN1
#define KE_SPI_PIN2         GPIO_PIN2
#define KE_SPI_PIN3         GPIO_PIN3

//*****************************************************************************
//
//! \brief Initialize  SPI as slave and enable SPI
//!
//! This function initialize SPI with 00 Phase/polarity mode (see s.804 Fig 31-4 SLAU367P)
//! and with low ChipSelect signal.
//!
//! \param None
//!
//! \return SPI_BASE_ADDR
//
//*****************************************************************************
extern uint16_t ke_spi_s_init_spislave(void);


//*****************************************************************************
//
//! \brief Initialize and enable DMA for work with SPI
//!
//! This function initialize DMA with trigger on SPI TX interrupt
//!
//! \param srcAddr is the msgbufer address,  SPI transfers data from this address.
//! \param txSz is size of msgbufer.
//!
//!
//! \return SPI_TX_DMA_CH
//
//*****************************************************************************
extern uint16_t ke_spi_s_enable_txdmamode(uint32_t srcAddr, uint16_t txSz);


//*****************************************************************************
//
//! \brief Return status enable/disable DMA
//!
//! This function return status enable/disable DMA
//!
//! \param None
//!
//!
//! \return isen  status  enable/disable
//
//*****************************************************************************
extern uint16_t ke_spi_s_isDMAen(void);

//*****************************************************************************
//
//! \brief Enable DMA
//!
//! This function enable DMA
//!
//! \param None
//!
//!
//! \return None
//
//*****************************************************************************
extern void ke_spi_s_txDMAen(void);

#endif /* KESPI_KE_SPI_SLAVE_H_ */
