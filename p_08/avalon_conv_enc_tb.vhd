library IEEE;
use IEEE.STD_LOGIC_1164.all;
use IEEE.NUMERIC_STD.all;

entity avalon_conv_enc_tb is
end avalon_conv_enc_tb;

architecture rtl_tb of avalon_conv_enc_tb is

component avalon_conv_enc
    port(
        -- system
        clk        : IN  STD_LOGIC;
        rstn       : IN  STD_LOGIC;
        -- Avalon interface
        conv_enc_address    : IN  STD_LOGIC_VECTOR( 1 DOWNTO 0);
        conv_enc_chipselect : IN  STD_LOGIC;
        conv_enc_write      : IN  STD_LOGIC;
        conv_enc_writedata  : IN  STD_LOGIC_VECTOR(31 DOWNTO 0);
        conv_enc_readdata   : OUT STD_LOGIC_VECTOR(31 DOWNTO 0)
    );
end component;

-- system
signal clk 	      : STD_LOGIC := '0';
signal rstn       : STD_LOGIC := '1';
signal w_conv_enc_address    : STD_LOGIC_VECTOR( 1 DOWNTO 0):= "00";
signal w_conv_enc_chipselect : STD_LOGIC := '0';
signal w_conv_enc_write      : STD_LOGIC := '0';
signal w_conv_enc_writedata  : STD_LOGIC_VECTOR(31 DOWNTO 0):= X"00000000";
signal w_conv_enc_readdata   : STD_LOGIC_VECTOR(31 DOWNTO 0):= X"00000000";
-- clock period
constant clk_period 	     : TIME 	 := 20 ns;

begin
    uut: avalon_conv_enc 
    port map(
        clk                  => clk                ,
        rstn                 => rstn               ,
        conv_enc_address     => w_conv_enc_address   ,
        conv_enc_chipselect  => w_conv_enc_chipselect,
        conv_enc_write       => w_conv_enc_write     ,
        conv_enc_writedata   => w_conv_enc_writedata ,
        conv_enc_readdata    => w_conv_enc_readdata
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
		wait for clk_period*1;
		rstn <= '1';
		wait for clk_period*1;
        
        -- FW reset
        w_conv_enc_chipselect <= '1';
        w_conv_enc_address <= "10";
		w_conv_enc_write <= '0';
		wait for clk_period*1;
		w_conv_enc_write <= '1';
		wait for clk_period*1;
        
        -- Load data
        w_conv_enc_address <= "00";
		w_conv_enc_writedata <= X"000000FF";
		wait for clk_period;
        
        -- Start calc
        w_conv_enc_address <= "01";
		--w_conv_enc_writedata <= X"00000001";
		wait for clk_period;
        w_conv_enc_write <= '0';
        
		-- CALC + 1
        wait for clk_period;
        w_conv_enc_address <= "00";
        wait for clk_period*34;
        wait for clk_period;
        w_conv_enc_address <= "01";
        wait for clk_period;
        w_conv_enc_address <= "00";
        wait for clk_period*34;
        
        -- Load data
        w_conv_enc_write <= '1';
        w_conv_enc_address <= "00";
        -- w_conv_enc_writedata <= X"000000FF";
        wait for clk_period;
        
        -- Start calc
        w_conv_enc_address <= "01";
        wait for clk_period;
        -- w_conv_enc_write <= '0';
        wait;
        
    end process;
end;
