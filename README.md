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

Note: For option1 to display the records, there is some bug which is not letting stock and genre columns to display the records.
Also, there is an issues with the amount of books displayed. Instead it will only display the first 8 books. We believe the
issues is caused from buffer overflow from the amount of books there are in each process.


