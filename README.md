# Cyclone II SoPC projects

**Description:**

VHDL hardware accelerators design on Cyclone II FPGA with microcontroller applications written in C for Nios II core  

Homework assignments as a part of Embedded systems design course  

Projects cover a range of applications for System on Programable Chip. The development board used for the project is Altera DE2 with Cyclone II FPGA and Nios II softcore. Every project is a two-part design: hardware description of CPU core with peripherals and accelerators, and C application. Each project has *.sopcinfo* file available and pin assignments *.csv* that are used in a particular design.

**Status:**   
Ongoing, projects are uploaded as they are being developed  

**Further development:**  
TBD  

## **Project 7: Altera DE2 onboard RAM integration**  

**Description:**  

System integration of two RAM chips on the Altera DE2 development board.   
Memory modules:
 - SRAM: ISSI IS61LV25616AL, 256Kx16, as Avalon MM Slave/SoPC component
 - SDRAM: ICSI IS42S16400, 4Mx16, as IP Core/Qsys SDRAM controller
 
Altera PLL is utilized in order to synchronize off-chip SDRAM timings with the main system. This is achieved with a phase shift of -3ns/-54deg for SDRAM module.

Software is used as a testing platform to confirm memories read and write. Errors are injected on purpose at the. Test function checks both SRAM and SDRAM modules.
 
Peripherals used: GPIO for communication with the off-chip memory modules

**Branch:**  
p_07_dev  

**Status:**   
Finished  


## **Project 6: Square root hardware accelerator**  

**Description:**  

Hardware accelerator for the calculation of y = [sqrt(x)] (nearest whole number that is a square root of x), with x being 32-bit wide and y 16-bit wide (y is padded to 32-bits in order to fit in one Nios II register during system integration). Pseudocode for implemented sqrt function:  

    mask = 1 << 30; 
    root = 0; // result after the completion
    rem  = data_in; // value of x
    while(mask){
        if((root + mask) <= rem){
            rem = rem - (root + mask);
            root = root + (2*mask);
        }
        root = root >> 1;
        mask = mask >> 2;
    }  

ASMD for the accelerator architecture: [Diagram](https://github.com/AleksandarLilic/Cyclone_II_SoPC/blob/main/p_06_doc/p_06_asmd.pdf)  

Interaction between accelerator and Nios II core is achieved via GPIO memory mapped registers as follows:  
 - READY : Accelerator status [CPU read]
   - 0 - Busy  
   - 1 - Ready for new calculation  
 - START : Accelerator start signal [CPU write] 
   - 0 - NULL  
   - 1 - Start new calculation (valid only if READY == 1)  
 - DONE_TICK : Current calculation finished pulse [CPU read] 
   - 0 - NULL   
   - 1 - Calculation finished (pulse duration: one clock cycle)  
 - ACC_VAL_IN : Accelerator input value [CPU write]  
   - 32-bit unsigned integer  
 - ACC_RESULT : Accelerator output value [CPU read]  
   - 32-bit unsigned integer  

Peripherals used: GPIO for Seven-segment display and JTAG UART for data input and output.  

**Branch:**  
p_06_dev  

**Status:**   
Finished  

## **Project 4 & 5: Alarm clock with HAL & IRQ**  

**Description:**  

Improved Alarm clock SW application with the use of HAL for timer and UART peripherals and IRQ for timer and push buttons PIO. Two things are achieved with this approach compared to Project 3 version:  
 - Improved portability due to HAL and 
 - Added determinism thru interrupts.  
 
Peripherals used: GPIO for Seven-segment display, pushbuttons, switches and LED, Timer and JTAG UART.  

**Branch:**  
p_04_dev  

**Status:**   
Finished  

## **Project 3: Alarm clock**  

**Description:**  

Alarm clock SW application. Peripherals used: GPIO for Seven-segment display, pushbuttons, switches and LED, Timer and JTAG UART. 

**Status:**   
Finished  

## **Project 2: Software Logic Unit**  

**Description:**  

Introductory SW & HW project
Software implementation of the logic unit thru function:  

    /***********************************************************************
    * function: sw_lu()
    * purpose:  bit operations
    * argument:
    *   a, b: operands
    *   op: opcode of a function
    * return:
    *   val: the result of an operation
    ***********************************************************************/
    alt_u8 sw_lu(alt_u8 a, alt_u8 b, alt_u8 op);  
        
Peripherals used: GPIO for switches, button and LEDs.  
Operands and opcode are set through 18 slide switches with padding on the two most significant bits of the *b* operand. The result is displayed on 8 red LEDs. Switch for a microcontroller reset. The external crystal used is 50MHz.  

**Status:**   
Finished

## **Project 1: Flashing LED**

**Description:**  

Introductory HW project to get familiar with the IDE and implementation process.  
Peripherals used: GPIO for switches, button, and LEDs.  
Two LEDs are flashing with the period assigned thru 10 slide switches. Play/Pause button for enabling and disabling counter. The external crystal used is 50MHz.  

**Status:**   
Finished
