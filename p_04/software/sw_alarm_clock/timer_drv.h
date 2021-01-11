/***********************************************************************
*
* Module: Demo timer driver header
* File:   chu_timer_drv.h
*
***********************************************************************/
/* file inclusion */
#include "alt_types.h"
#include "io.h"

/***********************************************************************
* constant definitions
***********************************************************************/
#define TIMER_STAT_REG_OFT 0  // status register address offset
#define TIMER_CTRL_REG_OFT 1  // control register address offset
#define TIMER_PERL_REG_OFT 2  // period reg (lower 16 bits) addr offset
#define TIMER_PERH_REG_OFT 3  // period reg (upper 16 bits) addr offset

/***********************************************************************
* macro definitions
***********************************************************************/
/* check "to" field for ms tick */
#define timer_read_tick(base)   (IORD(base, TIMER_STAT_REG_OFT) & 0x01)
/* clear "to" field */
#define timer_clear_tick(base)  IOWR(base, TIMER_STAT_REG_OFT, 0)

/***********************************************************************
* function prototypes
***********************************************************************/
void timer_wr_per(alt_u32 timer_base, alt_u32 per);





