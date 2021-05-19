/*
 * utility.c
 *
 *  Created on: 6 мая 2021 г.
 *      Author: rukarlie
 */


#include <utility.h>




void ke_delay_ms(uint16_t t_ms){
    uint16_t i;
    for(i=0;i<t_ms; i++){
        __delay_cycles(8000);
        hal_system_WatchdogFeed();
    }
}


void ke_delay_us(uint16_t t_us){
    uint16_t i;
    for(i=0;i<t_us; i++){
        __delay_cycles(6);  //TODO: Check 1us
        hal_system_WatchdogFeed();
    }
}


uint16_t ke_uart_sndtext(char* p_msg){
    uint16_t length = strlen(p_msg);
    uint16_t i;
    for(i =0;i<length;i++){
        hal_uart_TxByte(p_msg[i]);
        hal_system_WatchdogFeed();    // If msg too long, WD can reset MCU.  We feed watchdog and he leave our MCU in rest (don't reset)

    }
    return  length;
}


uint16_t ke_uart_rcvtext(char* p_msg,uint16_t maxlen_msg, char sep){
    static uint16_t cntr = 0;
    uint16_t ret = 0;

    if(hal_uart_RxPeekByte((uint8_t*)&p_msg[cntr])){
               if((p_msg[cntr] == sep)||(cntr>=(maxlen_msg-1))){
                   p_msg[cntr] = 0;
                   ret = cntr+1;
                   cntr =0;
               }else{
                   cntr++;
                   ret =0;
               }
               hal_system_LEDToggle(HAL_SYS_LED_0 );  //Debug toggle led

           }

    return ret;
}



uint16_t ke_string_uppercase(char* p_char){
    uint16_t length = strlen(p_char);
    uint16_t i;
   for(i =0;i<length;i++){
       if(((uint8_t)p_char[i]>96) && ((uint8_t)p_char[i]<123)){
           p_char[i]= (char)((uint8_t)p_char[i]-32);
       }
   }

    return length;
}

 void ke_switch_initparams(sw_cntrl_pins* p_pin_tbl){
     p_pin_tbl->pin0 = SW_PIN0;
     p_pin_tbl->port0 = SW_PORT0;
     p_pin_tbl->pin1 = SW_PIN1;
     p_pin_tbl->port1 = SW_PORT1;



 }

 uint8_t ke_switch_init(sw_cntrl_pins* p_pin_tbl){
     uint8_t result =0;
     if(p_pin_tbl!=NULL){
         p_sw_tbl = p_pin_tbl;
         GPIO_setAsOutputPin(p_pin_tbl->port0, p_pin_tbl->pin0);
         GPIO_setAsOutputPin(p_pin_tbl->port1, p_pin_tbl->pin1);
         result=ke_switch_setchann(0);
     }else{
         result=1;
     }

     return result;
 }

uint8_t ke_switch_setchann(uint8_t ch_num){
    uint8_t result = 0;
    //ch_num%=4;
    if(p_sw_tbl!=NULL){

        if(ch_num&1){
            GPIO_setOutputHighOnPin(p_sw_tbl->port0, p_sw_tbl->pin0);
        }else{
            GPIO_setOutputLowOnPin(p_sw_tbl->port0, p_sw_tbl->pin0);
        }

        if(((ch_num)>>1)&1){
            GPIO_setOutputHighOnPin(p_sw_tbl->port1, p_sw_tbl->pin1);
        }else{
            GPIO_setOutputLowOnPin(p_sw_tbl->port1, p_sw_tbl->pin1);
        }


    }else{
        result =1;
    }
    return result;
}

