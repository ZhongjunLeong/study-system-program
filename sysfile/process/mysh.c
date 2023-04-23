#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <glob.h>
#include <string.h>
#define DELIMS " \t\n"
struct cmd_st
{
  glob_t globres;

};
static void prompt(void)
{

  printf("mysh-0.1$ ");
}
static void parse(char *line,struct cmd_st *res)
{// ls -a -l     /etc /aaa/bb/cc/   absd
  char *tok;
  while(1)
  {
    int i = 0;
    tok = strsep(&line,DELIMS);  //extract token from string
    if(tok == NULL)
      break;
    if(tok[0] == '\0')
      continue;
    glob(tok,GLOB_NOCHECK|GLOB_APPEND*i,NULL,&res->globres);//the first time dont append
    i = 1;//from second all append
  }


}
int main()
{
  char *linebuf = NULL;
  size_t linebuf_size = 0;
  struct cmd_st cmd;
  pid_t pid;
  while(1)
  {
    prompt();//printf start character
    if(getline(&linebuf,&linebuf_size,stdin) < 0)//get user input from termina
    break;
    parse(linebuf,&cmd);//distinct in or out oder
    if(0)//in oder
    {/*do sth*/ }
    else  //out oder
    {
      pid = fork();
      if(pid < 0)
      {
        perror("fork()");
        exit(1);
      }
      if(pid == 0)
      {
        
        execvp(cmd.globres.gl_pathv[0],cmd.globres.gl_pathv);
        perror("execvp()");
        exit(1);
      }
    
      else
        wait(NULL);
    
    }
  }
   
  exit(0);
}
