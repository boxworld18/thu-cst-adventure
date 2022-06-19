LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;
USE IEEE.STD_LOGIC_ARITH.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL;
USE IEEE.NUMERIC_STD.ALL;

entity top is
    port(
        rst, clk, cp: in std_logic;
        led1, led2, led3: out std_logic
    );
end top;

architecture bhv of top is
    signal cnt: integer := 0;
    signal tar: integer := 2500000;
begin
    process(rst, clk, cp)
    begin
        if (rst = '1') then
            led1 <= '0';
            led2 <= '0';
            led3 <= '0';
            cnt <= 0;
        elsif (clk = '1') then
            if (cnt < tar) then
                led2 <= '1';
                led3 <= '1';
            elsif (cnt < tar + 500000) then
                led2 <= '1';
            else
                led3 <= '1';
            end if;
        elsif (cp = '1' and cp'event) then
            cnt <= cnt + 1;
            if (cnt = tar) then
                led1 <= '1';
            end if;
        end if;
    end process;
end bhv;