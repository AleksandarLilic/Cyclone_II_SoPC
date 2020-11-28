library IEEE;
use IEEE.STD_LOGIC_1164.all;
use IEEE.NUMERIC_STD.all;

entity flashing_led_hw is
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
end flashing_led_hw;

architecture behavioral of flashing_led_hw is

-- Signals
constant counter_ms : INTEGER := 50000; -- clock cycles for 1 ms

signal  w_switch_val_ms	: STD_LOGIC_VECTOR(13 DOWNTO 0) 	:= (others => '0');
signal  reg_counter     : STD_LOGIC_VECTOR(15 DOWNTO 0) 	:= (others => '0');
signal  reg_counter_ms  : STD_LOGIC_VECTOR(13 DOWNTO 0) 	:= (others => '0');
signal  w_equality      : STD_LOGIC			:= '0';
signal  w_equality_led  : STD_LOGIC			:= '0';
signal  w_error_period  : STD_LOGIC			:= '0';
signal  reg_status_led  : STD_LOGIC			:= '0';


begin
    
    -- multiply switch value by 5 to get half of period of ms value
    w_switch_val_ms <= STD_LOGIC_VECTOR(shift_left(UNSIGNED("0000" & pi_switch),2)+(UNSIGNED("0000" & pi_switch)));
	 
	 -- error, every switch is at zero
	 w_error_period <=   '1' when w_switch_val_ms = (w_switch_val_ms'range => '0') else
                    '0';
    
    -- 1 ms passed
    w_equality <=   '1' when to_integer(UNSIGNED(reg_counter)) = counter_ms else
                    '0';    
    
    counter_1ms_process: process(clk)
	begin
		if(rising_edge(clk)) then
			if(rst = '1') then
				reg_counter	<= (others => '0');
            elsif(w_equality = '1') then
                reg_counter	<= (others => '0');              
			elsif(pi_btn = '0' and w_error_period = '0') then
				reg_counter <= STD_LOGIC_VECTOR(UNSIGNED(reg_counter) + 1);			
			end if;
		end if;
	end process;    
    
    -- # of ms passed (set from switch)
    w_equality_led <=   '1' when reg_counter_ms = w_switch_val_ms else
                        '0';
                    
    counter_switch_ms_process: process(clk)
	begin
		if(rising_edge(clk)) then
			if(rst = '1') then
				reg_counter_ms	<= (others => '0');
            elsif(w_equality = '1') then
                reg_counter_ms <= STD_LOGIC_VECTOR(UNSIGNED(reg_counter_ms) + 1);                
			elsif(w_equality_led = '1') then
				reg_counter_ms <= (others => '0');			
			end if;
		end if;
	end process;
                      
    status_led_process: process(clk)
	begin
		if(rising_edge(clk)) then
			if(rst = '1') then
				reg_status_led	<= '0';
			elsif(w_equality_led = '1') then
				reg_status_led	<= not reg_status_led;			
			end if;
		end if;
	end process;
    
	po_led_1 <= reg_status_led;
    po_led_2 <= not reg_status_led;

end behavioral;