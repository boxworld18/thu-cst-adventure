LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;
USE IEEE.STD_LOGIC_ARITH.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL;
USE IEEE.NUMERIC_STD.ALL;

entity top is
    port(
        rst, clk, cp: in std_logic;
        input: in std_logic_vector(3 downto 0);
        output1: out std_logic_vector(3 downto 0);
        output2: out std_logic_vector(3 downto 0)
    );
end top;

architecture bhv of top is
    signal cnt: integer := 0;
    signal time_cnt: std_logic_vector(3 downto 0) := "0000";
    signal ms_cnt: std_logic_vector(3 downto 0):= "0000";
    signal set: std_logic := '1';
begin

    process(rst, clk, cp)
    begin

        if (rst = '1') then
            set <= '1';
            time_cnt <= "0000";
            ms_cnt <= "0000";
        elsif (clk = '1') then
            set <= '0';
            cnt <= 0;
        elsif (set = '1') then
            time_cnt <= input;
        elsif (cp = '1' and cp'event and set = '0') then
            if not (time_cnt = "0000" and ms_cnt = "0000") then
                if (cnt = 100000) then
                    cnt <= 0;
                    if (ms_cnt = "0000") then
                        ms_cnt <= "1001";
                        time_cnt <= time_cnt - 1;
                    else
                        ms_cnt <= ms_cnt - 1;
                    end if;
                else
                    cnt <= cnt + 1;
                end if;
            end if;
        end if;
        output1 <= time_cnt;
        output2 <= ms_cnt;
    end process;

end bhv;