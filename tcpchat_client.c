
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>


/*
filename server_ipaddress portno
argv[0] filename
argv[1] server_ipaddress
agrv[2] portno
*/

void error(const char* msg){
    perror(msg);
    exit(1);
}

int main(int argc, char* argv[]){
    int sockfd,portno,n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    //! hostent is a structure which contains information about the host such as host name, IPv4 address, IPv6 address etc.

    char buffer[255];
    if(argc < 3){
        fprintf(stderr,"usage %s hostname port\n",argv[0]);
        exit(1);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd<0){
        error("Error opening socket");
    }   
    server = gethostbyname(argv[1]);
    if(server == NULL){
        fprintf(stderr,"Error no such host");
    }
    bzero((char *) &serv_addr,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char*) server->h_addr,(char*)&serv_addr.sin_addr.s_addr,server->h_length);

    serv_addr.sin_port = htons(portno);
    
    if(connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr))<0){
        error("Connection failed");
    }
    while(1){
        bzero(buffer,255);
        fgets(buffer,255,stdin);
        n = write(sockfd,buffer,strlen(buffer));
        if(n<0){
            error("Error on write");
        }
        bzero(buffer,255);
        n = read(sockfd,buffer,255);
        if(n<0){
            error("Error on read");
        }
        printf("Server: %s",buffer);
        int i = strncmp("Bye",buffer,3);
        if(i == 0){
            break;
        }

    }
    close(sockfd);
    return 0;

}


// 1.first server (in one terminal) gcc fname.c -o fname and ./fname 2000 = portnumber

// 2.then client ka do (in another terminal) , gcc fname -o fname , ./fname

// 3.own 1 mssg send from client only (not first from server)

// 4.own 1 mssg send from server only (not first from client)(then the end)