// file inclusion
// General C library
#include <stdio.h>
// Altera-specific library
#include <io.h>
#include <alt_types.h>
#include <sys/alt_timestamp.h>
#include "system.h"

// address and field definition
#define CONV_ENC_DATA       0
#define CONV_ENC_WE_START   1
#define CONV_ENC_FW_RST     2
#define CONV_ENC_STATUS     3
#define CONV_ENC_CNT_FLD    0x0000ffff
#define CONV_ENC_READY_BIT  0x80000000

#define CALC_SW_CNT         32

char calc_sw_state = '0';

alt_u32 calc_conv_enc_sw(alt_u32 reg, int *ticks)
{
    alt_u32 cnt = 0;
    alt_32 t0, t1, overhead;
    
    // initialize time_stamp timer to 0
    alt_timestamp_start();
    
    // determine the overhead of alt_timestamp()
    t0 = alt_timestamp();
    t1 = alt_timestamp();
    overhead = t1 - t0;
    
    // start actual measurement
    t0 = alt_timestamp();
    
    alt_u8  dout;
    alt_u32 din;
    
    while(cnt < CALC_SW_CNT){
        din = reg & 0x00000001; // mask out last bit
        cnt++;
        // printf("State: %c   ", calc_sw_state);
        switch(calc_sw_state) {            
            case '0':
                if(din == 0){
                    calc_sw_state = '0';
                    dout  = 0;
                }
                else{ //din == 1
                    calc_sw_state = '4';
                    dout  = 1;
                }
                break;
            
            case '1':
                if(din == 0){
                    calc_sw_state = '4';
                    dout  = 0;
                }
                else{ //din == 1
                    calc_sw_state = '0';
                    dout  = 1;
                }
                break;
            
            case '2':
                if(din == 0){
                    calc_sw_state = '5';
                    dout  = 1;
                }
                else{ //din == 1
                    calc_sw_state = '5';
                    dout  = 0;
                }
                break;
            
            case '3':
                if(din == 0){
                    calc_sw_state = '1';
                    dout  = 1;
                }
                else{ //din == 1
                    calc_sw_state = '5';
                    dout  = 0;
                }
                break;
            
            case '4':
                if(din == 0){
                    calc_sw_state = '2';
                    dout  = 1;
                }
                else{ //din == 1
                    calc_sw_state = '6';
                    dout  = 0;
                }
                break;
            
            case '5':
                if(din == 0){
                    calc_sw_state = '6';
                    dout  = 1;
                }
                else{ //din == 1
                    calc_sw_state = '2';
                    dout  = 0;
                }
                break;
                
            case '6':
                if(din == 0){
                    calc_sw_state = '7';
                    dout  = 0;
                }
                else{ //din == 1
                    calc_sw_state = '3';
                    dout  = 1;
                }
                break;
                
            case '7':
                if(din == 0){
                    calc_sw_state = '3';
                    dout  = 0;
                }
                else{ //din == 1
                    calc_sw_state = '7';
                    dout  = 1;
                }
                break;
            
            default:
                break;
        }// end switch
            
        // printf("reg: 0x%08X   \n", reg);
        // printf("          din: 0x%X    \n", din);
        // printf("          dout: 0x%X    \n\n", dout);
        
        reg = (reg >> 1) | (dout << 31); // shift reg right once and add dout on MSBit
        
        // printf("Value of reg is: %d \n\n", reg);
        
    }// end while
    // stop the measurement and update the results
    t1 = alt_timestamp();
    *ticks = (int) (t1-t0-overhead);
    return(reg);
}// calc_conv_enc_sw

alt_u32 calc_conv_enc_hw(alt_u32 conv_enc_base, alt_u32 reg, int *clks)
{
    alt_u32 status, result;
    
    IOWR(conv_enc_base, CONV_ENC_DATA, reg);   // write data
    IOWR(conv_enc_base, CONV_ENC_WE_START, 0); // write dummy data to start operation
    while(1){
    // loop until data is ready
    status=IORD(conv_enc_base, CONV_ENC_STATUS);
    if (status & CONV_ENC_READY_BIT)
        break;
    *clks = (int) (status & CONV_ENC_CNT_FLD);
    result = IORD(conv_enc_base, CONV_ENC_DATA);
   }
    return(result);
}// calc_conv_enc_hw

int main(void){
    alt_u32 data, val_sw, val_hw;
    int ticks, clks;
    int s = 0, c = 0;
    int samples = 10000;
    int i;
    data = 0x00000041;
    printf("Convolutional encoder test: \n");
    
    /* // single round:
    val_sw = calc_conv_enc_sw(data, &ticks);
    val_hw = calc_conv_enc_hw(CONV_ENC_BASE, data, &clks);
    
    // sanity check
    if(val_sw != val_hw)
        printf("Error: data value: %d, SW result: %d, HW result: %d \n", (int)data, (int)val_sw, (int)val_hw );
    
    // printf("Ticks SW: %d;  ", ticks);
    // printf("Clocks HW: %d;  ", clks); */
    
    // samples # of rounds:
    for (i = 0; i < samples; i++){
        val_sw = calc_conv_enc_sw(data, &ticks);
        val_hw = calc_conv_enc_hw(CONV_ENC_BASE, data, &clks);
        
        // sanity check
        if(val_sw != val_hw)
            printf("Error: data value: %d, SW result: %d, HW result: %d ; Round #: %d \n", (int)data, (int)val_sw, (int)val_hw, i);
        s = s + ticks;
        c = c + clks;
    }
    
    printf("Average clocks SW/HW: %d/%d;  ", s/samples, c/samples);
    printf("HW speedup: %d;  /n", s/c);
}
