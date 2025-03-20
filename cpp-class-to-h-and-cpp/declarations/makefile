DESC_FILE=declarations.l
EXEC_FILE=declarations.out

all: clean $(EXEC_FILE)

$(EXEC_FILE): lex.yy.c
	gcc -o $(EXEC_FILE) lex.yy.c

lex.yy.c: $(DESC_FILE)
	flex -l $(DESC_FILE)

clean:
	rm -f lex.yy.c $(EXEC_FILE)
