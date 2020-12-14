# Cyclone II SoPC projects

**Description:**

VHDL hardware accelerators design with microcontroller applications written in C  

Homework assignmets as a part of Embedded systems design course  

Projects cover a range of applications for System on Programable Chip. Development board used for the project is Altera DE2 with Cyclone II FPGA and Nios II soft core. Every project is a two part: hardware description of CPU core with peripherals and accelerators, and C application. Each project has *.sopcinfo* file avalibale and pin assignments *.csv* that are used in a particular project.

**Status:**   
Ongoing, projects are uploaded as they are being developed  

**Further development:**  
n/a  

## **Project 4: Alarm clock wih HAL**

**Description:**  

Improved Alarm clock SW application with the use of HAL. Peripherals used: GPIO for Seven-segment display, Timer and JTAG UART. 

**Status:**   


## **Project 3: Alarm clock**

**Description:**  

Alarm clock SW application. Peripherals used: GPIO for Seven-segment display, Timer and JTAG UART. 

**Status:**   
Finished


## **Project 2: Software Logic Unit**

**Description:**  

Introductory SW & HW project
Software implementation of logic unit thru function:  

    /***********************************************************************
    * function: sw_lu()
    * purpose:  bit operations
    * argument:
    *   a, b : operands
    *   op: op code of a function
    * return:
    *   val : result of a operation
    ***********************************************************************/
    alt_u8 sw_lu(alt_u8 a, alt_u8 b, alt_u8 op);  
        
Peripherals used: GPIO for switches, button and LEDs.  
Operands and opcode are set thru 18 slide switches with padding on *b* operand. Result is displayed on 8 red LEDs. Reset switch. External crystal used is 50MHz.  

**Status:**   
Finished

## **Project 1: Flashing LED**

**Description:**  

Introductory HW project with the aim of getting familiar with IDE and implementation process.  
Peripherals used: GPIO for switches, button and LEDs.  
Two LEDs are flashing with the period assigned thru 10 slide switches. Play/Pause button. External crystal used is 50MHz.  

**Status:**   
Finished
