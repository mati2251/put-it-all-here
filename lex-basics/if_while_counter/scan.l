%{
  #include <stdio.h>
  int yywrap(void);
  int yylex(void);
  int if_count = 0;
  int while_count = 0;
%}
%%
.
\n
if[ \n\t]*\(.*\) { if_count ++; }
while[ \n\t]*\(.*\) { while_count ++; }
EOF {}
%%
int yywrap(void) { 
   printf("if_count = %d while_count = %d ", if_count, while_count); 
   return 1; 
   }
int main(void) { return yylex(); }
