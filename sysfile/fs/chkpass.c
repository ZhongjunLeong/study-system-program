#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <shadow.h>
int main(int argc, char**argv)
{
  char * input_pass;
  char * crypt_pass;
  struct spwd *shadowline;
  if(argc < 2)
  {
    fprintf(stderr,"usage..\n");
    exit(1);
  }
  input_pass = getpass("password:");//get password
  shadowline = getspnam(argv[1]);//get password  file
  crypt_pass =  crypt(input_pass,shadowline->sp_pwdp);//the three $ content
  if(strcmp(shadowline->sp_pwdp,crypt_pass) == 0)
  {
      puts("ok");
  }
  else
  {
      puts("faile");
   
  }

  


  exit(0);
}
