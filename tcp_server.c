#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void main(){
    struct sockaddr_in serv_addr, cli_addr;
    int sockfd , newsockfd, port, n;
    socklen_t clilen;
    char buffer[255];
    port = 8080;

//!
    sockfd = socket(AF_INET,SOCK_STREAM,0);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);

//!
    bind(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));

//!
    listen(sockfd,5);
    clilen = sizeof(cli_addr);

//!
    newsockfd = accept(sockfd,(struct sockaddr *)&cli_addr, &clilen);

//!
    read(newsockfd,buffer, 255);
    printf("Client :%s",&buffer);

    bzero(buffer,255);
    fgets(buffer,255,stdin);
    write(newsockfd,buffer,strlen(buffer));



}

// 1.first server (in one terminal) gcc and ./ 

// 2.then client ka do (in another terminal) , gcc fname -o fname , ./fname

// 3.own 1 mssg send from client only (not first from server)

// 4.own 1 mssg send from server only (not first from client)(then the end)