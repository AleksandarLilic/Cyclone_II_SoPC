# Cyclone II SoPC projects

**Description:**

VHDL hardware accelerators design on Cyclone II FPGA with microcontroller applications written in C for Nios II core  

Homework assignments as a part of Embedded systems design course  

Projects cover a range of applications for System on Programmable Chip. The development board used for the project is Altera DE2 with Cyclone II FPGA and Nios II softcore. Every project is a two-part design: hardware description of CPU core with peripherals and accelerators, and C application. Each project has *.sopcinfo* file available and pin assignments *.csv* that are used in a particular design.

**Status:**   
Ongoing, projects are uploaded as they are being developed  

**Further development:**  
TBD  

## **Project 8: Convolutional Encoder**  

**Description:**  

Hardware design of a 32-bit convolutional encoder. Interaction between is achieved through one 32-bit shift register with parallel write from CPU and serial read and write from the accelerator. Simple 6-bit counter is used as a control parameter together with FSM. Accelerator is implemented as an IP Core/Qsys component in the Nios II system.  

Software is used as a testing platform to confirm values produced by the hardware accelerator - same encoding scheme is implemented as a C function. Additionally, both hardware and software solutions have execution timers which are used to measure performance difference between the two implementations.

Interaction between accelerator and Nios II core is achieved via memory mapped registers as follows:  
 - 00: DATA - Memory mapped register
   - 32-bit unsigned integer, current data value in the accelerator  
   - if (READY == 1), data in the register is the last calculated value  
 - 01: WE/START - Accelerator write enable and start signal [CPU write] 
   - 0 - NULL  
   - 1 - Load value and start new calculation, valid only if (READY == 1)  
 - 10: FW RESET - Accelerator reset signal [CPU write] 
   - 0 - NULL  
   - 1 - Reset accelerator data path  
 - 11: STATUS - Accelerator status and clock count [CPU read]  
   - 32-bit unsigned integer
   - STATUS[31] stores the current status of the accelerator:  
     - 0 - Busy  
     - 1 - Ready
   - STATUS[30:16] always evaluate to zero
   - STATUS[15:0] represent the number of clock cycles it took for accelerator to produce the final value on the output
 
\* Note: Two 1-bit registers do not hold an actual value but are used just to trigger a specific command or get status   

**Performance metrics:**  
Average number of clock cycles needed for encoding 10 000 samples of data, with both Nios 2 CPU and the accelerator driven from the same 50MHz PLL:
 - SW: 15 334 ticks
 - HW: 34 clock cycles
 - Speedup: SW/HW = x451
 
**Peripherals used:**  
*Timer*: software run-time recording  
*JTAG UART*: data output

**Branch:**  
p_08_dev  

**Status:**   
Ongoing 

## **Project 7: Altera DE2 onboard RAM integration**  

**Description:**  

System integration of two RAM chips on the Altera DE2 development board.     
Memory modules:  
 - SRAM: ISSI IS61LV25616AL, 256Kx16, as Avalon MM Slave/SoPC component  
 - SDRAM: ICSI IS42S16400, 4Mx16, as IP Core/Qsys SDRAM controller  
 
Altera PLL is utilized in order to synchronize off-chip SDRAM timings with the main system. This is achieved with a phase shift of -3ns/-54deg for SDRAM module.  

Software is used as a testing platform to confirm memories read and write. Errors are injected on purpose in the last four memory locations. Software test function checks both SRAM and SDRAM modules.  
 
**Peripherals used:**  
*GPIO*: communication with the off-chip memory modules

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

**Peripherals used:**  
*GPIO*: Seven-segment display  
*JTAG UART*: data input and output  

**Branch:**  
p_06_dev  

**Status:**   
Finished  

## **Project 4 & 5: Alarm clock with HAL & IRQ**  

**Description:**  

Improved Alarm clock SW application with the use of HAL for timer and UART peripherals and IRQ for timer and push buttons PIO. Two things are achieved with this approach compared to Project 3 version:  
 - Improved portability due to HAL and 
 - Added determinism thru interrupts.  
 
**Peripherals used:**  
*GPIO*: Seven-segment display, pushbuttons, switches and LED  
*Timer*:  Two timers, system and user     
*JTAG UART*: data output  

**Branch:**  
p_04_dev  

**Status:**   
Finished  

## **Project 3: Alarm clock**  

**Description:**  

Alarm clock SW application. Allows for setting time and alarm through switches/buttons, uses JTAG UART to displays current values/status and changes made thru settings and LED to signal the alarm activation.

**Peripherals used:**  
*GPIO*: Seven-segment display, pushbuttons, switches and LED  
*Timer*:  Two timers, system and user     
*JTAG UART*: data output  

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
        
Operands and opcode are set through 18 slide switches with padding on the two most significant bits of the *b* operand. The result is displayed on 8 red LEDs. Switch for a microcontroller reset. The external crystal used is 50MHz.  

**Peripherals used:**  
*GPIO*: switches, button and LEDs    

**Status:**   
Finished

## **Project 1: Flashing LED**

**Description:**  

Introductory HW project to get familiar with the IDE and implementation process.  
Two LEDs are flashing with the period assigned thru 10 slide switches. Play/Pause button for enabling and disabling counter. The external crystal used is 50MHz.  

**Peripherals used:**  
*GPIO*: switches, button and LEDs

**Status:**   
Finished
