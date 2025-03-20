%{
  #include <stdio.h>
  #include <stdlib.h>
  #include <unistd.h>
  #include <fcntl.h>
  #define MAX_FILE_SIZE 5000
  int yywrap(void);
  int yylex(void);
  char project_info[MAX_FILE_SIZE];
%}
%%
%%
int yywrap(void) { return 1; }
int main(int argc, char **argv) { 
  if(argc > 1){
    int file_id = open(argv[1], O_RDONLY);
    if(file_id == -1){
      perror("Error opening file");
      return -1;
    }
    off_t size = lseek(file_id, 0, SEEK_END);
    if(size > MAX_FILE_SIZE){
      perror("File too large");
      return -1;
    }
    lseek(file_id, 0, SEEK_SET);
    read(file_id, project_info, size);
    printf("%s", project_info);
    return yylex(); 
  }
  return -1;
}
