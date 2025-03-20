%{
  #include <stdio.h>
  int yywrap(void);
  int yylex(void);
  int nums[100];
  int it = 0;
  int res = 0;
%}
%%
[0-9]+  {
          nums[it] = atoi(yytext); 
          res = nums[it];
          it++;
        };
[ ]  {};
\*  {
      it--;
      res *= nums[it-1];
    };
    
\+ {;
      it--;
      res += nums[it-1];
    };
\-  {
      it--;
      res -= nums[it-1];
    };
\/  {
      it--;
      res /= nums[it-1];
    };
\n  {
      printf("%i\n", res);
    }
%%
int yywrap(void) { return 1; }
int main(void) { return yylex(); }
