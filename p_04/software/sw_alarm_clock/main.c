/***********************************************************************
*
* Module:  Simple alarm clock system using ad hoc driver
* File:    main.c
* Purpose: Task routines and main program
*
***********************************************************************/
/* file inclusion */
#include "system.h"
#include "avalon_gpio.h"
#include "uart_drv.h"
#include "timer_drv.h"

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
    mode_type sw_mode_time_set;
    settings_type sw_set_time_alarm;
    alt_u8 sw_alarm_enable;
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
    alt_u8 btn;
    alt_u8 sw;
    //status_struct *ptr_status = status;
  
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
        
    if (status -> sw_mode_time_set == mode_settings){
        btn = (alt_u8) btn_read(btn_base) & 0x7;    // read 3 pushbuttons
        btn_clear(btn_base);
        if (btn!=0){                                 // a button pressed
            check_btn(btn, status);
        }
    }
}

/***********************************************************************
* function: jtag_uart_disp_msg_v1()
* purpose:  display the interval when it is changed
* argument:
*   jtag_base: base address of JTAG UART
*   *status: pointer to status struct
* return:
* note:
***********************************************************************/
void jtaguart_disp_msg_v1(alt_u32 jtag_base, status_struct *status)
{
    alt_u8 local_h, local_m, local_s;
    static alt_u8 we = 0;
    char msg[] = "T HH:MM:SS    \n";
    if(status -> sw_mode_time_set == mode_time){
        if(status -> uart_send_data){
            we = 1;
            local_h = status -> time_h;
            local_m = status -> time_m;
            local_s = status -> time_s;
            msg[11] = status -> sw_alarm_enable ? '1' : '0';
            msg[13] = status -> alarm_active ? '1' : '0';
            status -> uart_send_data = 0;
        }
    }
    else{ //status -> sw_mode_time_set == mode_settings
        if (status -> chg_h || status -> chg_m || status -> chg_s){ 
        we = 1;
        //button has been pushed:
            //char msg[] = "T HH:MM:SS t\n";
            if(status -> sw_set_time_alarm == mode_time){
                msg[0] = 'V';
                local_h = status -> time_h;
                local_m = status -> time_m;
                local_s = status -> time_s;
            }
            else{ //status -> sw_set_time_alarm == mode_alarm)
                msg[0] = 'A';
                local_h = status -> alarm_h;
                local_m = status -> alarm_m;
                local_s = status -> alarm_s;
            }
            msg[11] = status -> chg_h ? 'H' : 
                      status -> chg_m ? 'M' :
                      status -> chg_s ? 'S' : '0';
            status -> chg_h = 0; 
            status -> chg_m = 0;
            status -> chg_s = 0;
        }
    }
    // write time:
    if(we){
        msg[3] =  local_h % 10 + '0';        // ascii code for 0 digit
        msg[2] = (local_h / 10) % 10 + '0';  // ascii code for 10 digit
        msg[6] =  local_m % 10 + '0';        // ascii code for 0 digit
        msg[5] = (local_m / 10) % 10 + '0';  // ascii code for 10 digit
        msg[9] =  local_s % 10 + '0';        // ascii code for 0 digit
        msg[8] = (local_s / 10) % 10 + '0';  // ascii code for 10 digit
        jtaguart_wr_str(jtag_base, msg);
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
    //int pd;
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
  
    //if (status -> chg_h == 1){
    //    status -> chg_h = 0;
        hex =  local_h % 10;          // 0 digit
        h_char[1] = ssd_conv_hex(hex);
        hex = (local_h / 10) % 10;    // 10 digit
        h_char[0] = ssd_conv_hex(hex);
    //}
    
    //if (status -> chg_m == 1){
    //    status -> chg_m = 0;
        hex =  local_m % 10;          // 0 digit
        m_char[1] = ssd_conv_hex(hex);
        hex = (local_m / 10) % 10;    // 10 digit
        m_char[0] = ssd_conv_hex(hex);        
   // }
    
    //if (status -> chg_s == 1){
    //    status -> chg_s = 0;
        hex =  local_s % 10;          // 0 digit
        s_char[1] = ssd_conv_hex(hex);
        hex = (local_s / 10) % 10;    // 10 digit
        s_char[0] = ssd_conv_hex(hex);        
    //}
  
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
void timer_inc(status_struct *status, alt_u32 timer_base)
{
    static alt_u8 timer_fired = 0;
    static alt_u16 time_ms = 0;
    static alt_u16 alarm_ms = 0;
    
    if (timer_read_tick(timer_base) == 1){
        timer_clear_tick(timer_base);
        timer_fired = 1;
    }
    // stop counter if current time has to be set
    if(!((status -> sw_mode_time_set == mode_settings) & (status -> sw_set_time_alarm == set_time))){
        if(timer_fired)
            time_ms++;
        if(time_ms == 1000){
            status -> time_s ++;
            // status -> chg_s = 1;
            time_ms = 0;
            status -> uart_send_data = 1;
        } // end if
        if(status -> time_s == 60){
            status -> time_m ++;
            //  status -> chg_m = 1;
            status -> time_s = 0;
        } // end if
        if(status -> time_m == 60){
            status -> time_h ++;
            //  status -> chg_h = 1;
            status -> time_m = 0;
        } // end if
        if(status -> time_h == 24){
            status -> time_h = 0;
        } // end if
    }
    
    if(status -> alarm_active){
        if(timer_fired){
            alarm_ms++;
        }
        if(alarm_ms >= 5000){
            status -> alarm_active = 0;
            alarm_ms = 0;
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
    if(!(status -> alarm_active)){
        alt_u8 eq_h = status -> time_h == status -> alarm_h;
        alt_u8 eq_m = status -> time_m == status -> alarm_m;
        alt_u8 eq_s = status -> time_s == status -> alarm_s;
        
        if(eq_h & eq_m & eq_s){
            status -> alarm_active = 1;
        }
    }
}

int main(){
    status_struct status;
    // initial settings
    flashsys_init_v1(BTN_BASE, USR_TIMER_BASE, LEDR_BASE, &status);
    
    //main loop    
    while(1){
        sw_get_command_v1(BTN_BASE, SW_BASE, &status);
        timer_inc(&status, USR_TIMER_BASE); 
        ssd_disp_msg_v1(&status);
        jtaguart_disp_msg_v1(JTAG_UART_BASE, &status);
        if(status.sw_alarm_enable)
            alarm_check(&status);        
        pio_write(LEDR_BASE, status.alarm_active);
        
    }    
}// main
