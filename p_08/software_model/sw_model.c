#include <stdio.h>

void main(){
    char state = '0';
    unsigned int cnt = 32;
    unsigned int reg = 0x00000041;
    unsigned int dout;
    unsigned int din;
    
    while(cnt>0){
        din = reg & 0x00000001; // mask out last bit
        //printf("reg before case: 0x%08X \n", reg);
       //printf("reg: 0x%08X    ", reg);
       //printf("din: 0x%08X    ", din);
       printf("State: %c   ", state);
       
        switch(state) {
            
            case '0':
                if(din == 0){
                    state = '0';
                    dout  = 0;
                }
                else{ //din == 1
                    state = '4';
                    dout  = 1;
                }
                break;
            
            case '1':
                if(din == 0){
                    state = '4';
                    dout  = 0;
                }
                else{ //din == 1
                    state = '0';
                    dout  = 1;
                }
                break;
            
            case '2':
                if(din == 0){
                    state = '5';
                    dout  = 1;
                }
                else{ //din == 1
                    state = '5';
                    dout  = 0;
                }
                break;
            
            case '3':
                if(din == 0){
                    state = '1';
                    dout  = 1;
                }
                else{ //din == 1
                    state = '5';
                    dout  = 0;
                }
                break;
            
            case '4':
                if(din == 0){
                    state = '2';
                    dout  = 1;
                }
                else{ //din == 1
                    state = '6';
                    dout  = 0;
                }
                break;
            
            case '5':
                if(din == 0){
                    state = '6';
                    dout  = 1;
                }
                else{ //din == 1
                    state = '2';
                    dout  = 0;
                }
                break;
                
            case '6':
                if(din == 0){
                    state = '7';
                    dout  = 0;
                }
                else{ //din == 1
                    state = '3';
                    dout  = 1;
                }
                break;
                
            case '7':
                if(din == 0){
                    state = '3';
                    dout  = 0;
                }
                else{ //din == 1
                    state = '7';
                    dout  = 1;
                }
                break;
            
            default : 
                printf("Error switch case");
        }//end switch
        
        //printf("State new: %c   ", state);
        printf("reg: 0x%08X   \n ", reg);
        printf("          din: 0x%X    \n", din);
        printf("          dout: 0x%X    \n\n", dout);
       // printf("dout shifted: 0x%08X \n", dout << 31);
       // printf("reg shifted: 0x%08X \n", reg >> 1);
        
        reg = (reg >> 1) | (dout << 31); // shift reg right once and add dout on MS Bit
        
        //printf("reg: 0x%08X \n", reg);
        
        cnt--;
    }
    printf("Value of reg final: 0x%08X \n\n", reg);
}
