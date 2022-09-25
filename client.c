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
    int clientSock;
    struct sockaddr_in serverAddress;
    char buffer[1024];
    int port = 5100;
    clientSock = socket(AF_INET, SOCK_STREAM, 0);
    socklen_t addrSize;
    if(clientSock < 0)
    {
        perror("[-] Socket error");
        exit(1);
    }
    printf("[+] TCP server socket created \n");
    memset(buffer, '\0', sizeof(buffer));

    memset(&serverAddress, '\0', sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(clientSock, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
    printf("Connected to the server \n");

    while(1)
    {
        recv(clientSock, buffer, 1024, 0);
        printf("Server: %s\n", buffer);
        bzero(buffer, sizeof(buffer));
        printf("Send your response \n");
        char input[20];
        scanf("%s", input);
        send(clientSock, input, strlen(input), 0);
    }


    return 0;
}