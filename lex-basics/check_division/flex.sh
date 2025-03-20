#! /bin/sh
flex -l $1.l && gcc -o $1.x lex.yy.c && rm -f lex.yy.c
