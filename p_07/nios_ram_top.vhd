library ieee;
use ieee.std_logic_1164.all;
entity nios_ram_top is
   port(
      clk: in std_logic;
      rst: in std_logic;
      -- to/from SRAM
      sram_addr: out std_logic_vector (17 downto 0);
      sram_dq: inout std_logic_vector (15 downto 0);
      sram_ce_n: out std_logic;
      sram_lb_n: out std_logic;
      sram_oe_n: out std_logic;
      sram_ub_n: out std_logic;
      sram_we_n: out std_logic;
      -- to/from SDRAM side
      dram_clk: out std_logic;
      dram_cs_n, dram_cke: out std_logic;
      dram_ldqm, dram_udqm: out std_logic;
      dram_cas_n, dram_ras_n, dram_we_n: out std_logic;
      dram_addr: out std_logic_vector(11 downto 0);
      dram_ba_0, dram_ba_1: out std_logic;
      dram_dq: inout std_logic_vector(15 downto 0)
   );
end nios_ram_top;

architecture behavioral of nios_ram_top is
   component nios_ram is
        port (
			clk_clk       : in    std_logic;             
			reset_reset_n : in    std_logic;             
			sdram_addr    : out   std_logic_vector(11 downto 0);                    
			sdram_ba      : out   std_logic_vector(1 downto 0);                     
			sdram_cas_n   : out   std_logic;                                        
			sdram_cke     : out   std_logic;                                        
			sdram_cs_n    : out   std_logic;                      
			sdram_dq      : inout std_logic_vector(15 downto 0) ; 
			sdram_dqm     : out   std_logic_vector(1 downto 0);                     
			sdram_ras_n   : out   std_logic;                                        
			sdram_we_n    : out   std_logic;                                        
			sram_dq       : inout std_logic_vector(15 downto 0); 
			sram_ce_n     : out   std_logic;                          
			sram_lb_n     : out   std_logic;
			sram_ub_n     : out   std_logic;
			sram_oe_n     : out   std_logic;                                        
			sram_we_n     : out   std_logic;                                        
			sram_addr     : out   std_logic_vector(17 downto 0);                    
			pll_clk       : out   std_logic;
			pll_areset_export : in    std_logic
        );
    end component nios_ram;
	 signal pll_areset : std_logic;
begin
	pll_areset <= not rst;
   nios: nios_ram
   port map(
      clk_clk => clk,
		reset_reset_n => rst,
      pll_clk => dram_clk,
		pll_areset_export => pll_areset,
      -- SDRAM
      sdram_addr	=> dram_addr,
      sdram_ba(1)	=> dram_ba_1,  
      sdram_ba(0)	=> dram_ba_0,   
      sdram_cas_n	=> dram_cas_n,
      sdram_cke	=> dram_cke,
      sdram_cs_n	=> dram_cs_n,
      sdram_dq		=> dram_dq,
      sdram_dqm(1)=> dram_udqm,
      sdram_dqm(0)=> dram_ldqm,
      sdram_ras_n	=> dram_ras_n,
      sdram_we_n	=> dram_we_n, 
      -- SRAM
      sram_addr 	=> sram_addr,
      sram_ce_n 	=> sram_ce_n,
      sram_dq 		=> sram_dq,
      sram_lb_n 	=> sram_lb_n,
      sram_oe_n 	=> sram_oe_n,
      sram_ub_n 	=> sram_ub_n,
      sram_we_n 	=> sram_we_n
   );
end behavioral;