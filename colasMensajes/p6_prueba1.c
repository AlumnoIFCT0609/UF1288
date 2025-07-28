#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/msg.h>
#include <strings.h>

#define MAX_SEND_SIZE 80

struct mymsgbuf{
  long mtype;
  char mtext[MAX_SEND_SIZE];
};

int send_msg(int qid,struct mymsgbuf *qbuf);
int leer_msg(int qid,long type,struct mymsgbuf *qbuf);

int send_msg(int qid,struct mymsgbuf *qbuf)
{
  int resultado, longitud;
  longitud = sizeof(struct mymsgbuf)-sizeof(long);
  if ((resultado=msgsnd(qid,qbuf,longitud,0))==-1) 
	return (-1);
  else
	return (0);
}

int leer_msg(int qid,long type,struct mymsgbuf *qbuf)
{
  int resultado, longitud;
  longitud = sizeof(struct mymsgbuf)-sizeof(long);

  if ((resultado=msgrcv(qid,qbuf,longitud,type,0))==-1)
	return (-1);
  else
	return (resultado);
}

int main(int argc,char *argv[])
{
  key_t clave;
  int msgqueue_id;
  long tipo;
  struct mymsgbuf qbuf;

  if (argc==1) 
	{
        printf("Error, faltan argumentos en la linea de comandos\n");
	}
  else
	{
	  clave=ftok(".",'m');

  if ((msgqueue_id=msgget(clave,IPC_CREAT|0660))==-1) 
		{
		  printf("Error al iniciar la cola\n");
		}
	  else
		{
		  tipo=atol(argv[2]);
		  
		  switch(tolower(argv[1][0]))
			{
			case 'e': 

			  printf("Enviando mensaje...\n");
			  qbuf.mtype = tipo;
			  strncpy(qbuf.mtext,argv[3],40);
			  send_msg(msgqueue_id,&qbuf);
			  break;

			case'r':
				
			  printf("Leyendo mensaje...\n");
			  leer_msg(msgqueue_id,tipo,&qbuf);
			  printf("Tipo: %ld Texto:%s \n",qbuf.mtype,qbuf.mtext);
			  break;  
			}
		}
	}
  return (0);
}    