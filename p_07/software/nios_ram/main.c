#include <stdio.h>
#include <alt_types.h>
#include "system.h"

/**************************************************************
 * function: check_mem()
 * purpose:  check memory within specified region
 * argument:
 *   mem_base: base address of memory
 *   min: lower boundary (address offset) of the test region
 *   max: upper boundary (address offset) of the test region
 * return:
 *   # of errors
 * note:
 *  - the routine is designed for 32-bit data
 *  - 4 artificial errors are ejected in the writing process
 *************************************************************/
int check_mem(alt_u32 mem_base, int min, int max)
{
  int err, real_err;
  alt_u32 *pbase;             // pointer to the base address
  alt_u32 i;                  // index used to generated data
  alt_u32 t_pattn=0xfa30fa30; // toggling pattern for data write

  pbase = (alt_u32 *)mem_base;
  err = 0;
  /* write entire test range */
  printf("write started ... \n");
  for (i=min; i<(max-3); i++){
    pbase[i] = i ^ t_pattn;        // invert certain bits
  }
  /* inject 4 errors in the end */
  for (i=max-3; i<=max; i++){
     pbase[i] = i;
  }
  /* read back entire range */
  printf("read back started ...\n");
  for (i=min; i<=max; i++){
     if (pbase[i]!=(i^t_pattn)) {
       err++;
// printf("  error at address %x: 0x%08x (0x%08x expected) \n",
//       (int)i, (int)pbase[i], (int)i^t_pattn);
     }
  }
  real_err= err-4;
  printf("completed with %d actual errors.\n", real_err);
    return(real_err);
}


/***********************************************************************
* function: main()
* purpose:  test entire ranges of off-chip and SRAM and SDRAM
* note:
*   - BSP configuration
*       -  put code in on-chip memory in linker-script page
*       -  enable small-C lib / reduce device driver options
***********************************************************************/
int main()
{
  printf("DE2 external SRAM/SDRAM test \n\n");
  printf("SRAM test: \n");
  check_mem(SRAM_BASE, 0, 0x0001ffff);   // 128K word address space
  printf("\n\nSDRAM test: \n");
  check_mem(SDRAM_BASE, 0, 0x001fffff);  // 2M word address space
}



