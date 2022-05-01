default:
	bison -d parser.y
	flex lexer.l
	gcc -o toy parser.tab.c lex.yy.c 

clean:
	rm lex.yy.c parser.tab.c toy
