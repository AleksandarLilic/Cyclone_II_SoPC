/***********************************************************************
*
* Module:  Simple alarm clock system using Altera HAL/C stdlib
* File:    main.c
* Purpose: Task routines and main program
*
***********************************************************************/
/* file inclusion */
/* General C library */
#include <stdio.h>
#include <unistd.h>
/* Altera-specific library */
#include "system.h"
#include "alt_types.h"
#include "timer_drv.h"
#include <sys/alt_alarm.h> //header for alt-nticks and alt.ticks.per.second
/* Module-specific library */
#include "avalon_gpio.h"

/***********************************************************************
* data type definitions
***********************************************************************/
#define USER_JTAG_TIMEOUT   1000 //ms
#define USER_ALARM_TIMEOUT  5000 //ms

typedef enum{
    mode_time,
    mode_settings    
}mode_type;

typedef enum{
    set_time,
    set_alarm    
}settings_type;

typedef struct{
    // switch status
    mode_type       sw_mode_time_set;
    settings_type   sw_set_time_alarm;
    alt_u8          sw_alarm_enable;
    // btn status
    alt_u8 btn_h;
    alt_u8 btn_m;
    alt_u8 btn_s;
    // current time
    alt_u8 time_h;
    alt_u8 time_m;
    alt_u8 time_s;
    // current alarm time
    alt_u8 alarm_h;
    alt_u8 alarm_m;
    alt_u8 alarm_s;
    // alarm active flag
    alt_u8 alarm_active;
    // chag flags time
    alt_u8 chg_h;
    alt_u8 chg_m;
    alt_u8 chg_s;
    // counter enable and status jtag
    alt_u8 uart_send_data;
} status_struct;

alt_u32 isr_timer_base;   // base address of the timer module
alt_u32 sys_ms_tick;      // elapsed ms ticks
alt_u32 isr_btn_base;   // base address of the PIO module
alt_u32 btn_pressed;      // button pressed
alt_u32 btn_status;

static void ms_clock_isr(void* context, alt_u32 id)
{
    /* clear current interrupt condition */
    timer_clear_tick(isr_timer_base);
    /* increment ms tick */
    sys_ms_tick++;
}

static void btn_isr(void* context, alt_u32 id)
{
	printf("btn isr started ");
    /* read 3 pushbuttons */
    btn_status = (alt_u8) btn_read(isr_btn_base) & 0x7;
    printf("btn status: %d, btn_status ");
	/* clear current interrupt condition */
	btn_clear(isr_btn_base);
    /* increment ms tick */
    btn_pressed = 1;
    printf("btn isr finished \n");
}

/***********************************************************************
* function: flashsys_init_v1()
* purpose:  system initialization
* argument:
*   btn_base: base address of pushbutton PIO
*   timer_base: base address of user timer
*   ledr_base: base address of ledr pio
*   status: pointer to status struct
* return:
* note:
***********************************************************************/
void flashsys_init_v1(alt_u32 btn_base, alt_u32 timer_base, alt_u32 ledr_base, status_struct *status)
{
    btn_clear(btn_base);              // clear button edge-capture reg
    IOWR(btn_base, PIO_INTM_REG_OFT, 0x0007);
    timer_wr_per(timer_base, 50000);  // set 1-ms timeout period
    pio_write(ledr_base, 0);
    status -> sw_mode_time_set = mode_time;
    status -> sw_set_time_alarm = set_time;
    status -> time_h = 0;
    status -> time_m = 59;
    status -> time_s = 0;
    status -> alarm_h = 0;
    status -> alarm_m = 59;
    status -> alarm_s = 5;
    status -> alarm_active = 0;    
    status -> chg_h = 0;  
    status -> chg_m = 0;  
    status -> chg_s = 0;  
}
/***********************************************************************
* function: check_btn()
* purpose:  check value of buttons and update struct
* argument:
*   btn: button value read from inputs
*   status: pointer to status struct
* return:
*   updated status
* note:
***********************************************************************/
void check_btn(alt_u8 btn, status_struct *status)
{
    if (btn & 0x01){                           // button 0 pressed    
    status -> chg_s = 1;
        if (status -> sw_set_time_alarm == set_time){
            status -> time_s ++;
            if (status -> time_s == 60){
                status -> time_s = 0;
            }
        }        
        else{
            status -> alarm_s ++;
            if (status -> alarm_s == 60){
                status -> alarm_s = 0;
            }            
        }
    }
    if (btn & 0x02){                           // button 1 pressed
    status -> chg_m = 1;
        if (status -> sw_set_time_alarm == set_time){
            status -> time_m ++;
            if (status -> time_m == 60){
                status -> time_m = 0;
            }
        }        
        else{
            status -> alarm_m ++;
            if (status -> alarm_m == 60){
                status -> alarm_m = 0;
            }            
        }
    }
    if (btn & 0x04){                           // button 2 pressed
    status -> chg_h = 1;
        if (status -> sw_set_time_alarm == set_time){
            status -> time_h ++;
            if (status -> time_h == 24){
                status -> time_h = 0;
            }
        }        
        else{
            status -> alarm_h ++;
            if (status -> alarm_h == 24){
                status -> alarm_h = 0;
            }            
        }
    }
}

