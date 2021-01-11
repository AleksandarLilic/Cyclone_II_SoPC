/***********************************************************************
*
* Module:  Demo JTAG UART driver functions
* File:    chu_uart_drv.c
* Purpose: Function to transmit a string
*
***********************************************************************/
/* file inclusion */
#include "uart_drv.h"


/***********************************************************************
* function: jtaguart_wr_str()
* purpose:  write (transmit) a string to JTAG UART
* argument:
*   jtag_base: base address of JTAG UART
*   msg: pointer to a string message
* return:
* note:
***********************************************************************/
void jtaguart_wr_str(alt_u32 jtag_base, char* msg)
{
  alt_u32 data32;

  while(*msg){
    data32 = (alt_u32) *msg;
    if(jtaguart_rd_wspace(jtag_base)!=0){    // buffer space available
      jtaguart_wr_ch(jtag_base, data32);     // send a char
      msg++;
    } // end if
  } // end while
}





