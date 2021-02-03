library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
entity avalon_sram is
   port (
      clk, reset: in  std_logic;
      -- avalon-MM slave interface
      address: in std_logic_vector(17 downto 0);
      chipselect_n: in std_logic; 
      byteenable_n: in std_logic_vector(1 downto 0);
      read_n: in std_logic;
      write_n: in std_logic;
      writedata: in std_logic_vector(15 downto 0);  -- from avalon
      readdata: out std_logic_vector(15 downto 0);  -- to avalon
      -- conduit to/from SRAM
      sram_addr: out std_logic_vector (17 downto 0);
      sram_dq: inout std_logic_vector (15 downto 0);
      sram_ce_n: out std_logic;
      sram_lb_n: out std_logic;
      sram_ub_n: out std_logic;
      sram_oe_n: out std_logic;
      sram_we_n: out std_logic     
   );
end avalon_sram;

architecture arch of avalon_sram is
   signal addr_reg: std_logic_vector(17 downto 0);
   signal rdata_reg, wdata_reg: std_logic_vector(15 downto 0);
   signal ce_n_reg, lb_n_reg, ub_n_reg: std_logic;
   signal oe_n_reg, we_n_reg: std_logic;
begin
   -- registers
   process (clk, reset)
   begin
      if reset='1' then
         addr_reg <= (others=>'0');
         rdata_reg <= (others=>'0');
         wdata_reg <= (others=>'0');
         ce_n_reg <= '1';
         lb_n_reg <= '1';
         ub_n_reg <= '1';
         oe_n_reg <= '1';
         we_n_reg <= '1';        
     elsif (clk'event and clk='1') then
         addr_reg <= address;
         rdata_reg <= sram_dq;    
         wdata_reg <= writedata;
         ce_n_reg <= chipselect_n;
         lb_n_reg <= byteenable_n(0);
         ub_n_reg <= byteenable_n(1);
         oe_n_reg <= read_n;
         we_n_reg <= write_n;        
     end if;
   end process;   
   -- to Avalon 
   readdata <= rdata_reg;
   -- to SRAM
   sram_addr <= addr_reg;
   sram_ce_n <= ce_n_reg;
   sram_lb_n <= lb_n_reg;
   sram_ub_n <= ub_n_reg;
   sram_oe_n <= oe_n_reg;
   sram_we_n <= we_n_reg;   
   -- SRAM tristate data bus
   sram_dq <= wdata_reg when we_n_reg='0' else (others=>'Z');
end arch;


