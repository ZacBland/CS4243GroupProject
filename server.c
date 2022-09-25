#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

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
            close(serverSock);
            send(clientSock, "hi client", strlen("hi client"), 0);
            bzero(buffer, sizeof(buffer));
            recv(clientSock, buffer, 1024, 0);
            printf("Response: %s \n", buffer);
        }
    }
    // Close the client socket id
    close(clientSock);
    return 0;
}