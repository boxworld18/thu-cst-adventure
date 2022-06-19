LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;
USE IEEE.STD_LOGIC_ARITH.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL;
USE IEEE.NUMERIC_STD.ALL;

entity top is
    port(
        rst, clk, cp: in std_logic;
        input: in std_logic_vector(3 downto 0);
        output: out std_logic_vector(3 downto 0);
        out_time: out std_logic_vector(3 downto 0)
    );
end top;

architecture bhv of top is
    signal cnt: integer := 0;
    signal time_cnt: std_logic_vector(3 downto 0) := "0000";
    signal start: std_logic := '0';
begin

    process(rst, clk, cp)
    begin
        if (rst = '1') then
            start <= '0';
            time_cnt <= "0000";
            output <= "0000";
            out_time <= "0000";
        elsif (clk = '1') then
            start <= '1';
        elsif (cp = '1' and cp'event) then
            if (start = '1' and cnt = 0 and time_cnt = "0000") then
                start <= '1';
            elsif (cnt = 1000000) then
                if (time_cnt /= "1001") then
                    time_cnt <= time_cnt + 1;
                end if;
                cnt <= 0;
            else
                cnt <= cnt + 1;
            end if;
            if (start = '1' and input /= "0000") then
                start <= '0';
                out_time <= time_cnt;
                if (input(3) = '1') then
                    output <= "1000";
                elsif (input(2) = '1') then
                    output <= "0100";
                elsif (input(1) = '1') then
                    output <= "0010";
                elsif (input(0) = '1') then
                    output <= "0001";
                end if;
            end if;
        end if;
    end process;

end bhv;