all: clean
	flex source.lex
	bison -d source.ypp
	g++ -o Hw3 *.c *.cpp
clean:
	rm -f lex.yy.c
	rm -f source.tab.*pp
	rm -f Hw3
