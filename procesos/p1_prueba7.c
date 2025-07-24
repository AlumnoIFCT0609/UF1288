
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>

void main(int argc, char **argv)
{
   pid_t pid;
    int valor;

   pid = fork();
   switch(pid)
   {
      case -1:   /* error del fork() */
         perror("fork");
         break;
      case 0:    /* proceso hijo */
         if(argc>1)
if (execvp(argv[1], &argv[1]) < 0)
	   perror("exec");
         break;
      default:   /* padre */
         while (wait(&valor) != pid);

         if (valor == 0)
            printf("El mandato se ejecuto de forma normal\n");
         else
         {
            if (WIFEXITED(valor))
                 printf("El hijo termino normalmente y su valor devuelto fue %d\n",
     WEXITSTATUS(valor));

            if (WIFSIGNALED(valor))
                 printf("El hijo termino al recibir la señal %d\n", WTERMSIG(valor));
         }
   }
}