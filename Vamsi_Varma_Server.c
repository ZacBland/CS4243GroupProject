

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX 200

void read_options(int connfd)
{
	char buff[MAX];
	int n;
	bzero(buff, MAX);
    FILE *filePointer ;
	char data[100];
	char options[100][100],opt[100][100];
		
	filePointer = fopen("options.txt", "r") ;
	if(filePointer == NULL){
		printf("File cant be opened");
		exit(0);

	}else{
		int i=0;
		while(fgets(data,100,filePointer)!=NULL){
			strcpy(options[i],data);
			i++;
		}
	}


	printf("Sending options to the client \n");
	write(connfd,options[0],sizeof(options[0]));
	printf("Waiting for the Client feedback \n");

	// read the message from client and copy it in buffer
	read(connfd, buff, sizeof(buff));
	printf("%s",buff);

}

int main()
{
    int port = 5100;
    int serverSock, clientSock;
    struct sockaddr_in serverAddress, clientAddress;
    socklen_t addrSize;
    char buffer[1024];
    pid_t childPid;

    serverSock = socket(AF_INET, SOCK_STREAM, 0);
    if(serverSock< 0)
    {
        perror("[-] Error creating socket");
        exit(1);
    }
    printf("[+] TCP socket created successfully \n");

    memset(buffer, '\0', sizeof(buffer));
    memset(&serverAddress, '\0', sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

    int bindingSuccess = bind(serverSock, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
    if(bindingSuccess < 0)
    {
        perror("[-] Error in binding");
        exit(1);
    }

    listen(serverSock, 3);
    printf("Waiting for connection \n");
    int numClients = 0;

    while (1) {
        clientSock = accept(serverSock, (struct sockaddr*)&clientAddress,&addrSize);
        if (clientSock < 0) {
            exit(1);
        }
        printf("Accepted connection from %s:%d\n",inet_ntoa(clientAddress.sin_addr),ntohs(clientAddress.sin_port));
        printf("Number of clients: %d \n\n",++numClients);
        if ((childPid = fork()) == 0) {
	    printf("ss -> %d \n",serverSock);
	    close(serverSock);
            send(clientSock, "hi client", strlen("hi client"), 0);
	    read_options(clientSock);
            bzero(buffer, sizeof(buffer));
            recv(clientSock, buffer, 1024, 0);
            printf("Response: %s \n", buffer);
        }
    }
    
    close(clientSock);
    return 0;
}
