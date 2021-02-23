library IEEE;
use IEEE.STD_LOGIC_1164.all;
use IEEE.NUMERIC_STD.all;

entity nios_ii_conv_enc_top is
	port(	
        -- system
        clk     : IN  STD_LOGIC;
        rstn    : IN  STD_LOGIC;
        -- sram
        sram_addr:  OUT     STD_LOGIC_VECTOR (17 DOWNTO 0);
        sram_dq:    INOUT   STD_LOGIC_VECTOR (15 DOWNTO 0);
        sram_ce_n:  OUT     STD_LOGIC;
        sram_oe_n:  OUT     STD_LOGIC;
        sram_we_n:  OUT     STD_LOGIC;
        sram_lb_n:  OUT     STD_LOGIC;
        sram_ub_n:  OUT     STD_LOGIC
	);
end nios_ii_conv_enc_top;

architecture behavioral of nios_ii_conv_enc_top is
    component nios_ii_conv_enc is
        port (
            clk_clk       : IN    STD_LOGIC                     := 'X';             -- clk
            reset_reset_n : IN    STD_LOGIC                     := 'X';             -- reset_n
            sram_dq       : INOUT STD_LOGIC_VECTOR(15 DOWNTO 0) := (others => 'X'); -- dq
            sram_ce_n     : OUT   STD_LOGIC;                                        -- ce_n
            sram_lb_n     : OUT   STD_LOGIC;                                        -- lb_n
            sram_ub_n     : OUT   STD_LOGIC;                                        -- ub_n
            sram_oe_n     : OUT   STD_LOGIC;                                        -- oe_n
            sram_we_n     : OUT   STD_LOGIC;                                        -- we_n
            sram_addr     : OUT   STD_LOGIC_VECTOR(17 DOWNTO 0)                     -- addr
        );
    end component nios_ii_conv_enc;
    
begin
    -- CPU instance
    nios_ii_cpu: component nios_ii_conv_enc
        port map (
            clk_clk       => clk,           --  clk.clk
            reset_reset_n => rstn,          --  reset.reset_n
            sram_dq       => sram_dq,       --  sram.dq
            sram_ce_n     => sram_ce_n,     --  .ce_n
            sram_lb_n     => sram_lb_n,     --  .lb_n
            sram_ub_n     => sram_ub_n,     --  .ub_n
            sram_oe_n     => sram_oe_n,     --  .oe_n
            sram_we_n     => sram_we_n,     --  .we_n
            sram_addr     => sram_addr      --  .addr
        );

end behavioral;
