#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include "socket_connection.h"
void get_content_webpage(char url[])
{	
	int sock,n;
	struct hostent *destination;
	struct sockaddr_in server;
	char msg[256];
	printf("%s",url);
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0)
		printf("error opening socket");
	destination = gethostbyname(url);
    	if (destination == NULL) {
        printf("ERROR, no such host\n");
      	return;
    }
	bzero(&server,sizeof(server));
	server.sin_family = AF_INET;
	
	bcopy((char *)destination->h_addr,(char *)&server.sin_addr.s_addr,destination->h_length);
	
	server.sin_port = htons(80);
	bzero(msg,256);
	strcat(msg,"GET / HTTP/1.1\nHost: www.jmarshall.com\nUser-Agent: Mozilla/5.0 (X11; Linux i686; rv:2.0.1) Gecko/20100101 Firefox/4.0.1\n\n");


	if(connect(sock,(struct sockaddr *) &server, sizeof(server)) < 0)
		printf("error connecting");
	printf("sending");
	n = write(sock,msg,strlen(msg));
	

	do{

	bzero(msg,256);
	n = recv(sock,msg,254,0);
	printf("%s",msg);
	}while(n != 0);		
	close(sock);
	
}