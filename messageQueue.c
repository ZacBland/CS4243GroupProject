#include <stdio.h>		// for printf
#include <time.h>		// for clock()
#include <unistd.h>		// for fork
#include <stdlib.h>		// for exit(1)
#include <sys/ipc.h> 	// Used by IPC maechanisms: messages, shared memory and semaphores
#include <sys/msg.h>	// for message queue structures
#include <string.h>		// for string operation: strlen
#include<sys/wait.h>	// for wait
#include <fcntl.h>		// for file control options
#include <errno.h>		// for system error numbers
#include <mqueue.h>		// for mq_close, mq_unlink, ...

//Taken from Joshi's example
#define QUEUE_NAME   "/addition"
#define PERMISSIONS 0660
#define MAX_MESSAGES 10
#define MAX_MSG_SIZE 256
#define MSG_BUFFER_SIZE MAX_MSG_SIZE + 10

int main()
{
    mqd_t qd;   // queue descriptors

	struct mq_attr attr;
	attr.mq_flags = 0;
	attr.mq_maxmsg = MAX_MESSAGES;	// The maximum number of messages that can be stored on the queue. 
	attr.mq_msgsize = MAX_MSG_SIZE;	// The maximum size of each message on the given message queue. 
	attr.mq_curmsgs = 0;	// This field represents the number of messages currently on the given queue.

    int childPID = fork();
    if(childPID == 0)
    {
        //This child will print out all of the messages that say "Even"

        //connect to queue with read/write permissions
        qd = mq_open (QUEUE_NAME, O_RDWR, PERMISSIONS, &attr);

		char in_buffer [MSG_BUFFER_SIZE];
        char out_buffer [MSG_BUFFER_SIZE];
        
        while(1)
        {
		    mq_receive (qd, in_buffer, MSG_BUFFER_SIZE, NULL);
            
            /*if(strcmp(in_buffer, "End") == 0)
            {
                printf("End command recived by child 1 \n");
                sprintf(out_buffer, "%s", in_buffer);
                mq_send (qd, out_buffer, strlen (out_buffer) + 1, 0);
                break;
            }*/
            
            //
            if(strcmp(in_buffer, "Even") != 0)
            {
                //if the message isn't a message we care about we put it back in the queue
                printf("Child 1 resending \n");
                sprintf(out_buffer, "%s", in_buffer);
                mq_send (qd, out_buffer, strlen (out_buffer) + 1, 0);
            }
            else
            {
                //If we care about the message then we process it
                printf("%s \n", in_buffer);
            }
        }
        printf ("Child 1 finished \n");
		mq_close (qd);
		mq_unlink (QUEUE_NAME);
    }
    else
    {
		int newChildPID = fork();
        if(newChildPID == 0)
        {
            //The same as the other child but for messages that say "Odd"

            qd = mq_open (QUEUE_NAME, O_RDWR, PERMISSIONS, &attr);

		    char in_buffer [MSG_BUFFER_SIZE];
            char out_buffer [MSG_BUFFER_SIZE];
        
            while(1)
            {
		        mq_receive (qd, in_buffer, MSG_BUFFER_SIZE, NULL);
            
                /*if(strcmp(in_buffer, "End") == 0)
                {
                    printf("End command recived by child 2 \n");
                    sprintf(out_buffer, "%s", in_buffer);
                    mq_send (qd, out_buffer, strlen (out_buffer) + 1, 0);
                    break;
                }*/
            
                if(strcmp(in_buffer, "Even") == 0)
                {
                    printf("Child 2 resending \n");
                    sprintf(out_buffer, "%s", in_buffer);
                    mq_send (qd, out_buffer, strlen (out_buffer) + 1, 0);
                }
                else
                {
                    printf("%s \n", in_buffer);
                }
            }
            printf ("Child 2 finished \n");
		    mq_close (qd);
		    mq_unlink (QUEUE_NAME);
        }

        else
        {
            //The parent process
            qd = mq_open (QUEUE_NAME, O_WRONLY | O_CREAT, PERMISSIONS, &attr);
		    char out_buffer [MSG_BUFFER_SIZE];

            //Output 5 Even and 5 Odd to the message queue
            for(int i = 0; i < 10; i++)
            {
                if(i % 2 == 0)
                {
                    sprintf (out_buffer, "%s", "Even");
                    mq_send (qd, out_buffer, strlen (out_buffer) + 1, 0);
                    
                }
                else
                {
                    sprintf (out_buffer, "%s", "Odd");
                    mq_send (qd, out_buffer, strlen (out_buffer) + 1, 0);
                }
                bzero(out_buffer, sizeof(out_buffer));
                printf("Message sent! \n");
            }
            //sprintf (out_buffer, "%s", "End");
            //mq_send (qd, out_buffer, strlen (out_buffer) + 1, 0);
            //printf("End command sent \n");

            //Wait for children to finish before exiting
            //ISSUE: the children never finish
            wait(NULL);
            wait(NULL);
		    exit(0);
        }
    }
    return 0;
}