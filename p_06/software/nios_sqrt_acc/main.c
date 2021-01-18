#include <stdio.h>
#include <math.h>
#include "system.h"
#include "avalon_gpio.h"

int main()
{
  alt_u32 val, res, ready, done;
  alt_u8 di1_msg[4]={sseg_conv_hex(13),0xfb,0xff,sseg_conv_hex(1)};

  sseg_disp_ptn(SSEG_BASE, di1_msg);               // display "di 1"
  printf("SQRT accelerator test #1: \n\n");
  while (1){
    printf("Calculate square root of x: y = sqrt(x) \n");
    printf("Enter x: ");
    scanf("%d", &val);
    /* send data to sqrt accelerator */
    pio_write(ACC_VAL_IN_BASE, val);
    /* wait until the division accelerator is ready */
    while (1) {
      ready = pio_read(READY_BASE)& 0x00000001;
      if (ready==1)
        break;
    }
    /* generate a start pulse */
    printf("Start ...\n");
    ready = pio_read(READY_BASE)& 0x00000001;
    printf("ready 1 : %u \n", ready);
    pio_write(START_BASE, 1);
    ready = pio_read(READY_BASE)& 0x00000001;
    printf("ready after write 1: %u \n", ready);
    //printf("debug FSM first: %u \n", pio_read(ACC_RESULT_BASE));
    pio_write(START_BASE, 0);
    ready = pio_read(READY_BASE)& 0x00000001;
        printf("ready after write 0: %u \n", ready);
    /* wait for completion  */
    // while (1) {
      // done = IORD(DONE_TICK_BASE, PIO_EDGE_REG_OFT) & 0x00000001;
      // if (done==1)
        // break;
    // }
    alt_u32 i = 500000;
    while(i > 0){
        i--;
        //if(i%1000 == 0)
        //printf("debug FSM in while: %u \n", pio_read(ACC_RESULT_BASE));
    }
    ready = pio_read(READY_BASE)& 0x00000001;
        printf("ready after loop: %u \n", ready);
    done = pio_read(DONE_TICK_BASE)& 0x00000001;
    printf("done flag: %u \n", done);
    //printf("debug FSM after while: %u \n", pio_read(ACC_RESULT_BASE));
    printf("value on pi_data port after accelerator: %u \n", pio_read(ACC_RESULT_BASE));
    /* clear done_tick register */
    pio_write(DONE_TICK_BASE, 1);
    /* retrieve results from division accelerator */
    res = pio_read(ACC_RESULT_BASE);
    printf("Hardware: sqrt(%u) = %u \n", val, res);
    /* compare results with built-in C operators */
    printf("Software: sqrt(%d) = %d \n", val, (int)sqrt(val));
  } // end while
}


