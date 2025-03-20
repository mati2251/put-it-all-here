%{
  #include <stdio.h>
  int yywrap(void);
  int yylex(void);
  int brackets_depth = 1;
%}
%s FUNCTION
%s CLASS
%%
<INITIAL>\{ {BEGIN CLASS; printf("%s", yytext);}
<CLASS>\{ {BEGIN FUNCTION;}
<FUNCTION>\{  {brackets_depth++;}
<FUNCTION>\}  {
                brackets_depth--; 
                if(brackets_depth == 0) {BEGIN CLASS; brackets_depth = 1; }
              }
<FUNCTION>(.|\n) {}
%%
int yywrap(void) { return 1; }
int main(void) { return yylex(); }
