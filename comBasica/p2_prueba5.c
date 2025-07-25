#include <fcntl.h>

int main(int argc, char *argv[])
{
   int desc_fich;
   if(argc < 3)
	  printf("Formato: %s fichero comando [opciones].\n", argv[0]);
      else
   {
      printf("Ejemplo de redireccion. \n");
      desc_fich= open(argv[1],O_CREAT|O_TRUNC|O_WRONLY, 0);
      dup2(desc_fich,1);
      close(desc_fich);
      execvp(argv[2], &argv[2]);
   }
}