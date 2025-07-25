#define _GNU_SOURCE
#include <unistd.h>
#define LEER 0
#define ESCRIBIR 1
int main (int argc, char *argv[])
{
   int descr[2];
   if(argc!=3)
      printf("Formato: %s comando_ent comando_sal. \n", argv[0]);
   else
   {
     pipe(descr);
     if(fork()==0)
     {
       close(descr[LEER]);
       dup2(descr[ESCRIBIR],1);
       close(descr[ESCRIBIR]);
       execlp(argv[1],argv[1],NULL);
       perror(argv[0]);
     }
     else
     {
       close(descr[ESCRIBIR]);
       dup2(descr[LEER],0);
       close(descr[LEER]);
       execlp(argv[2],argv[2],NULL);
       perror(argv[0]);
     }
   }
} 