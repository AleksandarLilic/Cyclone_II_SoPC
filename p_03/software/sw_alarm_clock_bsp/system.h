/*
 * system.h - SOPC Builder system and BSP software package information
 *
 * Machine generated for CPU 'cpu' in SOPC Builder design 'nios_alarm_clock'
 * SOPC Builder design path: C:/Users/Aleksandar/Documents/altera_projects/mas_I_esd/p_03/nios_alarm_clock.sopcinfo
 *
 * Generated: Sat Dec 05 13:15:59 CET 2020
 */

/*
 * DO NOT MODIFY THIS FILE
 *
 * Changing this file will have subtle consequences
 * which will almost certainly lead to a nonfunctioning
 * system. If you do modify this file, be aware that your
 * changes will be overwritten and lost when this file
 * is generated again.
 *
 * DO NOT MODIFY THIS FILE
 */

/*
 * License Agreement
 *
 * Copyright (c) 2008
 * Altera Corporation, San Jose, California, USA.
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * This agreement shall be governed in all respects by the laws of the State
 * of California and by the laws of the United States of America.
 */

#ifndef __SYSTEM_H_
#define __SYSTEM_H_

/* Include definitions from linker script generator */
#include "linker.h"


/*
 * CPU configuration
 *
 */

#define ALT_CPU_ARCHITECTURE "altera_nios2_qsys"
#define ALT_CPU_BIG_ENDIAN 0
#define ALT_CPU_BREAK_ADDR 0x80820
#define ALT_CPU_CPU_FREQ 50000000u
#define ALT_CPU_CPU_ID_SIZE 1
#define ALT_CPU_CPU_ID_VALUE 0x00000000
#define ALT_CPU_CPU_IMPLEMENTATION "tiny"
#define ALT_CPU_DATA_ADDR_WIDTH 0x14
#define ALT_CPU_DCACHE_LINE_SIZE 0
#define ALT_CPU_DCACHE_LINE_SIZE_LOG2 0
#define ALT_CPU_DCACHE_SIZE 0
#define ALT_CPU_EXCEPTION_ADDR 0x20
#define ALT_CPU_FLUSHDA_SUPPORTED
#define ALT_CPU_FREQ 50000000
#define ALT_CPU_HARDWARE_DIVIDE_PRESENT 0
#define ALT_CPU_HARDWARE_MULTIPLY_PRESENT 0
#define ALT_CPU_HARDWARE_MULX_PRESENT 0
#define ALT_CPU_HAS_DEBUG_CORE 1
#define ALT_CPU_HAS_DEBUG_STUB
#define ALT_CPU_HAS_JMPI_INSTRUCTION
#define ALT_CPU_ICACHE_LINE_SIZE 0
#define ALT_CPU_ICACHE_LINE_SIZE_LOG2 0
#define ALT_CPU_ICACHE_SIZE 0
#define ALT_CPU_INST_ADDR_WIDTH 0x14
#define ALT_CPU_NAME "cpu"
#define ALT_CPU_RESET_ADDR 0x0


/*
 * CPU configuration (with legacy prefix - don't use these anymore)
 *
 */

#define NIOS2_BIG_ENDIAN 0
#define NIOS2_BREAK_ADDR 0x80820
#define NIOS2_CPU_FREQ 50000000u
#define NIOS2_CPU_ID_SIZE 1
#define NIOS2_CPU_ID_VALUE 0x00000000
#define NIOS2_CPU_IMPLEMENTATION "tiny"
#define NIOS2_DATA_ADDR_WIDTH 0x14
#define NIOS2_DCACHE_LINE_SIZE 0
#define NIOS2_DCACHE_LINE_SIZE_LOG2 0
#define NIOS2_DCACHE_SIZE 0
#define NIOS2_EXCEPTION_ADDR 0x20
#define NIOS2_FLUSHDA_SUPPORTED
#define NIOS2_HARDWARE_DIVIDE_PRESENT 0
#define NIOS2_HARDWARE_MULTIPLY_PRESENT 0
#define NIOS2_HARDWARE_MULX_PRESENT 0
#define NIOS2_HAS_DEBUG_CORE 1
#define NIOS2_HAS_DEBUG_STUB
#define NIOS2_HAS_JMPI_INSTRUCTION
#define NIOS2_ICACHE_LINE_SIZE 0
#define NIOS2_ICACHE_LINE_SIZE_LOG2 0
#define NIOS2_ICACHE_SIZE 0
#define NIOS2_INST_ADDR_WIDTH 0x14
#define NIOS2_RESET_ADDR 0x0


