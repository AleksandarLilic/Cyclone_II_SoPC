library IEEE;
use IEEE.STD_LOGIC_1164.all;
use IEEE.NUMERIC_STD.all;

entity conv_enc is
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
end conv_enc;

architecture behavioral of conv_enc is
-- Custom Types
type FSM_state is (IDLE, CALC, DONE);
-- constants
-- constant c_ONE      : UNSIGNED(31 DOWNTO 0)         := X"00000001";
-- wires
signal w_cnt_next   : STD_LOGIC_VECTOR( 5 DOWNTO 0) := "000000";
signal w_d0_in      : STD_LOGIC := '0';
signal w_bit_in_fb  : STD_LOGIC := '0';
signal w_bit_d1_d2  : STD_LOGIC := '0';
signal w_bit_in     : STD_LOGIC := '0';
signal w_bit_out    : STD_LOGIC := '0';
-- regs
signal state        : FSM_state := IDLE;
signal state_nx     : FSM_state := IDLE;
signal reg_rdy      : STD_LOGIC := '0';
signal reg_acc_en   : STD_LOGIC := '0';
signal reg_cnt_en   : STD_LOGIC := '0';
signal reg_cnt_rstn : STD_LOGIC := '0';
signal reg_done     : STD_LOGIC := '0';

signal reg_cnt      : STD_LOGIC_VECTOR( 5 DOWNTO 0) := "000000";

signal reg_enc_data : STD_LOGIC_VECTOR(31 DOWNTO 0) := X"00000000";

signal reg_d0_out   : STD_LOGIC := '0';
signal reg_d1_out   : STD_LOGIC := '0';
signal reg_d2_out   : STD_LOGIC := '0';

signal debug        : INTEGER := 0;

begin
-- FSM
    -- process
    fsm_process: process(clk)
	begin 
		if(rising_edge(clk)) then
			if(rstn = '0' or pi_fw_rstn = '0') then
				state <= IDLE;
			else
				state <= state_nx;
			end if;
		end if;
	end process;
    
    -- states
    fsm_state_process: process(state, pi_start, reg_cnt)
    begin
        -- default values:
        state_nx     <= state;
        reg_rdy      <= '0';
        reg_acc_en   <= '0';
        reg_cnt_en   <= '0';
        reg_cnt_rstn <= '1';
        reg_done     <= '0';        
        debug        <= 99;
        
        case(state) is
            when IDLE =>
                debug    <= 1;
                reg_rdy  <= '1';
                if(pi_start = '1') then
                    state_nx     <= CALC;
                    reg_acc_en   <= '1';
                    reg_cnt_en   <= '1';
                    debug <= 2;
                end if;
            
            when CALC =>
                debug      <= 11;
                if(reg_cnt < "100001") then
                    state_nx     <= CALC;
                    reg_acc_en   <= '1';
                    reg_cnt_en   <= '1';
                    debug <= 12;
                else
                    state_nx     <= DONE;
                    reg_cnt_rstn <= '0';
                    reg_acc_en   <= '0';
                    reg_cnt_en   <= '0';
                    debug <= 13;
                end if;
            
            when DONE =>
                state_nx <= IDLE;
                reg_done <= '1';
                debug <= 21;
            
            when others =>
                NULL;
                debug <= 999;
        end case;
    end process;
    
-- counter
    counter_process: process(clk)
	begin
        if(rising_edge(clk)) then
            if(rstn = '0' or pi_fw_rstn = '0' or reg_cnt_rstn = '0') then
                reg_cnt <= "000000";
            else
                reg_cnt <= w_cnt_next;
            end if;
        end if;
	end process;
    
    w_cnt_next <= STD_LOGIC_VECTOR(UNSIGNED(reg_cnt) + 1) when reg_cnt_en = '1' else
                 reg_cnt;

-- data path                  
    -- FF
    ff_process: process(clk)
	begin
        if(rising_edge(clk)) then
            if(rstn = '0' or pi_fw_rstn = '0' ) then
                reg_d0_out <= '0';
                reg_d1_out <= '0';
                reg_d2_out <= '0';
            elsif(reg_acc_en = '1') then
                reg_d0_out <= w_d0_in;
                reg_d1_out <= reg_d0_out;
                reg_d2_out <= reg_d1_out;
            else
                reg_d0_out <= reg_d0_out;
                reg_d1_out <= reg_d1_out;
                reg_d2_out <= reg_d2_out;
            end if;
        end if;
	end process;
     
    w_bit_in    <= reg_enc_data(0);
    w_d0_in     <= w_bit_in    xor w_bit_in_fb;
    w_bit_in_fb <= reg_d1_out  xor reg_d2_out;
    w_bit_d1_d2 <= w_d0_in     xor reg_d0_out;
    w_bit_out   <= w_bit_d1_d2 xor reg_d2_out;
    
    -- shift register
    shift_reg_process: process(clk)
	begin
        if(rising_edge(clk)) then
            if(rstn = '0' or pi_fw_rstn = '0' ) then
                reg_enc_data <= X"00000000";
            elsif(pi_we = '1') then
                reg_enc_data <= pi_data;
            elsif(reg_acc_en = '1') then
                reg_enc_data <= w_bit_out & reg_enc_data(31 DOWNTO 1);
            else
                reg_enc_data <= reg_enc_data;
            end if;
        end if;
	end process;
    
    po_data <= reg_enc_data;
    po_rdy  <= reg_rdy;
    po_done <= reg_done;

end behavioral;
