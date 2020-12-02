library IEEE;
use IEEE.STD_LOGIC_1164.all;
use IEEE.NUMERIC_STD.all;

entity flashing_led_hw_tb is
end flashing_led_hw_tb;

architecture rtl_tb of flashing_led_hw_tb is 

component flashing_led_hw
	port(	
		-- INPUTS
		-- system
		clk		: IN  STD_LOGIC;
		rst		: IN  STD_LOGIC;
		
		-- data input
		pi_switch	: IN  STD_LOGIC_VECTOR(9 DOWNTO 0); -- blinking speed
		pi_btn  	: IN  STD_LOGIC;                    -- play/pause
		
		-- OUTPUTS
		-- data output
		po_led_1		: OUT STD_LOGIC;
        po_led_2		: OUT STD_LOGIC		
	); 
end component;    
   
signal clk 		: STD_LOGIC 	:= '0';
signal rst 		: STD_LOGIC 	:= '0';

signal reg_pi_switch: STD_LOGIC_VECTOR(9 DOWNTO 0)  := (others => '0');
signal reg_pi_btn	: STD_LOGIC  := '0';
signal reg_po_led_1	: STD_LOGIC  := '0';
signal reg_po_led_2	: STD_LOGIC  := '0';

   
constant clk_period 	: time 		:= 20 ns;

begin

	uut: flashing_led_hw port map (
		clk 		=> clk,
		rst 		=> rst,
		pi_switch 	=> reg_pi_switch,
		pi_btn   	=> reg_pi_btn,
		po_led_1 	=> reg_po_led_1,
      po_led_2    => reg_po_led_2
      );

	clk_process :process
	begin
		clk <= '0';
		wait for clk_period/2;
		clk <= '1';
		wait for clk_period/2;
  	end process;
  
	stim_proc: process
	begin  
		wait for 5 ns;
		wait for clk_period*10;
		rst <= '0';
		wait for clk_period*5;
		rst <= '1';
		reg_pi_btn <= '1';
		reg_pi_switch <= "0000000001";
		
		wait for clk_period;
		wait for 30 ms;
		reg_pi_btn <= '0';
		wait for clk_period;
		
		wait for 20 ms;
		reg_pi_btn <= '1';
		wait for 20 ms;
		
		reg_pi_switch <= "0000001001";
		
		wait for clk_period*5;
		wait;
	end process;
end;