/*
 * Define for each module class mastered by the CPU
 *
 */

#define __ALTERA_AVALON_JTAG_UART
#define __ALTERA_AVALON_PIO
#define __ALTERA_AVALON_SYSID_QSYS
#define __ALTERA_AVALON_TIMER
#define __ALTERA_NIOS2_QSYS
#define __AVALON_SRAM


/*
 * System configuration
 *
 */

#define ALT_DEVICE_FAMILY "Cyclone II"
#define ALT_ENHANCED_INTERRUPT_API_PRESENT
#define ALT_IRQ_BASE NULL
#define ALT_LOG_PORT "/dev/null"
#define ALT_LOG_PORT_BASE 0x0
#define ALT_LOG_PORT_DEV null
#define ALT_LOG_PORT_TYPE ""
#define ALT_NUM_EXTERNAL_INTERRUPT_CONTROLLERS 0
#define ALT_NUM_INTERNAL_INTERRUPT_CONTROLLERS 1
#define ALT_NUM_INTERRUPT_CONTROLLERS 1
#define ALT_STDERR "/dev/jtag_uart"
#define ALT_STDERR_BASE 0x810a8
#define ALT_STDERR_DEV jtag_uart
#define ALT_STDERR_IS_JTAG_UART
#define ALT_STDERR_PRESENT
#define ALT_STDERR_TYPE "altera_avalon_jtag_uart"
#define ALT_STDIN "/dev/jtag_uart"
#define ALT_STDIN_BASE 0x810a8
#define ALT_STDIN_DEV jtag_uart
#define ALT_STDIN_IS_JTAG_UART
#define ALT_STDIN_PRESENT
#define ALT_STDIN_TYPE "altera_avalon_jtag_uart"
#define ALT_STDOUT "/dev/jtag_uart"
#define ALT_STDOUT_BASE 0x810a8
#define ALT_STDOUT_DEV jtag_uart
#define ALT_STDOUT_IS_JTAG_UART
#define ALT_STDOUT_PRESENT
#define ALT_STDOUT_TYPE "altera_avalon_jtag_uart"
#define ALT_SYSTEM_NAME "nios_alarm_clock"


/*
 * btn configuration
 *
 */

#define ALT_MODULE_CLASS_btn altera_avalon_pio
#define BTN_BASE 0x81050
#define BTN_BIT_CLEARING_EDGE_REGISTER 0
#define BTN_BIT_MODIFYING_OUTPUT_REGISTER 0
#define BTN_CAPTURE 1
#define BTN_DATA_WIDTH 3
#define BTN_DO_TEST_BENCH_WIRING 0
#define BTN_DRIVEN_SIM_VALUE 0
#define BTN_EDGE_TYPE "FALLING"
#define BTN_FREQ 50000000
#define BTN_HAS_IN 1
#define BTN_HAS_OUT 0
#define BTN_HAS_TRI 0
#define BTN_IRQ 3
#define BTN_IRQ_INTERRUPT_CONTROLLER_ID 0
#define BTN_IRQ_TYPE "EDGE"
#define BTN_NAME "/dev/btn"
#define BTN_RESET_VALUE 0
#define BTN_SPAN 16
#define BTN_TYPE "altera_avalon_pio"


/*
 * hal configuration
 *
 */

#define ALT_MAX_FD 32
#define ALT_SYS_CLK SYS_TIMER
#define ALT_TIMESTAMP_CLK none


/*
 * jtag_uart configuration
 *
 */

#define ALT_MODULE_CLASS_jtag_uart altera_avalon_jtag_uart
#define JTAG_UART_BASE 0x810a8
#define JTAG_UART_IRQ 2
#define JTAG_UART_IRQ_INTERRUPT_CONTROLLER_ID 0
#define JTAG_UART_NAME "/dev/jtag_uart"
#define JTAG_UART_READ_DEPTH 64
#define JTAG_UART_READ_THRESHOLD 8
#define JTAG_UART_SPAN 8
#define JTAG_UART_TYPE "altera_avalon_jtag_uart"
#define JTAG_UART_WRITE_DEPTH 64
#define JTAG_UART_WRITE_THRESHOLD 8


/*
 * ledr configuration
 *
 */

