#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <linux/stat.h>
#include <linux/types.h>
#include <fcntl.h>
#define NOMBREFIFO "mififo"
#define TAM_BUF 80
#define TRUE 1

int main(void)
{
  int fp;
  char buffer[TAM_BUF];
  int nbytes;

  int result= mknod(NOMBREFIFO,S_IFIFO | 0660, 0);

  while(TRUE)
	{
	  fp=open(NOMBREFIFO,O_RDONLY);
	  nbytes=read(fp,buffer,TAM_BUF-1);
      buffer[nbytes]='\0';
	  printf("Cadena recibida: %s \n",buffer);
	  close(fp);
	}

  return 0;
}