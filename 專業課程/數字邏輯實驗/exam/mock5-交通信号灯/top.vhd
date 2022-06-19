LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;
USE IEEE.STD_LOGIC_ARITH.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL;
USE IEEE.NUMERIC_STD.ALL;

entity top is
    port(
        rst, pau, cp: in std_logic;
        led_rst, led_red: out std_logic;
        output1, output2: buffer std_logic_vector(3 downto 0);
        div: buffer std_logic
    );
end top;

architecture bhv of top is
    signal cnt: integer := 0;
    signal cnt2: integer := 0;
begin
    process(rst, pau, cp)
        variable tmp: std_logic_vector(3 downto 0);
    begin
        tmp := output1;
        if (rst = '1') then
            output1 <= "0011";
            output2 <= "0011";
            led_rst <= '1';
            led_red <= '0';
            cnt <= 0;
        else
            led_rst <= '0';
            if (pau = '1') then
                output1 <= "1000";
                output2 <= "1000";
                led_red <= '1';
            elsif (cp = '1' and cp'event) then

                if (cnt2 = 1) then
                    div <= not div;
                    cnt2 <= 0;
                else 
                    cnt2 <= cnt2 + 1;
                end if;

                if (pau = '0') then
                    cnt <= cnt + 1;
                    if (tmp > "0011") then
                        output1 <= "0011";
                        output2 <= "0011";
                        led_red <= '0';
                    elsif (tmp = "0011" or tmp = "0000") then
                        led_red <= '0';
                    else
                        led_red <= '1';
                    end if;
                    if (cnt = 1000000) then
                        cnt <= 0;
                        if (output1 /= "0000") then
                            output1 <= output1 - 1;
                            output2 <= output2 - 1;
                        end if;
                    end if;
                end if;
            end if;
        end if;
    end process;
end bhv;