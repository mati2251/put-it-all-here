%{
  #include <stdio.h>
  int yywrap(void);
  int yylex(void);
%}
%{
  int col_num = 0;
  int col_it = 0;
%}
%s TABLE
%%
<INITIAL>[0-9]+   {
                    col_num = atoi(yytext);
                    BEGIN TABLE;
                  };
<TABLE>.{5}\    {
                  col_it++;
                  if(col_it == col_num) printf("%s\n", yytext);
                }
<TABLE>\n  {col_it = 0;}
%%
int yywrap(void) { return 1; }
int main(void) { return yylex(); }
