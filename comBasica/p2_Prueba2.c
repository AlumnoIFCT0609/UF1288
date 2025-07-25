#define _GNU_SOURCE
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void tratar_alarma(void)
{
  printf("Activada \n");
}

int main(void)
{
	struct sigaction act;
	
	act.sa_handler = tratar_alarma; /* función a ejecutar */
	act.sa_flags = 0;               /* ninguna acción especifica*/
	
	/* Se bloquea la señal SIGINT cuando se ejecute la función
		tratar_alarma */
    sigemptyset(&act.sa_mask);
	sigaddset(&act.sa_mask, SIGINT);

	sigaction(SIGALRM, &act, NULL);

	for(;;)
	{
		alarm(3);	/* se arma el temporizador */  
		pause();	/* se suspende el proceso hasta que se reciba una señal */
	}
}