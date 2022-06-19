LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;
USE IEEE.STD_LOGIC_ARITH.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL;
USE IEEE.NUMERIC_STD.ALL;

entity top is
    port(
        clk, rst, cp: in std_logic;
        led1, led2: out std_logic;
        output: out std_logic_vector(3 downto 0);
        tst: buffer std_logic_vector(4 downto 0)
    );
end top;

architecture bhv of top is
    signal cnt: integer := 0;
    signal tot: integer := 0;
    signal start: integer := 0;
begin
    process(clk, rst, cp)
        variable num: std_logic_vector(4 downto 0) := "00000";
    begin
        if (rst = '1') then
            cnt <= 0;
            tot <= 0;
            led1 <= '0';
            led2 <= '0';
            output <= "0000";
            tst <= "00000";
        elsif (cp = '1' and cp'event and clk = '0' and start = 1) then
            start <= 0;
            num := tst;
            if (cnt < 1000000) then
                num(tot) := '0';
                tst(tot) <= '0';
                led1 <= '1';
                led2 <= '0';
                cnt <= 0;
            else
                num(tot) := '1';
                tst(tot) <= '1';
                led2 <= '1';
                led1 <= '0';
                cnt <= 0;
            end if;
            
            if (tot = 4) then
                case num is
                    when "11110" => output <= "0001";
                    when "11100" => output <= "0010";
                    when "11000" => output <= "0011";
                    when "10000" => output <= "0100";
                    when "00000" => output <= "0101";
                    when "00001" => output <= "0110";
                    when "00011" => output <= "0111";
                    when "00111" => output <= "1000";
                    when "01111" => output <= "1001";
                    when "11111" => output <= "0000";
                    when others => output <= "1111";
                end case;
                tot <= 0;
            else
                tot <= tot + 1;
            end if;

        elsif (cp = '1' and cp'event and clk = '1') then
            start <= 1;
            cnt <= cnt + 1;
        end if;
    end process;
end bhv;