#define ALT_MODULE_CLASS_ledr altera_avalon_pio
#define LEDR_BASE 0x81040
#define LEDR_BIT_CLEARING_EDGE_REGISTER 0
#define LEDR_BIT_MODIFYING_OUTPUT_REGISTER 0
#define LEDR_CAPTURE 0
#define LEDR_DATA_WIDTH 1
#define LEDR_DO_TEST_BENCH_WIRING 0
#define LEDR_DRIVEN_SIM_VALUE 0
#define LEDR_EDGE_TYPE "NONE"
#define LEDR_FREQ 50000000
#define LEDR_HAS_IN 0
#define LEDR_HAS_OUT 1
#define LEDR_HAS_TRI 0
#define LEDR_IRQ -1
#define LEDR_IRQ_INTERRUPT_CONTROLLER_ID -1
#define LEDR_IRQ_TYPE "NONE"
#define LEDR_NAME "/dev/ledr"
#define LEDR_RESET_VALUE 0
#define LEDR_SPAN 16
#define LEDR_TYPE "altera_avalon_pio"


/*
 * sram configuration
 *
 */

#define ALT_MODULE_CLASS_sram avalon_sram
#define SRAM_BASE 0x0
#define SRAM_IRQ -1
#define SRAM_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SRAM_NAME "/dev/sram"
#define SRAM_SPAN 524288
#define SRAM_TYPE "avalon_sram"


/*
 * ssd_h configuration
 *
 */

#define ALT_MODULE_CLASS_ssd_h altera_avalon_pio
#define SSD_H_BASE 0x81070
#define SSD_H_BIT_CLEARING_EDGE_REGISTER 0
#define SSD_H_BIT_MODIFYING_OUTPUT_REGISTER 0
#define SSD_H_CAPTURE 0
#define SSD_H_DATA_WIDTH 16
#define SSD_H_DO_TEST_BENCH_WIRING 0
#define SSD_H_DRIVEN_SIM_VALUE 0
#define SSD_H_EDGE_TYPE "NONE"
#define SSD_H_FREQ 50000000
#define SSD_H_HAS_IN 0
#define SSD_H_HAS_OUT 1
#define SSD_H_HAS_TRI 0
#define SSD_H_IRQ -1
#define SSD_H_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SSD_H_IRQ_TYPE "NONE"
#define SSD_H_NAME "/dev/ssd_h"
#define SSD_H_RESET_VALUE 0
#define SSD_H_SPAN 16
#define SSD_H_TYPE "altera_avalon_pio"


/*
 * ssd_m configuration
 *
 */

#define ALT_MODULE_CLASS_ssd_m altera_avalon_pio
#define SSD_M_BASE 0x81080
#define SSD_M_BIT_CLEARING_EDGE_REGISTER 0
#define SSD_M_BIT_MODIFYING_OUTPUT_REGISTER 0
#define SSD_M_CAPTURE 0
#define SSD_M_DATA_WIDTH 16
#define SSD_M_DO_TEST_BENCH_WIRING 0
#define SSD_M_DRIVEN_SIM_VALUE 0
#define SSD_M_EDGE_TYPE "NONE"
#define SSD_M_FREQ 50000000
#define SSD_M_HAS_IN 0
#define SSD_M_HAS_OUT 1
#define SSD_M_HAS_TRI 0
#define SSD_M_IRQ -1
#define SSD_M_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SSD_M_IRQ_TYPE "NONE"
#define SSD_M_NAME "/dev/ssd_m"
#define SSD_M_RESET_VALUE 0
#define SSD_M_SPAN 16
#define SSD_M_TYPE "altera_avalon_pio"


/*
 * ssd_s configuration
 *
 */

#define ALT_MODULE_CLASS_ssd_s altera_avalon_pio
#define SSD_S_BASE 0x81090
#define SSD_S_BIT_CLEARING_EDGE_REGISTER 0
#define SSD_S_BIT_MODIFYING_OUTPUT_REGISTER 0
#define SSD_S_CAPTURE 0
#define SSD_S_DATA_WIDTH 16
#define SSD_S_DO_TEST_BENCH_WIRING 0
#define SSD_S_DRIVEN_SIM_VALUE 0
#define SSD_S_EDGE_TYPE "NONE"
#define SSD_S_FREQ 50000000
#define SSD_S_HAS_IN 0
#define SSD_S_HAS_OUT 1
#define SSD_S_HAS_TRI 0
#define SSD_S_IRQ -1
#define SSD_S_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SSD_S_IRQ_TYPE "NONE"
#define SSD_S_NAME "/dev/ssd_s"
#define SSD_S_RESET_VALUE 0
#define SSD_S_SPAN 16
#define SSD_S_TYPE "altera_avalon_pio"


