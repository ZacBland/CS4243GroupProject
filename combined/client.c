#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#define MAX 200

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

    //previously use #define MAX 200, in the #include section of the file
    char no_of[50];
    char data[MAX], option[MAX], opt[100][100];
    int n,no_of_opts;
    bzero(buffer, sizeof(buffer));
    recv(clientSock, buffer, sizeof(buffer), 0);        //Reading the Options sent from client
    printf("The Options are: \n");
    char * token = strtok(buffer, ",");	    //Tokenizing the String based on the delimiter ","
    int j=0;

    while(token != NULL)
    {
        printf("%d . %s \n",j+1, token);   //Displaying the Options
        j++;
        token = strtok(NULL, ",");
    }

    char input[20];

    printf("\nPlease enter one of the options:\n");  //Taking the User input for the option selected
    scanf("%s", input);
    send(clientSock, input, strlen(input), 0);

    recv(clientSock, buffer, 1024, 0);
    printf("\n\n%s\n", buffer);
    
    input[0] = '\0';
    printf("Please enter one of the options:\n");  //Taking the User input for the option selected
    scanf("%s", input);
    send(clientSock, input, strlen(input), 0);

    while(1){
        input[0] = '\0';
        printf("\nPlease select option:\n");
        printf("1. Display the records\n");
        printf("2. Save the records\n");
        printf("3. Display the summary\n");
        printf("4. Exit\n");
        printf(">> ");
        scanf("%s", input);
        printf("\n\n");

        send(clientSock, input, strlen(input), 0);

        if(atoi(input) == 4)
            break;
    }

    return 0;
}