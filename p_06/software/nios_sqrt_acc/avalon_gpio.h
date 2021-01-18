/***********************************************************************
*
* Module:  General-purpose I/O driver header
* File:    avalon_gpio.h
* Purpose: Routines to access switches and LEDs
*
***********************************************************************/
/* file inclusion */
#include "alt_types.h"
#include "io.h"

/***********************************************************************
* constant definitions
***********************************************************************/
#define PIO_DATA_REG_OFT  0  // data register address offset
#define PIO_DIRT_REG_OFT  1  // direction register address offset
#define PIO_INTM_REG_OFT  2  // interrupt mask register address offset
#define PIO_EDGE_REG_OFT  3  // edge capture register address offset

/***********************************************************************
* macro definitions
***********************************************************************/
/* read/write PIO data register */
#define pio_read(base)         IORD(base, PIO_DATA_REG_OFT)
#define pio_write(base, data)  IOWR(base, PIO_DATA_REG_OFT, data)
/* read/clear pushbutton edge capture register */
/* must write 0xf if the write-individual bit option is used in SOPC */
#define btn_read(base)         IORD(base, PIO_EDGE_REG_OFT)
#define btn_clear(base)        IOWR(base, PIO_EDGE_REG_OFT, 0xf)
#define btn_is_pressed(base)   (IORD(base, PIO_EDGE_REG_OFT)!=0)

/***********************************************************************
* function prototypes
***********************************************************************/
alt_u8 sseg_conv_hex(int hex);
void sseg_disp_ptn(alt_u32 base, alt_u8 *ptn);


