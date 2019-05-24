all:
        clear;
        bison -d source.ypp;
        lex source.lex;
        g++ -o hw3 *.c *.cpp;