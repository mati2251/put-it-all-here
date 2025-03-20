%{
  #include <stdio.h>
  int yywrap(void);
  int yylex(void);
%}
%s NEWLINE
%s COMMENT
%%
<INITIAL>; { BEGIN(NEWLINE); printf("%s", yytext); }
<NEWLINE>[^( \n\t)] { printf("\n%s", yytext); BEGIN(INITIAL); }
<NEWLINE>\/\/ { printf("/*"); BEGIN(COMMENT); }
<NEWLINE>\n { BEGIN(INITIAL); printf("\n"); }
<COMMENT>\n { printf(" */\n"); BEGIN(INITIAL); }
%%
int yywrap(void) { return 1; }
int main(void) { return yylex(); }
