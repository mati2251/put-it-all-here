%{
  #include <stdio.h>
  int yywrap(void);
  int yylex(void);
  int nums[100];
  int it = 0;
  int res = 0;
%}
%%
^0*1+$ {printf("%s OK", yytext);};
^.* {printf("%s Error", yytext);};
%%
int yywrap(void) { return 1; }
int main(void) { return yylex(); }
