%{
  #include <stdio.h>
  int yywrap(void);
  int yylex(void);
  int operator_count = 0;
  int comment_depth = 0;
%}
%s COMMENT
%%
<INITIAL>"/*"  { BEGIN(COMMENT); comment_depth = 1;}
<INITIAL>\/\/.*\n
<INITIAL>==|!=|<=|>=|&&|\|=|\+|\*|\-|<|>|= { operator_count++; }
<INITIAL>.|\n { }
<COMMENT>"*/" { if(--comment_depth == 0) {BEGIN(INITIAL);} }
<COMMENT>"/*" { comment_depth++; }
<COMMENT>.|\n { }
%%
int yywrap(void) { 
  printf("Number of operators: %d", operator_count);
  return 1; 
  }
int main(void) { return yylex(); }
