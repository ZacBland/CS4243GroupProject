//Group Number: B
//Group member name: Vamsi Lakshman Varma Datla
//Email: vdatla@okstate.edu
//Date: 10102022
//Brief Description: I took my part in writing code for reading and dispalying options.txt and also displaying the records by gathering information from processes.

//Reading and displaying Options.txt:

//in server.c file

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
		strcpy(options[i],data); /*storing it in the options array. and the first element in
	the array contains the options that needs to be sent to the client*/
		i++;
	}
}
printf("Sending options to the client \n");
write(connfd,options[0],sizeof(options[0])); //sending the options to the client
printf("Waiting for the Client feedback \n");

//in client.c file


//previously use #define MAX 200, in the #include section of the file
char buff[MAX],no_of[50];
char data[MAX],option[MAX],opt[100][100];
int n,no_of_opts;
bzero(buff, sizeof(buff));
read(sockfd, buff, sizeof(buff)); //Reading the Options sent from client
printf("The Options are: \n");
char * token = strtok(buff, ","); //Tokenizing the String based on the delimiter ","
int j=0;
while(token != NULL)
	{
	printf("%d . %s \n",j+1, token); //Displaying the Options
	j++;
	token = strtok(NULL, ",");
	}
printf("\nplease enter one of the options"); //Taking the User input for the option selected
scanf("%s",data);


//Option1: Displaying the records

printf("Enter one option\n 1. Display Records \n 2. Exit \n");
                int sel=0;
                scanf("%d",&sel);
                char sel_opt[100],cat[10][200],rat[5][50], stock[2][50];
                if(sel == 1){
                        strcpy(sel_opt,"1");
                } else{
                        strcpy(sel_opt,"2");
                }

                write(sockfd, sel_opt,sizeof(sel_opt));
                read(sockfd,cat,sizeof(cat));
                for(int i = 0 ; i<10;i++){
                        printf("%d. %s \n",i+1, cat[i]);
                }                                       //
                char fie[703][1000];
                read(sockfd,fie,sizeof(fie));
                if(sel == 1){

                //for(int i =0 ; i<10;i++)
                     printf("%s \n",cat[i]);


                char cat_opt[100];
                printf("\n please enter one option");
                scanf("%s",cat_opt);
                write(sockfd, cat_opt, sizeof(cat_opt));
                //char fie[703][1000];
                //read(sockfd,fie,sizeof(fie));
                for(int k = 0; k<703;k++){
                        printf("%s \n", fie[k]);
                }

                }
                 if ((strncmp(buff, "exit", 2)) == 0) {
                        printf("Client Exit...\n");
                        exit(0);
                }


                 while(1){
        //Write user options
        bzero(buffer, sizeof(buffer));
        input[0] = '\0';
        printf("Please select option:\n");
        printf("1. Display the records\n");
        printf("2. Save the records\n");
        printf("3. Display the summary\n");
        printf("4. Exit\n");
        printf(">> ");
        scanf("%s", input);
        printf("\n");

        //Send input to server
        send(clientSock, input, strlen(input), 0);

        //break if option 4
        if(atoi(input) == 4)
            break;

        //Wait for server response
        memset(process_buff, 0 , sizeof(process_buff));
        bzero(process_buff, sizeof(process_buff));
        recv(clientSock, process_buff, 4000, 0);
        printf("%s\n", process_buff);

        //Go into option 1 if chosen
            //input choice
        char record[100];
        printf("Please select a record: \n");
        printf(">> ");
        scanf(" %[^\n]%*c", record);

            //send choice to server
        send(clientSock, record, strlen(record), 0);

            //recieve summary and display it
        char arr[200][200];
        if( recv(clientSock, arr, sizeof(sizeof(char) * 200) * 200, 0) < 0){
            return 1;
         }
          const char s[4] = ",";
        if(atoi(input) == 1){
                for(int i=0;i<200;i++){
                if(strlen(arr[i]) !=0){
                        char* token = strtok(arr[i], s);
                        int j=1;
                        //printf("===> %d \n",flag);
                        while(token != 0){
                                if(j== flag){
                                        token = strtok(0,s);
                                }
                                        printf(" %s,",token);
                                        token = strtok(0,s);
                                        j++;

                }
                printf("\n");
                printf("\n");

            }
	    }


//In server.c

write(connfd,column_names,sizeof(column_names));
                        printf("Waiting for column options\n");
                        read(connfd, column_option, sizeof(column_option));
                        printf("%s \n",column_option);
                        if((strcmp(column_option,"book category")==0)||(strcmp(column_option,"book")==0)){
                                printf("---> %s\n",column_option);

                                char category[10][200] ={"Poetry","Fiction","Music","Politics","Travel","Romance","Children","Nonfiction","Health","Religion"};
                                read(connfd, cli_opt, sizeof(cli_opt));
                                //printf("-=-=>\n %s ",cli_opt);


                                write(connfd, category, sizeof(category));
                                printf("+P %s",cli_opt);
                                //sleep(500);
                                read(connfd, cli_opt, sizeof(cli_opt));
                                printf("-=-=>\n %s ",cli_opt);
                                write(connfd,file_contents,sizeof(file_contents));
                                for(int k= 0 ; k<703;k++){
                                        printf("%s", file_contents[k]);
                                }



                        } else if((strcmp(column_option,"star rating")==0)||(strcmp(column_option,"star")==0)){
                                //printf("%s\n",column_option);
                                char rating[5][50] ={"One","Two","Three","Four","Five"};
                                read(connfd, cli_opt, sizeof(cli_opt));
                                write(connfd, rating, sizeof(rating));
                                //write(connfd,file_contents,sizeof(file_contents));
                        }else if(strcmp(column_option,"stock")==0){
                                //printf("%s",column_option);
                                //printf("%s\n",column_option);
                                char stock[2][50] ={"In-stock","Out-of-stock"};
                                read(connfd, cli_opt, sizeof(cli_opt));
                                write(connfd, stock, sizeof(stock));
                                //write(connfd,file_contents,sizeof(file_contents));
                        }else{
                                printf("Hello world \n");
                        }

                        //write(connfd, file_contents, sizeof(file_contents));

                        //fp = fopen("bookInfo.txt","r");



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
                        }else{
                        printf("option Not Available");

                        }

