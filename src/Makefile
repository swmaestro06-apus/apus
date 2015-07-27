LEX = lex
YACC = yacc -d

CC = cc

apus: y.tab.o lex.yy.o
	$(CC) -o apus y.tab.o lex.yy.o -ll -lm

lex.yy.o: lex.yy.c y.tab.h

y.tab.c y.tab.h: apus.y
	$(YACC) -v apus.y
lex.yy.c: apus.l
	$(LEX) apus.l
clean:
	-rm -f *.o lex.yy.c *.tab.* apus *.output
