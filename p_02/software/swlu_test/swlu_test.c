#include "io.h"
#include "alt_types.h"
#include "system.h"


// MACRO
#define POS_A  0
#define POS_B  8
#define POS_OP 14
#define MASK_A  (0xff << POS_A)
#define MASK_B  (0x3f << POS_B)
#define MASK_OP (0x0f << POS_OP)


/***********************************************************************
* function: sw_get_command_v0()
* purpose:  get values from switches
* argument:
*   sw_base: base address of switch PIO
*   sw_cmd: pointer to value (result)
* return:
*   updated per
* note:
***********************************************************************/
void sw_get_command_v0(alt_u32 sw_base, int *sw_cmd)
{
  *sw_cmd = IORD(sw_base, 0) & 0x0003ffff;  // read switch value
}

/***********************************************************************
* function: led_flash_v0()
* purpose:  set LEDs to a given value
* argument:
*   led_base: base address of discrete LED PIO
*   sw_cmd: value to be set
* return:
***********************************************************************/
void led_result_v0(alt_u32 led_base, int val)
{
  IOWR(led_base, 0, val);      // write LEDs
}

/***********************************************************************
* function: sw_lu()
* purpose:  bit operations
* argument:
*   a, b : operands
*   op: op code of a function
* return:
*   val : result of a operation
***********************************************************************/

alt_u8 sw_lu(alt_u8 a, alt_u8 b, alt_u8 op)
{
	alt_u8 val = 0;

  switch(op){
  case 0: // AND
	  val = a & b;
	  break;
  case 1: // OR
	  val = a | b;
	  break;
  case 2: // XOR
	  val = a ^ b;
	  break;
  case 3: // XNOR
	  val = ~(a ^ b);;
	  break;
  case 4: // NAND
	  val = ~(a & b);;
	  break;
  case 5: // NOR
	  val = ~(a | b);;
	  break;
  case 6: // SL
	  val = a << b;
	  break;
  case 7: // SR
	  val = a >> b;
	  break;
  case 8: // ROL
	  val = (a << b) | (a >> (8 - b));
	  break;
  case 9: // ROR
	  val = (a >> b) | (a << (8 - b));
	  break;
  case 10: // SRA
	  val = (a & 128) | ((a & 127) >> b);
	  break;
  case 11: // SETB
	  val = a | (1 << b);
	  break;
  case 12: // CLRB
	  val = a & ~(1 << b);
	  break;
  case 13: // a CPL b
	  val = (a ^ (1 << b));
	  break;
  case 14: // CPL a
	  val = ~a;
	  break;
  case 15: // =a
	  val = a;
	  break;
  default:
	  val = 0;
	  break;
  }
  return val;
}

/***********************************************************************
* function: main()
* purpose:  top-level program
* note:
***********************************************************************/
int main(){
  int sw_cmd;
  alt_u8 a, b, c, op;

  while(1){
    sw_get_command_v0(SWITCH_BASE ,&sw_cmd);

    //read = *sw_cmd;
    //a = (alt_u8) (read);

    a  = (sw_cmd & MASK_A ) >> POS_A;
    b  = (sw_cmd & MASK_B ) >> POS_B;
    op = (sw_cmd & MASK_OP) >> POS_OP;

    c = sw_lu(a, b, op);

    led_result_v0(LED_BASE, c);
  }
}



