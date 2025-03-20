%{
  #include <stdio.h>
  int yywrap(void);
  int yylex(void);
%}
%s CODE
%%
<INITIAL><[pP][rR][eE]> { BEGIN CODE; }
<INITIAL>. {}
<INITIAL>\n {}
<CODE><\/[pP][rR][eE]> { BEGIN INITIAL; }
<CODE><.+>
%%
int yywrap(void) { return 1; }
int main(void) { return yylex(); }
