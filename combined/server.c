#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "process.h"

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
        if ((childPid = fork()) == 0) 
        {
            close(serverSock);

            //previously use #define MAX 200, in the #include section of the file
            FILE *filePointer ;
            char data[100];
            char options[100][100],opt[100][100];
            filePointer = fopen("options.txt", "r") ; //Opening the Options.txt file
            if(filePointer == NULL)
            {
                    printf("File cant be opened");
                    exit(0);
            }
            else
            {
                int i=0;
                while(fgets(data,100,filePointer)!=NULL) //reading the file line - by - line
                { 
                        strcpy(options[i],data); //storing it in the options array. and the first element in the array contains the options that needs to be sent to the client
                        i++;
                }
            }	
            printf("Sending options to the client \n");
            send(clientSock, options[0], sizeof(options[0]), 0);  //sending the options to the client
            printf("Waiting for the Client feedback \n");

            // read the message from client and copy it in buffer
            bzero(buffer, sizeof(buffer));
            recv(clientSock, buffer, 1024, 0);
            printf("Response: %s \n\n", buffer);

            // print buffer which contains the client contents
            if(strcmp(buffer,"bookInfo.txt")==0){

                char column_names[50] = "Book category, Star rating, Stock";
                char column_option[100];

                write(clientSock,column_names,sizeof(column_names));
                printf("Waiting for column options\n");
                read(clientSock, column_option, sizeof(column_option));
                printf("%s \n",column_option);

                readFile("bookInfo.txt", 6);
                if((strcmp(column_option,"Book category")==0)||(strcmp(column_option,"Book")==0))
                    processSetup(703, 6, 1, 43);
                else if((strcmp(column_option,"Star rating")==0)||(strcmp(column_option,"Star")==0))
                    processSetup(703, 6, 2, 5);
                else if(strcmp(column_option,"Stock") == 0)
                    processSetup(703, 6, 4, 2);
                else
                    printf("Incorrect category.\n");

            }
            else if(strcmp(buffer,"amazonBestsellers.txt")==0){
                char column_names[50] = "User rating, Year, Genre";
                char column_option[100];
                write(clientSock, column_names, sizeof(column_names));
                printf("Waiting for column options\n");
                read(clientSock, column_option, sizeof(column_option));
                printf("%s \n",column_option);

                readFile("amazonBestsellers.txt", 7);
                if((strcmp(column_option,"User rating") == 0)||(strcmp(column_option,"User") == 0))
                    processSetup(550, 7, 2, 10);
                else if(strcmp(column_option,"Year") == 0)
                    processSetup(550, 7, 5, 11);
                else if(strcmp(column_option,"Genre") == 0)
                    processSetup(550, 7, 6, 2);
                else
                    printf("Incorrect category.\n");

                // if msg contains "Exit" then server exit and chat ended.
                if (strncmp("exit", buffer, 4) == 0) {
                    printf("Server Exit...\n");
                    break;
                }
                
            }
            char userMenu[100] = "1. Display the records \n2. Save the records \n3. Display the summary\n4. Exit \n\n";
            write(clientSock,userMenu,sizeof(userMenu));
            printf("Waiting for user command\n");
            /*bzero(buffer, sizeof(buffer));
            recv(clientSock, buffer, 1024, 0);
            printf("Response: %s \n\n", buffer);*/
        }
        
    }
    // Close the client socket id
    close(clientSock);
    return 0;
}