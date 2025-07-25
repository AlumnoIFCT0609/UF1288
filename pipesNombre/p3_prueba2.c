#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#define NOMBREFIFO "mififo"

int main(int argc, char *argv[])
{
  int fp;
  int result=1;
  
  if(argc!=2)
	  printf("uso: %s cadena \n", argv[0]);
  else if ((fp=open(NOMBREFIFO,O_WRONLY))==-1)
	perror("fopen");
  else
	{	
	  write(fp,argv[1],strlen(argv[1]));
	  close(fp);
	  result=0;
	}

  return result;

}