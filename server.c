#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
	
#define PORT 8888
#define BUFFER_SIZE 1024

int main() {
	int sockfd;
	char buffer[BUFFER_SIZE];
	char *hello = "Hello from server";
	struct sockaddr_in servaddr, cliaddr;
		
	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}
		
	memset(&servaddr, 0, sizeof(servaddr));
	memset(&cliaddr, 0, sizeof(cliaddr));
		
	// Filling server information
	servaddr.sin_family = AF_INET; // IPv4
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(PORT);
		
	// Bind the socket with the server address
	if ( bind(sockfd, (const struct sockaddr *)&servaddr,
			sizeof(servaddr)) < 0 )
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
		
	ssize_t n;
	socklen_t len;
	
	len = sizeof(cliaddr); //len is value/result
	
	while ((n = recvfrom(sockfd, (char *)buffer, BUFFER_SIZE, MSG_WAITALL, ( struct sockaddr *) &cliaddr, &len)) > 0) {
		buffer[n] = '\0';
		printf("[RECEIVED] %s\n", buffer);
		sendto(sockfd, (const char *)hello, strlen(hello), MSG_CONFIRM, (const struct sockaddr *) &cliaddr, len);
		printf("[SEND] %s\n", hello);
	}
	
	return 0;
}
