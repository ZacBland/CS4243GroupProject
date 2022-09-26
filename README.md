# CS4243GroupProject
From Vamsi Lakshman Varma Datla

I have taken Brennan's code which is server and client connection and integrated it with my code of reading and displaying options.txt. It worked fine

Commands to run my code:

gcc -w Vamsi_Varma_Server.c
./a.out

Parallelly run the below commands on the other terminal.

gcc -w Vamsi_Varma_Client.c
./a.out

Now on Client side it will display options and now select the required option.

from Bhanu Teja Solipeta

I have pushed the integrated code from server to client connection until reading the column names from the selected file and tested it. It worked fine

Commands to run the code:

gcc -w Bhanu_Server.c
./a.out

also run the below commands on client side
gcc -w Bhanu_Client.c
./a.out

After selecting a file options corresponding to the file are shown below

from Blake:

I just uploaded the first draft of process.c. This file contains:

- Two static 3D char (2D String) arrays storing the contents of the file. One for each file. (The hardcoded portion).

- Main function that acts as a tempory menu that requests file name and the column to focus on

  - This menu is just for interfacing with my program. I know someone else is making the full menu.

- Process function that searches through the specified file array for the specified column and collects the unique categories and counts the number of items within it.

  - This will be used to make a process per unique category and define the array size for each of those processes

- Next goal is to actually make the forking processes. Not sure if it'll happen by tonight but I will at least get started.

From Brennan:
To compile my code use:
gcc server.c -o server
gcc server.c -o client

to run use
./server
and ./client
to connect
