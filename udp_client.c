#include <stdio.h>
#include <strings.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>

#define MAXLINE 1000

int main(){
	char buffer[100];
	char *message = "client:hello server";
	int sockfd,n;
	struct sockaddr_in servaddr;
	
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(5000);
	servaddr.sin_family = AF_INET;
	sockfd = socket(AF_INET,SOCK_DGRAM,0);
	if(connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr))<0){
		printf("connection failed");
		exit(0);
	}
	sendto(sockfd,message,MAXLINE,0,(struct sockaddr *)NULL,sizeof(servaddr));

	recvfrom(sockfd,buffer,sizeof(buffer),0,(struct sockaddr*)NULL,NULL);
	puts(buffer);
	close(sockfd);




}


// 1.first server (in one terminal) gcc and ./ 

// 2.then client ka do (in another terminal) , gcc fname -o fname , ./fname

// 3.predefined mssg send from server (then the end)