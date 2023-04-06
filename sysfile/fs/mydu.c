#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <glob.h>
#include <string.h>
#define PATHSIZE 1024
static int path_noloop(const char *path)
{
  char *pos;
  pos = strrchr(path,'/');
  if(pos == NULL)
    exit(1);
  if(strcmp(pos+1,".") == 0||strcmp(pos+1,"..") == 0)
    return 0;

  return 1;
}
static int64_t mydu(const char *path)//int64_4 == long long
{
  static struct stat statres;//when using digui before,make it static to avoid stack burden 
  static char nextpath[PATHSIZE];
  glob_t globres;
  int64_t sum;
  int i;
  if( lstat(path,&statres) < 0)
  {
    perror("lstat()");
    exit(1);
  }
  if(!S_ISDIR(statres.st_mode)) //not a directory file
    return statres.st_blocks;
  strncpy(nextpath,path,PATHSIZE);
  strncat(nextpath,"/*",PATHSIZE);
  glob(nextpath,0,NULL,&globres);

  strncpy(nextpath,path,PATHSIZE);
  strncat(nextpath,"/.*",PATHSIZE);
  glob(nextpath,GLOB_APPEND,NULL,&globres);//all /.*  go append to globres
  sum = statres.st_blocks;
  for(i = 0; i < globres.gl_pathc; i++)
  {
   if(path_noloop(globres.gl_pathv[i]))
   sum +=  mydu(globres.gl_pathv[i]);
  }
//  sum += statres.st_blocks;
  globfree(&globres);
  return sum;
}
int main(int argc,char **argv)
{

  if(argc < 2)
  {
    fprintf(stderr,"usgae..\n");
    exit(1);
  }

 printf("%lld\n", mydu(argv[1])/2);
 exit(0);
}
