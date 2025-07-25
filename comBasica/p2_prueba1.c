#define _GNU_SOURCE
#include <stdio.h>
#include <signal.h>

 int main(void)
{
   
   struct sigaction act;

   act.sa_handler= SIG_IGN;   /* Ignora la señal */
   act.sa_flags= 0;           /* Ninguna accion especial */   
   sigemptyset(&act.sa_mask); /* Ninguna señal bloqueada */

   printf("Se imprime, luego se ejecuta");  // fuera del bucle no lo imprime

   sigaction(SIGINT, &act, NULL);

   while(1){
       //printf("Se imprime, luego se ejecuta");  // lo imprime dentro del bucle, 
       
      
   }                  /* Bucle infinito */
}