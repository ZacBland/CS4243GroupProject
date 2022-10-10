# CS4243GroupProject


To run server:

gcc -Wall -o server process.c server.c -lrt && ./server

To run client:

gcc -o client client.c && ./client

On client side:

Once connection created between server and client, it asks the client to select an option (Eg: 1)
Now, it asks to select a column (Eg: 1)

Now, it prompts to choos an option (1. Display the records, 2. Save the records, 3. Display the summary, 4. Exit)
Eg: select 1 which displays the unique values of the column, choose any of them it then displays the respective records. Similarly it is same for option2. The output file "output.txt" will be saved in the same path.

If you want to exit, please select option4.



