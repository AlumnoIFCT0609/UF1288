#define _GNU_SOURCE
#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>

pid_t pid;

void matar_proceso(void)
{
	kill(pid, SIGKILL);	/* se envía la señal al hijo */
}

void main(int argc, char **argv)
{
	int status;
	struct sigaction act;
  
	/* Se crea el proceso hijo */
	pid = fork();
	switch(pid)
	{
		case -1:   /* error del fork() */
		  perror("fork");
			break;
		case 0:    /* proceso hijo */
		  if(argc>1)
			/* El proceso hijo ejecuta el mandato recibido */
			execvp(argv[1], &argv[1]);
			perror("exec");
			break;
		default:   /* padre */
			/* establece el manejador */
			act.sa_handler = matar_proceso; /*función a ejecutar*/
			act.sa_flags = 0;   /* ninguna acción especifica */
			sigemptyset(&act.sa_mask);
			sigaction(SIGALRM, &act, NULL);
			alarm(5);
	
			/* Espera al proceso hijo */
			wait(&status);
	}
}