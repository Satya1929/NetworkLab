#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

// void main(){
//     int sockfd, portno,n;
//     struct sockaddr_in serv_addr;
    
//     struct hostent *server;

//     char buffer[255];

//     portno = 8080;
//     sockfd = socket(AF_INET,SOCK_STREAM,0);

//     server = gethostbyname("127.0.0.1");

//     serv_addr.sin_family = AF_INET;
//     bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr,server->h_length);

//     serv_addr.sin_port = htons(portno);
//     connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));

//     fgets(buffer,255,stdin);
//     write(sockfd,buffer,strlen(buffer));

//     bzero(buffer,255);
//     read(sockfd,buffer,255);
//     printf("Server : %s",buffer);

// }
void main(){
    int sockfd ,  portno;
    struct sockaddr_in serv_addr;
    struct hostent* server;

    sockfd = socket(AF_INET,SOCK_STREAM,0);

    server = gethostbyname("127.0.0.1");
    portno = 8080;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(portno);

    bcopy((char *)server->h_addr,(char *)&serv_addr.sin_addr.s_addr,server->h_length);

    connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));

    char buffer[255];
    fgets(buffer,255,stdin);
    write(sockfd,buffer,strlen(buffer));

    bzero(buffer,255);
    read(sockfd,buffer,255);
    printf("Server: %s",buffer);
}

// 1.first server (in one terminal) gcc and ./ 

// 2.then client ka do (in another terminal) , gcc fname -o fname , ./fname

// 3.own 1 mssg send from client only (not first from server)

// 4.own 1 mssg send from server only (not first from client)(then the end)