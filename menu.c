#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int fd[2];
    char buffer[20];
    if(pipe(fd) < 0){
        perror("pipe");
        exit(1);
    }
    
    while(1){
        int input;
        printf("\nPlease select option:\n");
        printf("1. Display the records\n");
        printf("2. Save the records\n");
        printf("3. Display the summary\n");
        printf("4. Exit\n");
        printf(">> ");
        scanf("%d", &input);
        printf("\n\n");

        if(input == 1){
            printf("option 1\n");
        }
        else if(input == 2){
            printf("option 2\n");
        }
        else if(input == 3){
            printf("option 3\n");
        }
        else if(input == 4){
            break;
        }
        else{
            continue;
        }
        


    }

    printf("exited\n");
    return 0;
}