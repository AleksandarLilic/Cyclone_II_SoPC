library IEEE;
use IEEE.STD_LOGIC_1164.all;
use IEEE.NUMERIC_STD.all;

entity nios_sqrt_top is
	port(	
        -- system
        clk     : IN  STD_LOGIC;
        rstn    : IN  STD_LOGIC;
        -- status
        hex3, hex2, hex1, hex0: OUT STD_LOGIC_VECTOR(6 DOWNTO 0);
        -- sram
        sram_addr:  OUT     STD_LOGIC_VECTOR (17 DOWNTO 0);
        sram_dq:    INOUT   STD_LOGIC_VECTOR (15 DOWNTO 0);
        sram_ce_n:  OUT     STD_LOGIC;
        sram_oe_n:  OUT     STD_LOGIC;
        sram_we_n:  OUT     STD_LOGIC;
        sram_lb_n:  OUT     STD_LOGIC;
        sram_ub_n:  OUT     STD_LOGIC
	);
end nios_sqrt_top;

architecture behavioral of nios_sqrt_top is
    component nios_sqrt is
        port (
            clk_clk           : in    std_logic                    ;  -- clk
            reset_reset_n     : in    std_logic                    ;  -- reset_n
            acc_val_in_export : out   std_logic_vector(31 downto 0);  -- export
            sseg_export       : out   std_logic_vector(31 downto 0);  -- export
            sram_dq           : inout std_logic_vector(15 downto 0);  -- dq
            sram_ce_n         : out   std_logic;                      -- ce_n
            sram_lb_n         : out   std_logic;                      -- lb_n
            sram_ub_n         : out   std_logic;                      -- ub_n
            sram_oe_n         : out   std_logic;                      -- oe_n
            sram_we_n         : out   std_logic;                      -- we_n
            sram_addr         : out   std_logic_vector(17 downto 0);  -- addr
            start_export      : out   std_logic;                      -- export
            acc_result_export : in    std_logic_vector(31 downto 0) ; -- export
            ready_export      : in    std_logic                     ; -- export
            done_export       : in    std_logic                       -- export
        );
    end component nios_sqrt;
    
signal w_sseg4       :  STD_LOGIC_VECTOR(31 DOWNTO 0) := (others => '0');
signal w_acc_val_in  :  STD_LOGIC_VECTOR(31 DOWNTO 0) := (others => '0');
signal w_acc_res_out :  STD_LOGIC_VECTOR(31 DOWNTO 0) := (others => '0');
signal w_start : STD_LOGIC := '0';
signal w_done  : STD_LOGIC := '0';
signal w_ready : STD_LOGIC := '0';

begin
    -- cpu instantiation
    nios_cpu: component nios_sqrt
        port map (
            clk_clk           => clk,   --  clk.clk
            reset_reset_n     => rstn,  --  reset.reset_n
            acc_val_in_export => w_acc_val_in,  --  acc_val_in.export
            sseg_export       => w_sseg4,       --  sseg.export
            sram_dq           => sram_dq,       --  sram.dq
            sram_ce_n         => sram_ce_n,     --  .ce_n
            sram_lb_n         => sram_lb_n,     --  .lb_n
            sram_ub_n         => sram_ub_n,     --  .ub_n
            sram_oe_n         => sram_oe_n,     --  .oe_n
            sram_we_n         => sram_we_n,     --  .we_n
            sram_addr         => sram_addr,     --  .addr
            start_export      => w_start,       --  start.export
            acc_result_export => w_acc_res_out, --  acc_result.export
            ready_export      => w_ready,       --  ready.export
            done_export       => w_done         --  done.export
        );
    -- accelerator instantiation
    sqrt_i: entity work.sqrt
        port map(
            -- system
            clk  => clk,
            rstn => rstn,
            -- control & status
            pi_start  => w_start,
            po_rdy    => w_ready, 
            po_done   => w_done,
            -- datapath
            pi_data   => w_acc_val_in,
            po_data   => w_acc_res_out
        );

        -- SSEG display   
        hex3 <= w_sseg4(30 downto 24);       
        hex2 <= w_sseg4(22 downto 16);       
        hex1 <= w_sseg4(14 downto 8);       
        hex0 <= w_sseg4(6 downto 0);
        
end behavioral;
