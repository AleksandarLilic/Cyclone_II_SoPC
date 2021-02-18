library IEEE;
use IEEE.STD_LOGIC_1164.all;
use IEEE.NUMERIC_STD.all;

entity conv_enc_tb is
end conv_enc_tb;

architecture rtl_tb of conv_enc_tb is

component conv_enc
    port(
        -- system
        clk        : IN  STD_LOGIC;
        rstn       : IN  STD_LOGIC;
        -- control & status
        pi_fw_rstn : IN  STD_LOGIC;
        pi_we      : IN  STD_LOGIC;
        pi_start   : IN  STD_LOGIC;
        po_rdy     : OUT STD_LOGIC;
        po_done    : OUT STD_LOGIC;
        -- data path
        pi_data    : IN  STD_LOGIC_VECTOR(31 DOWNTO 0);
        po_data    : OUT STD_LOGIC_VECTOR(31 DOWNTO 0)
	);
end component;

-- system
signal clk 	      : STD_LOGIC := '0';
signal rstn       : STD_LOGIC := '1';
-- signal/control
signal reg_pi_fw_rstn : STD_LOGIC := '1';
signal reg_pi_we      : STD_LOGIC := '0';
signal reg_pi_start   : STD_LOGIC := '0';
signal reg_po_rdy     : STD_LOGIC := '0';
signal reg_po_done    : STD_LOGIC := '0';
-- data path
signal reg_pi_data    : STD_LOGIC_VECTOR(31 DOWNTO 0) := X"00000000";
signal reg_po_data    : STD_LOGIC_VECTOR(31 DOWNTO 0) := X"00000000";
-- clock period
constant clk_period 	: time 		:= 20 ns;

begin
    
    uut: conv_enc port map(
    clk     =>  clk,
    rstn    =>  rstn,
    -- control & status
    pi_fw_rstn=> reg_pi_fw_rstn,
    pi_we     => reg_pi_we     ,
    pi_start  => reg_pi_start  ,
    po_rdy    => reg_po_rdy    ,
    po_done   => reg_po_done   ,
    -- data path
    pi_data   => reg_pi_data   ,
    po_data   => reg_po_data
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
        -- system reset
		rstn <= '0';
		wait for clk_period*2;
		rstn <= '1';
        reg_pi_fw_rstn <= '1';
		wait for clk_period*2;
        
        reg_pi_we <= '1';
		reg_pi_start <= '1';
		reg_pi_data <= X"00000041";
		wait for clk_period;
        reg_pi_we <= '0';
		reg_pi_start <= '0';
		
		wait for clk_period;
        wait for clk_period*20;
        wait;
        
    end process;
    
end;

