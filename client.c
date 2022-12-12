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
	char buffer[BUFFER_SIZE] = {0};
	char res[BUFFER_SIZE] = {0};
	struct sockaddr_in servaddr;
	
	// Creating socket file descriptor
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}
	
	memset(&servaddr, 0, sizeof(servaddr));
		
	// Filling server information
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = INADDR_ANY;
		
	ssize_t n;
	socklen_t len;
	
	while (1) {
		printf("[UDP]> ");
		scanf("%s", res);
		
		sendto(sockfd, (const char *)res, strlen(res), MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));
		printf("[SEND] %s\n", res);
		n = recvfrom(sockfd, (char *)buffer, BUFFER_SIZE, MSG_WAITALL, (struct sockaddr *) &servaddr, &len);
		buffer[n] = '\0';
		printf("[RECEIVED] %s\n", buffer);
	}
	
	close(sockfd);
	return 0;
}