/***********************************************************************
* function: sw_get_command_v1()
* purpose:  get command from pushbuttons and switches
* argument:
*   btn_base: base address of pushbutton PIO
*   sw_base: base address of switch PIO
*   *status: pointer to status struct
* return:
*   updated status
* note:
***********************************************************************/
void sw_get_command_v1(alt_u32 btn_base, alt_u32 sw_base, status_struct *status)
{
    //alt_u8 btn;
    alt_u8 sw;
  
    sw = (alt_u8) pio_read(sw_base) & 0x7;    // read 3 switches
    if (sw & 0x01)
        status -> sw_alarm_enable = 1;
    else
        status -> sw_alarm_enable = 0;
  
    if (sw & 0x02)
        status -> sw_set_time_alarm = set_alarm;
    else
        status -> sw_set_time_alarm = set_time;
    
    if (sw & 0x04)
        status -> sw_mode_time_set = mode_settings;
    else
        status -> sw_mode_time_set = mode_time;
        
    if (btn_pressed == 1){ // interrupt occurred
    	printf("should not run ");
    	btn_pressed = 0; // clear global flag
    	if (status -> sw_mode_time_set == mode_settings){ // if in mode that should register btn press
    		check_btn(btn_status, status);
            btn_status = 0;
    	}
    }
}

/**********************************************************************
* function: jtag_uart_disp_msg_v2()
* purpose:  display the interval when it is changed
* argument:
*   *status: pointer to status struct
* return:
* note:
***********************************************************************/
void jtaguart_disp_msg_v2(status_struct *status)
{
    alt_u8 local_h, local_m, local_s;
    static alt_u8 we = 0;
    static char local_mode, local_st1, local_st2;
    
    if(status -> sw_mode_time_set == mode_time){
        if(status -> uart_send_data){
            we = 1;
            local_h = status -> time_h;
            local_m = status -> time_m;
            local_s = status -> time_s;
            local_mode = 'T';
            local_st1 = status -> sw_alarm_enable ? '1' : '0';
            local_st2 = status -> alarm_active ? '1' : '0';
            status -> uart_send_data = 0;
        }
    }
    else{ //status -> sw_mode_time_set == mode_settings
        if (status -> chg_h || status -> chg_m || status -> chg_s){ 
        we = 1;
        // button has been pushed:
            if(status -> sw_set_time_alarm == mode_time){
                local_mode = 'V';
                local_h = status -> time_h;
                local_m = status -> time_m;
                local_s = status -> time_s;
            }
            else{ //status -> sw_set_time_alarm == mode_alarm)
                local_mode = 'A';
                local_h = status -> alarm_h;
                local_m = status -> alarm_m;
                local_s = status -> alarm_s;
            }
            local_st1 = status -> chg_h ? 'H' : 
                        status -> chg_m ? 'M' :
                        status -> chg_s ? 'S' : '0';
            local_st2 = ' ';
            status -> chg_h = 0; 
            status -> chg_m = 0;
            status -> chg_s = 0;
        }
    }
    // write time:
    if(we){
        printf("Interval: %c %02d:%02d:%02d %c %c\n", local_mode, local_h, local_m, local_s, local_st1, local_st2);
        we = 0;
    }
}

