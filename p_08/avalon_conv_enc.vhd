library IEEE;
use IEEE.STD_LOGIC_1164.all;
use IEEE.NUMERIC_STD.all;

entity avalon_conv_enc is
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
end avalon_conv_enc;

architecture behavioral of avalon_conv_enc is
-- Custom Types
type FSM_state is (IDLE, CNT);
-- wires
signal w_fw_rstn : STD_LOGIC;
signal w_we      : STD_LOGIC;
signal w_start   : STD_LOGIC;
signal w_rdy     : STD_LOGIC;
signal w_done    : STD_LOGIC;
signal w_din     : STD_LOGIC_VECTOR(31 DOWNTO 0);
signal w_dout    : STD_LOGIC_VECTOR(31 DOWNTO 0);
signal wr_en     : STD_LOGIC;
signal wr_din    : STD_LOGIC;
-- regs
signal state        : FSM_state := IDLE;
signal state_nx     : FSM_state := IDLE;
signal reg_cnt      : UNSIGNED(15 DOWNTO 0);
signal reg_cnt_nx   : UNSIGNED(15 DOWNTO 0);

begin
-- Instance of a Convolutional Encoder accelerator
    conv_enc_I: entity work.conv_enc(behavioral) 
        port map (
            clk        => clk,
            rstn       => rstn,
            -- control & status
            pi_fw_rstn => w_fw_rstn,
            pi_we      => w_we,
            pi_start   => w_start,
            po_rdy     => w_rdy,
            po_done    => w_done,
            -- data path
            pi_data    => w_din,
            po_data    => w_dout
        );

-- Registers
    register_store_process: process(clk)
	begin 
		if(rising_edge(clk)) then
			if(rstn = '0' or w_fw_rstn = '0') then
				w_din <= (others=>'0');
			else
                if wr_din = '1' then
                   w_din <= conv_enc_writedata;
                end if;
			end if;
		end if;
	end process;

-- Decoding
    -- Register offset:
        -- 00: DATA
        -- 01: WE/START
        -- 10: FW RESET
        
    -- Write
    wr_en     <= '1' when conv_enc_write = '1' and conv_enc_chipselect = '1' else
                 '0';
    wr_din    <= '1' when conv_enc_address = "00" and wr_en = '1' else
                 '0';
    w_start   <= '1' when conv_enc_address = "01" and wr_en = '1' else
                 '0';
    w_we      <= '1' when conv_enc_address = "01" and wr_en = '1' else
                 '0';
    w_fw_rstn <= '0' when conv_enc_address = "10" and wr_en = '1' else
                 '1';
    -- Read
    conv_enc_readdata <= w_dout when conv_enc_address = "00" else
                         w_rdy & "000" & x"000" & STD_LOGIC_VECTOR(reg_cnt);

-- HW counter to keep track of execution cycles
    -- FSM process
    fsm_process: process(clk)
	begin 
		if(rising_edge(clk)) then
			if(rstn = '0' or w_fw_rstn = '0') then
				state <= IDLE;
                reg_cnt <= (others => '0');
			else
                state <= state_nx;
                reg_cnt <= reg_cnt_nx;
			end if;
		end if;
	end process;
    
    -- Next state and cnt
    process(state, reg_cnt, w_start, w_done)
    begin
        state_nx   <= state;
        reg_cnt_nx <= reg_cnt;
        
        case(state) is
            when IDLE =>
                if (w_start = '1') then
                    reg_cnt_nx <= X"0001";
                    state_nx   <= CNT;
                end if;
                    
            when CNT =>
                if (w_done = '1') then
                    state_nx   <= IDLE;
                else
                    reg_cnt_nx <= reg_cnt + 1;
                end if;
                
            when others =>
                NULL;
                
        end case;
    end process;
end behavioral;
