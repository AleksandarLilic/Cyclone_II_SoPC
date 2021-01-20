#include <stdio.h>
#include <math.h>
#include "system.h"
#include "avalon_gpio.h"

int main()
{
  alt_u32 val, res, ready, done;
  alt_u8 sqrt_msg[4]={0x12,0x18,0x2f,0x07};

  sseg_disp_ptn(SSEG_BASE, sqrt_msg);               // display "sqrt"
  printf("\n\n SQRT accelerator test: \n");
  while (1){
    printf("Calculate square root of x: y = sqrt(x) \n");
    printf("Enter x: ");
    scanf("%d", &val);
    // send data to sqrt accelerator
    pio_write(ACC_VAL_IN_BASE, val);
    // wait until the sqrt accelerator is ready
    while (1) {
      ready = pio_read(READY_BASE)& 0x00000001;
      if (ready==1)
        break;
    }
    // generate a start pulse
    printf("Start ...\n");
    pio_write(START_BASE, 1);
    pio_write(START_BASE, 0);
    // wait for completion
    while (1) {
      done = IORD(DONE_TICK_BASE, PIO_EDGE_REG_OFT) & 0x00000001;
      if (done==1)
        break;
    }
    // clear done_tick register 
    pio_write(DONE_TICK_BASE, 1);
    // retrieve results from sqrt accelerator 
    res = pio_read(ACC_RESULT_BASE);
    printf("Hardware: sqrt(%u) = %u \n", val, res);
    // compare results with built-in C operators 
    printf("Software: sqrt(%d) = %d \n", val, (int)sqrt(val));
  } // end while
}


