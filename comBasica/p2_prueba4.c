#include <unistd.h>
#define LECTURA 0
#define ESCRITURA 1
int main()
{

   int descr[2], bytesleidos;
   char mensaje[101];
   char *frase="Veremos si la transferencia es buena";
   pipe(descr);
   if(fork()==0)                    /* Proceso hijo */
   {
      close(descr[LECTURA]);
      write(descr[ESCRITURA], frase, strlen(frase));
      close(descr[ESCRITURA]);   
   }   else                         /* Proceso padre */
   {
      close(descr[ESCRITURA]);
      bytesleidos=read (descr[LECTURA], mensaje, 100);
      while(bytesleidos)
      {
         mensaje[bytesleidos]='\0';
         printf("Bytes leidos: %b \n",bytesleidos);

         printf("Mensaje: %s \n",mensaje);
         bytesleidos=read (descr[LECTURA], mensaje, 100);
      }
             close(descr[LECTURA]);
   }
}
