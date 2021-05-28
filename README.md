# UtilityFxn_MSP430FR6047
UtilityFxn for MSP430FR6047. It's some small functions, which can help. For use this utility requires HAL for MSP430FR6047

ke_spi_slave must simplicate work with spi MSP430. In this file there are initialisation SPI slave and transfer to SPI throgh DMA channel .  

Example (Transmit data):


    uint16_t spiBase = ke_spi_s_init_spislave();     //Init SPI Slave

    uint8_t msgPos =0;
    for( msgPos=0; msgPos <sizeof(txMsg);  msgPos++){
        if(txMsg[ msgPos]=='\0') txMsg[ msgPos]='>';
    }


   uint16_t spidmaCh = ke_spi_s_enable_txdmamode(txMsg, sizeof(txMsg));   //Set array txMsg as transmit buffer
 


    while(1){


        if(ke_spi_s_isDMAen() ==0){
            ke_spi_s_txDMAen();                     //When the transfer ends, DMA id disabled. Enable DMA
        }
        hal_system_WatchdogFeed();

    }
