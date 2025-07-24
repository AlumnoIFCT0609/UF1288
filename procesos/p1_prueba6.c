#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

void main(int argc, char **argv)
{
   pid_t pid;

   pid = fork();
   switch(pid)
    {
      case -1:   /* error del fork() */
         perror("fork");
         break;
      case 0:    /* proceso hijo */
         if (execvp(argv[1], &argv[1])< 0)
         perror("exec");
         break;
      default:   /* padre */
         printf("Proceso padre\n");
   }
}