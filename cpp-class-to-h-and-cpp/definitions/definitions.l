%{
  #include <stdio.h>
  #include <string.h>
  #include <stdbool.h>

  int yywrap(void);
  int yylex(void);
  char classname[100];
  char functiondeclaration[1000];
  char functiontype[100];
  bool open = false;
  int brackets_depth = 0;
%}
%s CLASS_NAME
%s FUNCTION_TYPE
%s FUNCTION_NAME
%s FUNCTION
keyword [a-zA-Z0-9_]+
%%
<INITIAL>class[ \t\n]* {BEGIN CLASS_NAME;}
<INITIAL>(.|\n) {}
<CLASS_NAME>(.|\n) {}
<CLASS_NAME>{keyword} {strcpy(classname, yytext); BEGIN FUNCTION_TYPE;}
<FUNCTION_TYPE>(\{|\}|;) {}
<FUNCTION_TYPE>(public:)|(private:)|(protected:) {}
<FUNCTION_TYPE>{keyword}\([^()]* {strcpy(functiondeclaration, yytext); open=true;}
<FUNCTION_TYPE>\) {if (open) {
                    strcat(functiondeclaration, yytext); 
                    printf("%s::%s", classname, functiondeclaration);
                    brackets_depth = 0;
                    BEGIN FUNCTION;
                }}
<FUNCTION_TYPE>{keyword}[ \t\n]+ {strcpy(functiontype, yytext); open = false; BEGIN FUNCTION_NAME;}
<FUNCTION_NAME>{keyword}\([^()]* {strcpy(functiondeclaration, yytext); open=true;}
<FUNCTION_NAME>\) {if (open) {
                    strcat(functiondeclaration, yytext); 
                    printf("%s %s::%s", functiontype, classname, functiondeclaration);
                    brackets_depth = 0;
                    BEGIN FUNCTION;
                }}
<FUNCTION_NAME>; {BEGIN FUNCTION_TYPE;}
<FUNCTION_NAME>(.|\n) {}
<FUNCTION_NAME>\{ {}
<FUNCTION_NAME>\} {}
<FUNCTION>\{ {brackets_depth++; printf("%s", yytext);}
<FUNCTION>\} {--brackets_depth; printf("%s", yytext); if(brackets_depth==0) BEGIN FUNCTION_TYPE;}
%%
int yywrap(void) { return 1; }
int main(void) { 
  return yylex(); 
}
