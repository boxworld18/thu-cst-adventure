main: main.o Parser.o
	g++ -o $@ $^

Parser.o: Parser.cpp Parser.h
	g++ -o $@ -c $<

main.o: main.cpp Parser.h
	g++ -o $@ -c $<

clean: 
	rm -f *.o -f main