/*
 * ke_spi_slave.c
 *
 *  Created on: 26 мая 2021 г.
 *      Author: rukarlie
 */

#include "ke_spi_slave.h"




#pragma vector=KE_SPI_VECTOR
__interrupt void spi_clbck(void){

    if(HWREG16(KE_SPI_BASE_ADDR + OFS_UCAxIFG) & EUSCI_A_SPI_TRANSMIT_INTERRUPT){       //Проверяем какое прерывание нам пришло, по приёму или по передаче

        //User code

        HWREG16(KE_SPI_BASE_ADDR + OFS_UCAxIFG) &=  ~EUSCI_A_SPI_TRANSMIT_INTERRUPT;    //Сбрасываем флаг прерывания
    }

    if(HWREG16(KE_SPI_BASE_ADDR + OFS_UCAxIFG) & EUSCI_A_SPI_RECEIVE_INTERRUPT){

            //User code

            HWREG16(KE_SPI_BASE_ADDR + OFS_UCAxIFG) &=  ~EUSCI_A_SPI_RECEIVE_INTERRUPT;
        }
   // hal_system_WatchdogFeed();


}



uint16_t ke_spi_s_init_spislave(void){
    GPIO_setAsPeripheralModuleFunctionInputPin(
           KE_SPI_PIN_PORT,
           KE_SPI_PIN0+KE_SPI_PIN1+KE_SPI_PIN2 + KE_SPI_PIN3,
           GPIO_PRIMARY_MODULE_FUNCTION
           );     // Конфигурация пинов 0-3 на порту 7 для работы с SPI на порту А2    || Configure Port 7 Pins 0-3 for work with EUSCI_A2 SPI (slaseb7d.pdf)

   EUSCI_A_SPI_initSlaveParam spiParams;       //Структура параметров SPI

   // Задаём параметры пока по дефолту
   spiParams.clockPhase = EUSCI_A_SPI_PHASE_DATA_CHANGED_ONFIRST_CAPTURED_ON_NEXT;  //Фаза SPI, по какому фронту читать
   spiParams.clockPolarity = EUSCI_A_SPI_CLOCKPOLARITY_INACTIVITY_LOW;              //Полярность сигнала, какой фронт считается первым а какой вторым
   spiParams.spiMode = EUSCI_A_SPI_4PIN_UCxSTE_ACTIVE_LOW;                          // Режим работы, сколькипроводная система и полярность управляющего сигнала
   spiParams.msbFirst = EUSCI_A_SPI_MSB_FIRST;                                      //Литл-биг ендиан


   //Инициализация SPi slave
  
   EUSCI_A_SPI_initSlave(KE_SPI_BASE_ADDR, &spiParams);
   EUSCI_A_SPI_enable(KE_SPI_BASE_ADDR);
   //EUSCI_A_SPI_disableInterrupt(KE_SPI_BASE_ADDR, EUSCI_A_SPI_TRANSMIT_INTERRUPT);
   EUSCI_A_SPI_transmitData(KE_SPI_BASE_ADDR, 0xAB);


   return KE_SPI_BASE_ADDR;

}


uint16_t ke_spi_s_enable_txdmamode(uint32_t srcAddr, uint16_t txSz){
    EUSCI_A_SPI_disableInterrupt(KE_SPI_BASE_ADDR, EUSCI_A_SPI_TRANSMIT_INTERRUPT);
    
    DMA_initParam dma4spiParams;
    dma4spiParams.channelSelect =  KE_SPI_TX_DMA_CH;
    dma4spiParams.transferModeSelect = DMA_TRANSFER_SINGLE;
    dma4spiParams.transferSize = txSz;
    dma4spiParams.triggerSourceSelect = KE_SPI_TX_DMA_TRG;  //UCA2TX (ref. Table 9-11 s.86 slaseb7d)
    dma4spiParams.transferUnitSelect = DMA_SIZE_SRCBYTE_DSTBYTE;
    dma4spiParams.triggerTypeSelect = DMA_TRIGGER_RISINGEDGE;
    
    DMA_init(&dma4spiParams);
    DMA_setSrcAddress(KE_SPI_TX_DMA_CH , srcAddr, DMA_DIRECTION_INCREMENT);
    DMA_setDstAddress(KE_SPI_TX_DMA_CH ,EUSCI_A_SPI_getTransmitBufferAddress(KE_SPI_BASE_ADDR), DMA_DIRECTION_UNCHANGED);
    DMA_enableTransfers(KE_SPI_TX_DMA_CH );
    
    return KE_SPI_TX_DMA_CH ;
    
}

uint16_t ke_spi_s_isDMAen(void){
    return HWREG16(DMA_BASE + KE_SPI_TX_DMA_CH  + OFS_DMA0CTL) & DMAEN;
}

void ke_spi_s_txDMAen(void){
    HWREG16(DMA_BASE + KE_SPI_TX_DMA_CH + OFS_DMA0CTL) |= DMAEN;
}


