LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;
USE IEEE.NUMERIC_STD.ALL;

library work;
use work.sqrt_package.all;

entity euclidean is
	port(
		input1values, input2values : in std_logic_vector(127 downto 0);
		distance : out std_logic_vector(31 downto 0)
	);
end euclidean;

architecture behavioural of euclidean is

signal operand : unsigned(31 downto 0);
signal input0bin0, input0bin1, input0bin2, input0bin3, input0bin4, input0bin5, input0bin6, input0bin7 : signed(15 downto 0);
signal input1bin0, input1bin1, input1bin2, input1bin3, input1bin4, input1bin5, input1bin6, input1bin7 : signed(15 downto 0);

begin
	process(input1values, input2values)
	begin
		input0bin0 <= signed(input1values(15 downto 0));
		input0bin1 <= signed(input1values(31 downto 16));
		input0bin2 <= signed(input1values(47 downto 32));
		input0bin3 <= signed(input1values(63 downto 48));
		input0bin4 <= signed(input1values(78 downto 64));
		input0bin5 <= signed(input1values(95 downto 79));
		input0bin6 <= signed(input1values(111 downto 96));
		input0bin7 <= signed(input1values(127 downto 112));

		input1bin0 <= signed(input1values(15 downto 0));
		input1bin1 <= signed(input1values(31 downto 16));
		input1bin2 <= signed(input1values(47 downto 32));
		input1bin3 <= signed(input1values(63 downto 48));
		input1bin4 <= signed(input1values(78 downto 64));
		input1bin5 <= signed(input1values(95 downto 79));
		input1bin6 <= signed(input1values(111 downto 96));
		input1bin7 <= signed(input1values(127 downto 112));
	end process;

	process(input0bin0, input0bin1, input0bin2, input0bin3, input0bin4, input0bin5, input0bin6, input0bin7, input1bin0, input1bin1, input1bin2, input1bin3, input1bin4, input1bin5, input1bin6, input1bin7)
	begin
		distance <= std_logic_vector(sqrt(to_unsigned((to_integer(input0bin0 - input1bin0)**2) 
						+ (to_integer(input0bin1 - input1bin1)**2) 
						+ (to_integer(input0bin2 - input1bin2)**2)  
						+ (to_integer(input0bin3 - input1bin3)**2)  
						+ (to_integer(input0bin4 - input1bin4)**2)  
						+ (to_integer(input0bin5 - input1bin5)**2) 
						+ (to_integer(input0bin6 - input1bin6)**2)  
						+ (to_integer(input0bin7 - input1bin7)**2), 32)));
	end process;

end behavioural;