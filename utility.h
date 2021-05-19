/*
 * utility.h
 *
 *  Created on: 6 мая 2021 г.
 *      Author: rukarlie
 *      This file contains utility functions, which can help in work. Name of every function must conform to the form: ke_fxnname().
 */

#ifndef UTILITY_H_
#define UTILITY_H_

#include <stdint.h>
#include <stdbool.h>
#include "hal.h"
#include "string.h"

#define SW_PIN0 GPIO_PIN0
#define SW_PIN1 GPIO_PIN1
#define SW_PORT0 GPIO_PORT_P7
#define SW_PORT1 GPIO_PORT_P7

typedef struct
{
    uint8_t     port0;       //Port GPIO for bit 0
    uint16_t    pin0;        //Pin GPIO for bit0
    uint8_t     port1;       //Port GPIO for bit 1
    uint16_t    pin1;        //Pin GPIO for bit1

}sw_cntrl_pins;

sw_cntrl_pins* p_sw_tbl;   //Pointer to pin table  for switch


/* Function prototypes */

//*****************************************************************************
//
//! Make delay(ms)
//!
//! \param t_ms     Count of ms
//!
//! \return none
//
// *****************************************************************************
extern void ke_delay_ms(uint16_t t_ms);


//*****************************************************************************
//
//! Make delay(us)
//!
//! \param t_us     Count of us
//!
//! \return none
//
// *****************************************************************************
extern void ke_delay_us(uint16_t t_us);


//*****************************************************************************
//
//! UART send text
//!
//! UART must be initialized.
//!
//! \param *p_msg        Pointer to the message (must have NULL termination)
//!
//! \return len_msg      Length of the message
//
// *****************************************************************************
extern uint16_t ke_uart_sndtext(char* p_msg);

//*****************************************************************************
//
//! UART receive text
//!
//! UART must be initialized. This function checks the presence of bytes
//!received by UART at each call. If there is a received byte, then it writes
//!it to an array, the address and maximum size of which is passed
//!in the argument.If the message is fully received, the function will return
//!the number of bytes received, otherwise zero.
//!DO NOT use more than once for the entire program code.
//!
//! \param *p_msg        Pointer to the message
//! \param  maxlen_msg   Max length received msg
//! \param  sep          Character which is separator for text
//!
//! \return len_msg      Length of the message
//
// *****************************************************************************
extern uint16_t ke_uart_rcvtext(char* p_msg,uint16_t maxlen_msg, char sep);


//*****************************************************************************
//
//! Convert all chars to uppercase
//!
//!
//!
//! \param *p_char       Pointer to the chars (must have NULL termination)
//!
//! \return len_msg      Length of the message
//
// *****************************************************************************
extern uint16_t ke_string_uppercase(char* p_char);

//*****************************************************************************
//
//! Initialize switch params with def pins
//!
//!
//!
//! \param *p_pin_tbl       Pointer to table contrl pins
//! \return none
// *****************************************************************************
extern void ke_switch_initparams(sw_cntrl_pins* p_pin_tbl);

//*****************************************************************************
//
//! Initialize switch
//!
//!
//!
//! \param *p_pin_tbl       Pointer to table contrl pins
//! \return none
// *****************************************************************************
extern uint8_t ke_switch_init(sw_cntrl_pins* p_pin_tbl);

//*****************************************************************************
//
//! Set channel  on switch
//!
//!
//!
//! \param ch_num       Pointer to table contrl pins
//! \return res
// *****************************************************************************
extern uint8_t ke_switch_setchann(uint8_t ch_num);

#endif /* UTILITY_H_ */