/***********************************************************************
* function: ssd_disp_msg_v1()
* purpose:  display current pause status and interval on 6-digit 7-seg LED
* argument:
*   *status: struct_status with data with values to be displayed
* return:
* note:
***********************************************************************/
void ssd_disp_msg_v1(status_struct *status)
{
    alt_u8 hex, h_char[2], m_char[2], s_char[2];
    alt_u8 local_h, local_m, local_s;

    if((status -> sw_mode_time_set == mode_settings) && (status -> sw_set_time_alarm == set_alarm)){ 
        local_s = status -> alarm_s; 
        local_m = status -> alarm_m;
        local_h = status -> alarm_h;
    }
    else{
        local_s = status -> time_s; 
        local_m = status -> time_m;
        local_h = status -> time_h;        
    }
  
    hex =  local_h % 10;          // 0 digit
    h_char[1] = ssd_conv_hex(hex);
    hex = (local_h / 10) % 10;    // 10 digit
    h_char[0] = ssd_conv_hex(hex);

    hex =  local_m % 10;          // 0 digit
    m_char[1] = ssd_conv_hex(hex);
    hex = (local_m / 10) % 10;    // 10 digit
    m_char[0] = ssd_conv_hex(hex);

    hex =  local_s % 10;          // 0 digit
    s_char[1] = ssd_conv_hex(hex);
    hex = (local_s / 10) % 10;    // 10 digit
    s_char[0] = ssd_conv_hex(hex);
  
    ssd_disp_ptn(SSD_H_BASE, h_char); // display h digit
    ssd_disp_ptn(SSD_M_BASE, m_char); // display m digit
    ssd_disp_ptn(SSD_S_BASE, s_char); // display s digit
}

/***********************************************************************
* function: timer_inc()
* purpose:  increase time
* argument:
*   *status: struct_status with data for time value
* return:
* note:
***********************************************************************/
void timer_inc(status_struct *status)
{
    static alt_u8 timer_fired = 0;
    static alt_u16 alarm_s = 0;    
    
    static int last=0;
    
    if ((sys_ms_tick - last) < 1000) // interval not reached (1000ms period)
        return;
    last = sys_ms_tick;
    timer_fired = 1;
    
    // stop counter if current time has to be set
    if(!((status -> sw_mode_time_set == mode_settings) & (status -> sw_set_time_alarm == set_time))){
        if(timer_fired){
            status -> time_s ++;
            status -> uart_send_data = 1;
        } // end if
        if(status -> time_s == 60){
            status -> time_m ++;
            status -> time_s = 0;
        } // end if
        if(status -> time_m == 60){
            status -> time_h ++;
            status -> time_m = 0;
        } // end if
        if(status -> time_h == 24){
            status -> time_h = 0;
        } // end if
    }
    
    if(status -> alarm_active){
        if(timer_fired){ //when timer is fired, start count for duration
            alarm_s++;
        }
        if(alarm_s >= 5){ //alarm ring and LED ON duration (5sec)
            status -> alarm_active = 0;
            alarm_s = 0;
        }
    }
    timer_fired = 0;
}

/***********************************************************************
* function: alarm_check()
* purpose:  compare values, if equal fire alarm
* argument:
*   *status: struct_status with data for time value
* return:
* note:
***********************************************************************/
void alarm_check(status_struct *status)
{
    // function is only called when alarm is enabled
    if(!(status -> alarm_active)){ // if alarm is currently not fired, check it
        alt_u8 eq_h = status -> time_h == status -> alarm_h;
        alt_u8 eq_m = status -> time_m == status -> alarm_m;
        alt_u8 eq_s = status -> time_s == status -> alarm_s;
        
        if(eq_h & eq_m & eq_s){ // if all three values are equal, fire the alarm
            status -> alarm_active = 1;
        }
    }
}

int main(){
    status_struct status;
    // initial settings
    flashsys_init_v1(BTN_BASE, USR_TIMER_BASE, LEDR_BASE, &status);
    /* assign initial values to global variables */
    isr_timer_base = USR_TIMER_BASE;
    sys_ms_tick = 0;
    isr_btn_base = BTN_BASE;
    btn_pressed = 0;
    /* register ISR */
    alt_irq_register(USR_TIMER_IRQ, NULL, ms_clock_isr);
    alt_irq_register(BTN_IRQ, NULL, btn_isr);
    /* main loop */
    
    //enable pio interrupts
   // pio_write(BTN_BASE + PIO_INTM_REG_OFT, 0x7);
    int reg_read = pio_read(BTN_BASE + PIO_INTM_REG_OFT);
    printf("reg read: %d", reg_read);

    //main loop    
    while(1){
        sw_get_command_v1(BTN_BASE, SW_BASE, &status);
        timer_inc(&status); 
        ssd_disp_msg_v1(&status);
        if(status.sw_alarm_enable)
            alarm_check(&status);        
        jtaguart_disp_msg_v2(&status);
        pio_write(LEDR_BASE, status.alarm_active);        
    }    
}// main
