/***********************************************************************
*
* Module:  Demo timer driver functions
* File:    chu_timer_drv.c
* Purpose: Functions to set up timer
*
***********************************************************************/
/* file inclusion */
#include "timer_drv.h"

/***********************************************************************
* function: timer_wr_per()
* purpose:  write timer timeout period and configure/start timer
* argument:
*   timer_base: base address of time-stamp timer
*   per: timeout period value
* return:
* note:
***********************************************************************/
void timer_wr_per(alt_u32 timer_base, alt_u32 per)
{
  alt_u16 high, low;

  /* unpack 32-bit timeout period into two 16-bit half words */
  high = (alt_u16) (per>>16);
  low = (alt_u16) (per & 0x0000ffff);
  /* write timeout period */
  IOWR(timer_base, TIMER_PERH_REG_OFT, high);
  IOWR(timer_base, TIMER_PERL_REG_OFT, low);
  /* configure timer to start, continuous mode; enable interrupt */
  IOWR(timer_base, TIMER_CTRL_REG_OFT, 0x0007);
}

