library ieee;
use ieee.std_logic_1164.all;
entity nios_swlu_top is
     port(
       clk: 	in  std_logic;
       rst: 	in  std_logic;
       sw: 		in  std_logic_vector(17 downto 0);
       ledr: 	out std_logic_vector( 7 downto 0)
     );
end nios_swlu_top;

architecture behavioral of nios_swlu_top is
  
     component nios_ii_setup is
        port (
            clk_clk         : in  std_logic                     ; -- clk
            reset_reset_n   : in  std_logic                     ; -- reset_n
            switches_export : in  std_logic_vector(17 downto 0) ; -- export
            leds_export     : out std_logic_vector( 7 downto 0)   -- export
        );
    end component nios_ii_setup;

	 begin
	 
    cpu: component nios_ii_setup
        port map (
            clk_clk         => clk,  -- clk.clk
            reset_reset_n   => rst,  -- reset.reset_n
            switches_export => sw,   -- switches.export
            leds_export     => ledr  -- leds.export
        );
		  
end behavioral;

