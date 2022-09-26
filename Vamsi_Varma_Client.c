#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#define MAX 200
void read_options(int sockfd)
{
	char buff[MAX],no_of[50];
	char data[MAX],option[MAX],opt[100][100];
	int n,no_of_opts;
		bzero(buff, sizeof(buff));
		read(sockfd, buff, sizeof(buff));
		printf("The Options are: \n %s \n",buff);
                char * token = strtok(buff, ",");
                int j=0;
                while(token != NULL){
                        printf("%d . %s \n",j+1, token);
			j++;
                        token = strtok(NULL, ",");
                }

		printf("\nplease enter one of the options");
		scanf("%s",data);

		write(sockfd, data, sizeof(data));
		
		printf("Please enter exit to quit");

		if ((strncmp(buff, "exit", 4)) == 0) {
			printf("Client Exit...\n");
			exit(0);
		}
}

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
        printf("Server: %s\n %d \n", buffer,clientSock);
        bzero(buffer, sizeof(buffer));
        read_options(clientSock);
        printf("Send your response \n");
        char input[20];
        scanf("%s", input);
        send(clientSock, input, strlen(input), 0);
    }


    return 0;
}
