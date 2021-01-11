/***********************************************************************
*
* Module: Demo JTAG UART driver header
* File:   chu_uart_drv.h
*
***********************************************************************/
/* file inclusion */
#include "alt_types.h"
#include "io.h"

/***********************************************************************
* constant definitions
***********************************************************************/
#define JUART_DATA_REG_OFT  0          // data register address offset
#define JUART_CTRL_REG_OFT  1          // control register addr offset

/* check # slots available in FIFO buffer */
#define jtaguart_rd_wspace(base)   \
   ((IORD(base, JUART_CTRL_REG_OFT) & 0xffff0000) >> 16)
/* write an 8-bit char  */
#define jtaguart_wr_ch(base, data)  \
   IOWR(base, JUART_DATA_REG_OFT, data & 0x000000ff)

/***********************************************************************
* function prototypes
***********************************************************************/
void jtaguart_wr_str(alt_u32 jtag_base, char* msg);
