library IEEE;
use IEEE.STD_LOGIC_1164.all;
use IEEE.NUMERIC_STD.all;

entity sqrt_tb is
end sqrt_tb;

architecture rtl_tb of sqrt_tb is

component sqrt
    port(	
        -- system
        clk     : IN  STD_LOGIC;
        rstn    : IN  STD_LOGIC;

        -- control & status
        pi_start    : IN  STD_LOGIC;
        po_rdy      : OUT STD_LOGIC;
        po_done     : OUT STD_LOGIC;
		
        -- datapath
        pi_data     : IN  STD_LOGIC_VECTOR(31 DOWNTO 0);
        po_data     : OUT STD_LOGIC_VECTOR(31 DOWNTO 0)
	);
end component;

signal clk 	    : STD_LOGIC 	:= '0';
signal rstn     : STD_LOGIC 	:= '0';

-- data input
signal reg_pi_start    : STD_LOGIC := '0';
signal reg_po_rdy      : STD_LOGIC := '0';
signal reg_po_done     : STD_LOGIC := '0';
-- datapath
signal reg_pi_data     : STD_LOGIC_VECTOR(31 DOWNTO 0) := (others => '0');
signal reg_po_data     : STD_LOGIC_VECTOR(31 DOWNTO 0) := (others => '0');

constant clk_period 	: time 		:= 20 ns;

begin
    
    uut: sqrt port map(
    clk     =>  clk,
    rstn    =>  rstn,
    -- control & status
    pi_start    =>  reg_pi_start,
    po_rdy      =>  reg_po_rdy,
    po_done     =>  reg_po_done,
    -- datapath
    pi_data     =>  reg_pi_data,
    po_data     =>  reg_po_data
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
		wait for 10 ns;
		wait for clk_period;
		rstn <= '0';
		wait for clk_period*2;
		rstn <= '1';
		wait for clk_period*2;
		reg_pi_start <= '1';
		reg_pi_data <= X"00000057"; -- dec 87
		wait for clk_period;
		reg_pi_start <= '0';
		
		wait for clk_period;
        wait for clk_period*20;
        
        reg_pi_start <= '1';
		reg_pi_data <= X"00000271"; -- dec 625
		wait for clk_period;
		reg_pi_start <= '0';
        
		wait for clk_period*5;
		wait;
	end process;


end;