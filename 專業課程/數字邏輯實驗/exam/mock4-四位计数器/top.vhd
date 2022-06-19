LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;
USE IEEE.STD_LOGIC_ARITH.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL;
USE IEEE.NUMERIC_STD.ALL;

entity top is
    port(
        clk: in std_logic;
        output1: buffer std_logic_vector(3 downto 0);
        output2: buffer std_logic_vector(3 downto 0);
        output3: buffer std_logic_vector(3 downto 0);
        output4: buffer std_logic
    );
end top;

architecture bhv of top is
    signal cnt: integer := 0;
    signal is_start: integer := 0;
begin
    process(clk)
        variable tmp1: std_logic_vector(3 downto 0);
        variable tmp2: std_logic_vector(3 downto 0);
        variable tmp3: std_logic_vector(3 downto 0);
    begin
        tmp1 := output1;
        tmp2 := output2;
        tmp3 := output3;
        if (clk = '1' and clk'event) then
            if (cnt = 10000) then
                if (is_start = 0 and tmp1 = "0000" and tmp2 = "0000" and tmp3 = "0000") then
                    output4 <= '1';
                    output1 <= output1 + 1;
                    is_start <= 1;
                elsif (output4 = '0' and tmp3 = "1000" and tmp2 = "0110" and tmp1 = "1001") then
                    
                elsif (output1 = "1001") then
                    output1 <= "0000";
                    if (output2 = "1001") then
                        output2 <= "0000";
                        if (output3 = "1001") then
                            output4 <= '0';
                            output3 <= "0000";
                        else
                            output3 <= output3 + 1;
                        end if;
                    else
                        output2 <= output2 + 1;
                    end if;
                else 
                    output1 <= output1 + 1;
                end if;
                cnt <= 0;
            else
                cnt <= cnt + 1;
            end if;
        end if;
    end process;
end bhv;