%{
  #include <stdio.h>
  int yywrap(void);
  int yylex(void);
%}
%%
^\ *[0-9]*[05]\ *$ {printf("%s(+)",yytext);}
^\ *[0-9]+\ *$ {printf("%s(-)",yytext);}
%%
int yywrap(void) { return 1; }
int main(void) { return yylex(); }