/*
 * sw configuration
 *
 */

#define ALT_MODULE_CLASS_sw altera_avalon_pio
#define SW_BASE 0x81060
#define SW_BIT_CLEARING_EDGE_REGISTER 0
#define SW_BIT_MODIFYING_OUTPUT_REGISTER 0
#define SW_CAPTURE 0
#define SW_DATA_WIDTH 3
#define SW_DO_TEST_BENCH_WIRING 0
#define SW_DRIVEN_SIM_VALUE 0
#define SW_EDGE_TYPE "NONE"
#define SW_FREQ 50000000
#define SW_HAS_IN 1
#define SW_HAS_OUT 0
#define SW_HAS_TRI 0
#define SW_IRQ -1
#define SW_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SW_IRQ_TYPE "NONE"
#define SW_NAME "/dev/sw"
#define SW_RESET_VALUE 0
#define SW_SPAN 16
#define SW_TYPE "altera_avalon_pio"


/*
 * sys_timer configuration
 *
 */

#define ALT_MODULE_CLASS_sys_timer altera_avalon_timer
#define SYS_TIMER_ALWAYS_RUN 0
#define SYS_TIMER_BASE 0x81020
#define SYS_TIMER_COUNTER_SIZE 32
#define SYS_TIMER_FIXED_PERIOD 0
#define SYS_TIMER_FREQ 50000000
#define SYS_TIMER_IRQ 0
#define SYS_TIMER_IRQ_INTERRUPT_CONTROLLER_ID 0
#define SYS_TIMER_LOAD_VALUE 49999
#define SYS_TIMER_MULT 0.0010
#define SYS_TIMER_NAME "/dev/sys_timer"
#define SYS_TIMER_PERIOD 1
#define SYS_TIMER_PERIOD_UNITS "ms"
#define SYS_TIMER_RESET_OUTPUT 0
#define SYS_TIMER_SNAPSHOT 1
#define SYS_TIMER_SPAN 32
#define SYS_TIMER_TICKS_PER_SEC 1000.0
#define SYS_TIMER_TIMEOUT_PULSE_OUTPUT 0
#define SYS_TIMER_TYPE "altera_avalon_timer"


/*
 * sysid_qsys_0 configuration
 *
 */

#define ALT_MODULE_CLASS_sysid_qsys_0 altera_avalon_sysid_qsys
#define SYSID_QSYS_0_BASE 0x810a0
#define SYSID_QSYS_0_ID 4
#define SYSID_QSYS_0_IRQ -1
#define SYSID_QSYS_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SYSID_QSYS_0_NAME "/dev/sysid_qsys_0"
#define SYSID_QSYS_0_SPAN 8
#define SYSID_QSYS_0_TIMESTAMP 1607166877
#define SYSID_QSYS_0_TYPE "altera_avalon_sysid_qsys"


/*
 * usr_timer configuration
 *
 */

#define ALT_MODULE_CLASS_usr_timer altera_avalon_timer
#define USR_TIMER_ALWAYS_RUN 0
#define USR_TIMER_BASE 0x81000
#define USR_TIMER_COUNTER_SIZE 32
#define USR_TIMER_FIXED_PERIOD 0
#define USR_TIMER_FREQ 50000000
#define USR_TIMER_IRQ 1
#define USR_TIMER_IRQ_INTERRUPT_CONTROLLER_ID 0
#define USR_TIMER_LOAD_VALUE 49999
#define USR_TIMER_MULT 0.0010
#define USR_TIMER_NAME "/dev/usr_timer"
#define USR_TIMER_PERIOD 1
#define USR_TIMER_PERIOD_UNITS "ms"
#define USR_TIMER_RESET_OUTPUT 0
#define USR_TIMER_SNAPSHOT 1
#define USR_TIMER_SPAN 32
#define USR_TIMER_TICKS_PER_SEC 1000.0
#define USR_TIMER_TIMEOUT_PULSE_OUTPUT 0
#define USR_TIMER_TYPE "altera_avalon_timer"

#endif /* __SYSTEM_H_ */
