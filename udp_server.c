#include <stdio.h>
#include <strings.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAXLINE 1000
int main(){
	char buffer[100];
	char *message = "Hello Client";
	int listenfd,len;
	struct sockaddr_in servaddr,cliaddr;
	bzero(&servaddr,sizeof(servaddr));
	
	listenfd = socket(AF_INET,SOCK_DGRAM,0);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(5000);
	servaddr.sin_family = AF_INET;
	
	bind(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
	
	len = sizeof(cliaddr);
	int n = recvfrom(listenfd,buffer,sizeof(buffer),0,(struct sockaddr*)&cliaddr,&len);
	buffer[n] = '\0';
	puts(buffer);
	sendto(listenfd,message,MAXLINE,0,(struct sockaddr*)&cliaddr,sizeof(cliaddr));

}

// 1.first server (in one terminal) gcc and ./ 

// 2.then client ka do (in another terminal) , gcc fname -o fname , ./fname

// 3.predefined mssg send from server (then the end)
