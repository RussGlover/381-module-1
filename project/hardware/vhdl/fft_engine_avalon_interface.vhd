library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.math_real.all;
use ieee.math_complex.all;
library std;
use std.textio.all;
 
library work;
use work.fft_len.all;
use work.icpx.all;
-------------------------------------------------------------------------------
 
entity fft_engine_avalon_interface is
 PORT ( clk, rst_n : IN STD_LOGIC;
	read_en, write_en : IN STD_LOGIC;
	writedata : IN STD_LOGIC_VECTOR(31 DOWNTO 0);
	readdata : OUT STD_LOGIC_VECTOR(31 DOWNTO 0);
	address : IN STD_LOGIC_VECTOR(2 DOWNTO 0)	
	);
end fft_engine_avalon_interface;
 
-------------------------------------------------------------------------------
 
architecture interface of fft_engine_avalon_interface is

  constant ADDR_WIDTH : integer := LOG2_FFT_LEN;
  constant FFT_LEN    : integer := 2 ** LOG2_FFT_LEN;
  constant ZERO 		 : integer := 0;
  
  component fft_engine
    generic (
      LOG2_FFT_LEN : integer);
    port (
      din       : in  icpx_number;
      addr_in   : in  integer;
      wr_in     : in  std_logic;
      dout      : out icpx_number;
      addr_out  : in  integer;
      ready     : out std_logic;
      busy      : out std_logic;
      start     : in  std_logic;
      rst_n     : in  std_logic;
      syn_rst_n : in  std_logic;
      clk       : in  std_logic);
  end component;
  
  signal din       : icpx_number := icpx_zero;
  signal addr_in   : integer     := 0;
  signal wr_in     : std_logic   := '0';
  signal dout      : icpx_number := icpx_zero;
  signal addr_out  : integer     := 0;
  signal ready     : std_logic   := '0';
  signal start     : std_logic   := '0';
  signal busy      : std_logic   := '0';
  signal syn_rst_n : std_logic   := '0';
  
   -- Function reversing the std_logic_vector was written
  -- by Jonathan Bromley and published on comp.lang.vhdl
  -- Thread: Slicing of an array: wrong direction
  -- https://groups.google.com/forum/#!msg/comp.lang.vhdl/eBZQXrw2Ngk/4H7oL8hdHMcJ
  function rev_slv (a : in std_logic_vector)
    return std_logic_vector is
    variable result : std_logic_vector(a'range);
    alias aa        : std_logic_vector(a'reverse_range) is a;
  begin
    for i in aa'range loop
      result(i) := aa(i);
    end loop;
    return result;
  end;  -- function rev_slv
  
   -- Function for easy conversion of integer indices
  -- std_logic_vectors used to address the memory
  function i2a (
    constant ia : integer)
    return std_logic_vector is
    variable res : std_logic_vector(ADDR_WIDTH-1 downto 0);
  begin  -- i2a
    res := std_logic_vector(to_unsigned(ia, ADDR_WIDTH));
    return res;
  end i2a;
  
  begin
  
  fft_instance : fft_engine
    generic map (
      LOG2_FFT_LEN => LOG2_FFT_LEN)
    port map (
      din       => din,
      addr_in   => addr_in,
      wr_in     => wr_in,
      dout      => dout,
      addr_out  => addr_out,
      ready     => ready,
      busy      => busy,
      start     => start,
      rst_n     => rst_n,
      syn_rst_n => syn_rst_n,
      clk       => clk);
	
	-- purpose: synchronization of reset
	process (clk, rst_n)
	begin  -- process
    if rst_n = '0' then                 -- asynchronous reset (active low)
      syn_rst_n <= '0';
		readdata <= (others => '0');		
    elsif clk'event and clk = '1' then  -- rising clock edge   
  	 syn_rst_n <= rst_n;
	 
	 start <= '0';
	 wr_in <= '0';
	 if( write_en = '1' ) then
		if(address = "111") then 
				syn_rst_n <= '0';
			end if;
										
	 end if;
	 if( ready = '1' ) then
      readdata <= (others => '-');	 
		if( read_en = '1') then
			case address is
				when "011" =>				
					readdata <= icpx2stlv(dout);
				when "100" =>				
					readdata <= (0 => '1' , others => '0');				
				when 	others => null;				
			end case;		
		elsif( write_en = '1' ) then
			case address is
				--writing in a new value			
				when "000" =>					
					din <= stlv2icpx( std_LOGIC_VECTOR(resize(signed(writedata(31 downto 16)), 32) sll 16 )  ) ;					
					addr_in <= to_integer(unsigned(writedata(15 downto 0)));
					wr_in <= '1';											
				--Preparing for reading values
				when "001" =>					
					--addr_out <= to_integer(unsigned(writedata(15 downto 0)));		
					addr_out <= to_integer(unsigned(rev_slv(i2a(to_integer(unsigned(writedata(15 downto 0)))))));	
				--start processing
				when "010" =>					
					start <= '1';	
				--reset manually	
				when "111" =>
					syn_rst_n <= '0';
										
				when others => null;
			end case;
		end if;		
	 else
	  readdata <= (others => '-');
		if( read_en = '1') then
			--Report ready status
			case address is
				when "100" =>				
					readdata <= (0 => ready , others => '0');
				when 	others => null;
			end case;
		end if;
	 end if;
	 
	 end if;
	end process;
		
end interface;								
					
					
					
				
					
		
	 
	