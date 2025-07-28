#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <ctype.h>

#define TAM_SEG 100

int main(int argc, char **argv)
{
  key_t clave;
  int shmid;
  char *seg;

  clave=ftok(".",'S');

  if((shmid=shmget(clave,TAM_SEG,IPC_CREAT|IPC_EXCL|0660))==-1)
	{
	  printf("El segmento de memoria compartida ya existe\n");
	  printf("    Abriendo como cliente\n");

	  if((shmid=shmget(clave,TAM_SEG,0))==-1)
		printf("Error al abrir el segmento\n");
	}
  else
	printf("Nuevo segmento creado\n");

  if(argc==1)
	printf("Error de argumentos\n");

  else if (shmid != -1)
	{
	  if((seg=shmat(shmid,NULL,0))== (char *)-1)
		printf("Error al mapear el segmento\n");
	  else
		switch(tolower(argv[1][0]))
		  {
		  case 'e': /* escribir en el segmento */
			if(argc==3)
			  {
				strncpy(seg,argv[2],TAM_SEG-1);
				if(strlen(argv[2])>=TAM_SEG-1)
				  seg[TAM_SEG-1]='\0';
				printf("Hecho...\n");
			  }
			break;
			
		  case 'l': /* Leer del segmento */
			printf("El contenido del segmento es: %s\n", seg);
			break;
			
		  case 'b':
			shmctl(shmid,IPC_RMID,0);
			printf("Segmneto de memoria marcado para borrar\n");
			break;
		  default:
			break;
		  }

	  shmdt(seg);

	}
  
  return(0);

}