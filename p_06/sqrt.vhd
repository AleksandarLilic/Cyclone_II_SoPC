library IEEE;
use IEEE.STD_LOGIC_1164.all;
use IEEE.NUMERIC_STD.all;

entity sqrt is
	port(	
        -- system
        clk     : IN  STD_LOGIC;
        rst	    : IN  STD_LOGIC;

        -- control & status
        pi_start    : IN  STD_LOGIC;
        po_rdy      : OUT STD_LOGIC;
        po_done     : OUT STD_LOGIC;        
		
        -- datapath
        pi_data     : IN  STD_LOGIC_VECTOR(31 DOWNTO 0);
        po_data     : OUT STD_LOGIC_VECTOR(31 DOWNTO 0)
	);
end sqrt;

architecture behavioral of sqrt is
-- Custom Types
type FSM_state is (IDLE, CALC, DONE);
-- constant
constant c_ONE      : UNSIGNED(31 DOWNTO 0)         := X"00000001";
-- wires
signal w_sum        : UNSIGNED(31 DOWNTO 0)         := (others => '0');

-- regs
signal state    : FSM_state := IDLE;
signal state_nx : FSM_state := IDLE;

signal reg_ready    : STD_LOGIC := '0';
--signal reg_ready_nx : STD_LOGIC := '0';
signal reg_done     : STD_LOGIC := '0';
--signal reg_done_nx  : STD_LOGIC := '0';

signal reg_mask     : STD_LOGIC_VECTOR(31 DOWNTO 0) := (others => '0');
signal reg_mask_nx  : STD_LOGIC_VECTOR(31 DOWNTO 0) := (others => '0');
signal reg_root     : STD_LOGIC_VECTOR(31 DOWNTO 0) := (others => '0');
signal reg_root_nx  : STD_LOGIC_VECTOR(31 DOWNTO 0) := (others => '0');
signal reg_rem      : STD_LOGIC_VECTOR(31 DOWNTO 0) := (others => '0');
signal reg_rem_nx   : STD_LOGIC_VECTOR(31 DOWNTO 0) := (others => '0');

begin

    fsm_process: process(clk)
	 begin
        if(rising_edge(clk)) then
            if(rst = '1') then
                state    <= IDLE;
                reg_mask <= (others => '0');
                reg_root <= (others => '0');
                reg_rem  <= (others => '0');
            else
                state    <= state_nx;
                reg_mask <= reg_mask_nx;
                reg_root <= reg_root_nx;
                reg_rem  <= reg_rem_nx;
            end if;
        end if;
	 end process;
    
    fsm_state_process: process(state, pi_start, pi_data, reg_rem, reg_mask, reg_root, reg_mask_nx, w_sum)
    begin
        -- Default Values:
        state_nx    <= state;
        reg_ready   <= '0';
        reg_done    <= '0';
        reg_mask_nx <= reg_mask;
        reg_root_nx <= reg_root;
        reg_rem_nx  <= reg_rem;
		  
		  
        case(state) is
            when IDLE =>
                reg_ready <= '1';
                if(pi_start = '1') then
                    state_nx <= CALC;
                    reg_mask_nx <= STD_LOGIC_VECTOR(shift_left(c_ONE,2));
                    reg_root_nx <= (others => '0');
                    reg_rem_nx  <= pi_data;
                end if;
                
            when CALC =>
                if(reg_mask > X"00000000") then
                    state_nx <= CALC;
                    if(w_sum <= UNSIGNED(reg_rem)) then
                        reg_rem_nx  <= STD_LOGIC_VECTOR(UNSIGNED(reg_rem) - w_sum);
                        reg_root_nx <= STD_LOGIC_VECTOR(shift_right((UNSIGNED(reg_root) + shift_right(UNSIGNED(reg_mask),2)),2));
                    else
                        reg_root_nx <= STD_LOGIC_VECTOR(shift_right(UNSIGNED(reg_root),1));
                    end if;
                    reg_mask_nx <= STD_LOGIC_VECTOR(shift_right(UNSIGNED(reg_mask_nx),2));
                else
                    state_nx <= DONE;
                end if;
                
            when DONE =>
                state_nx <= IDLE;
                reg_done <= '1';
            
            when others => NULL;
        end case;
    end process;
    
    w_sum <= UNSIGNED(reg_root) + UNSIGNED(reg_mask);
    
    po_rdy  <= reg_ready;
    po_done <= reg_done;
    po_data <= reg_root;

end behavioral;