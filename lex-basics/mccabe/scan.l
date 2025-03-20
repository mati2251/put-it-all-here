%{
  #include <stdio.h>
  int yywrap(void);
  int yylex(void);
  int brackets_count = 0;
  int zc = 1;
%}
%s CONDITION
%s CASE
%%
<INITIAL>.
<INITIAL>\n
<INITIAL>if[ \n\t]*\(  { BEGIN(CONDITION); brackets_count = 1; zc++; }
<INITIAL>while[ \n\t]*\( { BEGIN(CONDITION); brackets_count = 1; zc++; }
<INITIAL>switch[ \n\t]*\(.+\) { BEGIN(CASE); brackets_count = 0; }
<CONDITION>\( { brackets_count ++; }\
<CONDITION>\) { if(--brackets_count == 0) {BEGIN(INITIAL);} }
<CONDITION>[&|]{2} { zc++; }
<CONDITION>.
<CONDITION>\n
<CASE>case {zc++;}
<CASE>\{ { brackets_count ++; }\
<CASE>\} { if(--brackets_count == 0) {BEGIN(INITIAL);} }
<CASE>.
<CASE>\n
%%
int yywrap(void) { 
    printf("zc: %d", zc);
   return 1; 
   }
int main(void) { return yylex(); }
