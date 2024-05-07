#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


void error(const char *msg)
{
    perror(msg);
    //! is an inbuild function which integrates the error no. and outputs the error description by using stderr which is standard error
    exit(1);
}
int main(int argc, char *argv[])
{
    //! argc will be the no. of parameters we are passing. In our case argc will be 2.
    //! argv will contain the parameters which are the file and our port no.

    //! first check if port no. provided or not. if user not provide port no. then argc will be 1
    if (argc < 2)
    {
        fprintf(stderr, "Port no. not provided. Program terminated\n");
        exit(1);
    }

    int sockfd, newsockfd, portno, n;
    char buffer[255];

    struct sockaddr_in serv_addr, cli_addr;
    //! sockaddr_in gives us the internet address and it is included in file <netinet/in.h>
    socklen_t clilen; //! 32bit datatype

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    { //! socket function has resulted in a failure
        error("Error opening the socket");
    }
    bzero((char *)&serv_addr, sizeof(serv_addr));
    //! bzero is used to set all the values in a buffer to zero. It takes two arguments.

    portno = atoi(argv[1]);
    //! converts string into integer

    //! The sin in sin_family, sin_addr, and sin_port stands for "Socket INternet"
    serv_addr.sin_family = AF_INET;
    //! This sets the address family of the server address to AF_INET, which stands for Internet Address Family.
    //! It's used for IPv4 addresses

    serv_addr.sin_addr.s_addr = INADDR_ANY;
    //! This sets the IP address for the server. INADDR_ANY is a special value that means the server can accept a client connection on any interface,
    //! in case the server host has multiple interfaces
    //! In the line serv_addr.sin_addr.s_addr = INADDR_ANY;, we're accessing the sin_addr field of the serv_addr structure, which is itself a structure of type struct in_addr. This structure has a single field, s_addr, which holds an IP address in network byte order.
    //! INADDR_ANY is a special constant that's typically used for the sin_addr.s_addr field of the serv_addr structure.
    //! It tells the kernel to choose the IP address of on                                                                  e of the network interfaces of the machine to use for the socket.
    //! This is useful when your machine has multiple network interfaces (like Ethernet, Wi-Fi, etc.), and you want your server to be reachable via any of them.

    serv_addr.sin_port = htons(portno);
    //! This sets the port number for the server. htons is a function that converts the integer portno from host byte order to network byte order.
    //! This is necessary because network protocols expect numbers in network byte order, but the host might use a different byte order internally

    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    { //! typecasting sockaddr_in to sockaddr
        error("Binding failed");
    }

    listen(sockfd, 5);
    clilen = sizeof(cli_addr);

    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
    if (newsockfd < 0)
    {
        error("Error on accept");
    }

    while (1)
    {
        bzero(buffer, 255);
        n = read(newsockfd, buffer, 255);
        if (n < 0)
        {
            error("Error on reading");
        }
        printf("Client %s\n", &buffer);

        //! Now the server will reply
        bzero(buffer, 255);
        fgets(buffer, 255, stdin);

        n = write(newsockfd, buffer, strlen(buffer));
        if (n < 0)
        {
            error("Error on writing");
        }
        
        int i = strncmp("Bye",buffer,3);
        if(i == 0){
            break;
        }
        
    }
    close(newsockfd);
    close(sockfd);
    return 0;
}


// 1.first server (in one terminal) gcc fname.c -o fname and ./fname 2000 = portnumber

// 2.then client ka do (in another terminal) , gcc fname -o fname , ./fname

// 3.own 1 mssg send from client only (not first from server)

// 4.own 1 mssg send from server only (not first from client)(then the end)