

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
		// print buffer which contains the client contents
		if(strcmp(buff,"bookInfo.txt")==0){
			char column_names[50] = "Book category, Star rating, Stock";
			char column_option[100];
			write(connfd,column_names,sizeof(column_names));
			printf("Waiting for column options\n");
			read(connfd, column_option, sizeof(column_option));
			printf("%s \n",column_option);
			if((strcmp(column_option,"book category")==0)||(strcmp(column_option,"book")==0)){
				printf("%s",column_option);
			} else if((strcmp(column_option,"star rating")==0)||(strcmp(column_option,"star")==0)){
				printf("%s",column_option);
			}else if(strcmp(column_option,"stock")){
				printf("%s",column_option);
			}else{
				printf("Hello world \n");
			}


		}else if(strcmp(buff,"amazonBestsellers.txt")==0){
			char column_names[50] = "User rating, Year, Genre";
			char column_option[100];
			write(connfd,column_names,sizeof(column_names));
			printf("Waiting for column options\n");
			read(connfd, column_option, sizeof(column_option));
			printf("%s \n",column_option);
			if((strcmp(column_option,"user rating")==0)||(strcmp(column_option,"user")==0)){
			        printf("%s",column_option);
			} else if(strcmp(column_option,"year")==0){
			        printf("%s",column_option);
			}else if(strcmp(column_option,"genre")){
			        printf("%s",column_option);
			}else{
				printf("Hello world \n");
																																																		                        }
		}
		else{
			printf("option Not Available");
			
		}


		
		// if msg contains "Exit" then server exit and chat ended.
		if (strncmp("exit", buff, 4) == 0) {
			printf("Server Exit...\n");
		//	break;
		}
	


	

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
