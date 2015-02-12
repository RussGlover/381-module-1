LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;
USE IEEE.NUMERIC_STD.ALL;

entity euclidean_interface is
	port(
		clock, reset : in std_logic;
		writedata : in std_logic_vector(255 downto 0);
		readdata : out std_logic_vector(255 downto 0);
		write_n : in std_logic
	);
end euclidean_interface;

architecture behavioural of euclidean_interface is
	component euclidean
	port (
		input1values, input2values : in std_logic_vector(127 downto 0);
		distance : out std_logic_vector(31 downto 0)
	);
	end component;

	signal operand1, operand2 : std_logic_vector(127 downto 0) := (others => '0');
	signal result : std_logic_vector(31 downto 0) := (others => '0');
	signal zeroes : std_logic_vector(223 downto 0) := (others => '0');

	begin
		
		euclidean_distance : euclidean port map(
			input1values => operand1,
			input2values => operand2,
			distance => result
		);

		process(clock, reset)
			begin
				if (reset = '1') then
					operand1 <= (others => '0');
					operand2 <= (others => '0');
				elsif (rising_edge(clock)) then
					if (write_n = '1') then
						operand1 <= writedata(127 downto 0);
						operand2 <= writedata(255 downto 128);
						readdata <= zeroes & result;
					else
						null;
					end if;
				end if;
		end process;

end behavioural;



