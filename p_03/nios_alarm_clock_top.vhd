library ieee;
use ieee.std_logic_1164.all;
entity nios_alarm_clock_top is
port(
    clk:    in std_logic;
    rst:    in std_logic;
    sw:     in std_logic_vector(2 downto 0);
    key:    in std_logic_vector(2 downto 0);
    ledr:   out std_logic;
    hex5, hex4, hex3, hex2, hex1, hex0: out std_logic_vector(6 downto 0);
    sram_addr:  out   std_logic_vector (17 downto 0);
    sram_dq:    inout std_logic_vector (15 downto 0);
    sram_ce_n, sram_oe_n, sram_we_n: out std_logic;
    sram_lb_n, sram_ub_n:            out std_logic
);
end nios_alarm_clock_top;

architecture behavioral of nios_alarm_clock_top is
   component nios_alarm_clock is
        port (
            clk_clk           : in    std_logic ;                        -- clk
            reset_reset_n     : in    std_logic ;                        -- reset_n
            sw_in_export      : in    std_logic_vector( 2 downto 0);     -- export
            btn_in_export     : in    std_logic_vector( 2 downto 0);     -- export
            ssd_s_out_export  : out   std_logic_vector(15 downto 0);     -- export
            ssd_m_out_export  : out   std_logic_vector(15 downto 0);     -- export
            ssd_h_out_export  : out   std_logic_vector(15 downto 0);     -- export
            ledr_out_export   : out   std_logic;                         -- export
            sram_dq           : inout std_logic_vector(15 downto 0); 	 -- dq
            sram_ce_n         : out   std_logic;                         -- ce_n
            sram_lb_n         : out   std_logic;                         -- lb_n
            sram_ub_n         : out   std_logic;                         -- ub_n
            sram_oe_n         : out   std_logic;                         -- oe_n
            sram_we_n         : out   std_logic;                         -- we_n
            sram_addr         : out   std_logic_vector(17 downto 0)      -- addr
        );
    end component nios_alarm_clock;
   signal ssd_s: std_logic_vector(15 downto 0);
   signal ssd_m: std_logic_vector(15 downto 0);
   signal ssd_h: std_logic_vector(15 downto 0);
   
begin
   nios_unit: nios_alarm_clock 
   port map(
      clk_clk           => clk, 
      reset_reset_n     => rst, 
      btn_in_export     => key,
      sw_in_export      => sw,
      ledr_out_export   => ledr,
      ssd_s_out_export  => ssd_s,
      ssd_m_out_export  => ssd_m,
      ssd_h_out_export  => ssd_h,
      -- SRAM
      sram_addr => sram_addr,
      sram_dq   => sram_dq,
      sram_ce_n => sram_ce_n,
      sram_lb_n => sram_lb_n,
      sram_oe_n => sram_oe_n,
      sram_ub_n => sram_ub_n,
      sram_we_n => sram_we_n
    );
    hex5 <= ssd_h(14 downto 8);       
    hex4 <= ssd_h( 6 downto 0);
    hex3 <= ssd_m(14 downto 8);       
    hex2 <= ssd_m( 6 downto 0);    
    hex1 <= ssd_s(14 downto 8);       
    hex0 <= ssd_s( 6 downto 0);       
end behavioral;
