%{
  #include <stdio.h>
  int yywrap(void);
  int yylex(void);  
%}
%%
^[ \t]+
%%
int yywrap(void) { return 1; }
int main(void) { return yylex(); }
