LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;
USE IEEE.STD_LOGIC_ARITH.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL;
USE IEEE.NUMERIC_STD.ALL;

entity top is
    port(
        rst, clk, pau, cp, mode: in std_logic;
        output7: out std_logic_vector(6 downto 0);
        div: buffer std_logic
    );
end top;

architecture bhv of top is
    signal cnt: integer := 0;
    signal cnt2: integer := 0;
    signal time_cnt: std_logic_vector(3 downto 0) := "0000";
    signal stop: integer := 0;
    signal output: std_logic_vector(3 downto 0);
    signal start: integer := 0;
begin

    process(rst, cp, mode)
    begin
        if (rst = '1') then
            if (mode = '1') then
                output <= "0101";
            elsif (mode = '0') then
                output <= "0011";
            end if;
        elsif (cp = '1' and cp'event) then
            if (cnt2 = 4999999) then
                div <= not div;
                cnt2 <= 0;
            else 
                cnt2 <= cnt2 + 1;
            end if;

            if (pau = '0' and clk = '1') then
                if (cnt = 1000000) then
                    if (output /= "0000") then
                        output <= output - 1;
                    end if;
                    cnt <= 0;
                elsif (stop = 0) then
                    cnt <= cnt + 1;
                end if;
            end if;
        end if;
    end process;

    process(output)
    begin
        case output is
            when "0000" => output7 <= "1111110";
            when "0001" => output7 <= "0110000";
            when "0010" => output7 <= "1101101";
            when "0011" => output7 <= "1111001";
            when "0100" => output7 <= "0110011";
            when "0101" => output7 <= "1011011";
            when others => output7 <= "0000000";
        end case;
    end process;
end bhv;