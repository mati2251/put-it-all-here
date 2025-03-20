%{
  #include <stdio.h>
  int yywrap(void);
  int yylex(void);
  int tab_depth = 0;
  void print_new_line();
%}
%s NEWLINE
%s COMMENT
new_line \n
new_line_with_right_bracket \n\}
comment\/\/
semicolon ;
left_bracket \{
right_bracket \}
white_characters [ \t]
non_white_characters [^ \n\t]
%%
<INITIAL>{semicolon}                    { printf("%s", yytext); BEGIN(NEWLINE);}
<INITIAL>{left_bracket}                 { tab_depth++; printf("%s", yytext); }
<INITIAL>{new_line}                     { print_new_line(); }
<INITIAL>{new_line_with_right_bracket}  { tab_depth--; print_new_line(); printf("}");};
<INITIAL>{white_characters}             {}
<INITIAL>{right_bracket}                { tab_depth--; printf("%s", yytext); }
<NEWLINE>{non_white_characters}         { print_new_line(); printf("%s", yytext); BEGIN(INITIAL); }
<NEWLINE>{comment}                      { printf("/*"); BEGIN(COMMENT); }
<NEWLINE>{new_line}                     { print_new_line(); BEGIN(INITIAL);}
<NEWLINE>{new_line_with_right_bracket}  { 
                                          tab_depth--; 
                                          print_new_line(); 
                                          printf("}"); 
                                          BEGIN(INITIAL);
                                        }
<COMMENT>{new_line}                     { printf(" */"); print_new_line(); BEGIN(INITIAL);}
<COMMENT>{new_line_with_right_bracket}  { 
                                          printf(" */"); 
                                          tab_depth--; 
                                          print_new_line(); 
                                          printf("}"); 
                                          BEGIN(INITIAL);
                                        }
%%
int yywrap(void) { return 1; }
int main(void) { return yylex(); }
void print_new_line(){
  printf("\n");
  for(int i = 0; i < tab_depth; i++) 
    printf("\t");
}