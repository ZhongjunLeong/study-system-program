#include <stdio.h>
#include <stdlib.h>
#include <glob.h>

#define PAT "/etc/a*.conf"
//#define PAT "/etc/*"


#if 0
int errfunc_(const char *errpath,int eerrno)
{
  puts(errpath);
  fprintf(stderr,"ETTOT MSG:%s\n",strerror(eerrno));
  return 0;
}
#endif
int main()
{
  int i,err;
  glob_t globres;

  err = glob(PAT,0,NULL,&globres);
  if(err)
  {
    printf("Error code = %d\n",err);
    exit(1);
  }
  for(i = 0; i < globres.gl_pathc;i++)//printf oder content
    puts(globres.gl_pathv[i]);
globfree(&globres);
  exit(0);
}
