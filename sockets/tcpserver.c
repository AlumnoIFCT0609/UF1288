#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <unistd.h>
#define PORTNUMBER 12563

int main(void)
{

    char buf[1024];
    int s, n, ns, len;
    struct sockaddr_in name;

    s= socket(PF_INET, SOCK_STREAM,0);
    name.sin_family = AF_INET;
    name.sin_port = htons(PORTNUMBER);
    name.sin_addr.s_addr = htonl(INADDR_ANY);
    len = sizeof(struct sockaddr_in);

    bind(s,(struct sockaddr *) &name, len);

    listen(s,5);

    //ns = accept(s,(struct socket *)&name, &len);
    struct sockaddr_in client;
    socklen_t  client_len = sizeof(client); // no es un tipo int
    ns = accept(s, (struct sockaddr *) &client, &client_len);

    while ((n=recv(ns,buf,sizeof(buf),0))>0)
    {
        //write(stdout,buf,n);
        write(1, buf, n); // 1 es el descriptor para stdout
        //esto si se prefiere funcion de stdio -> fwrite(buf, 1, n, stdout);

        printf("imprimiendo");
    }
    close(ns);
    close(s);



}