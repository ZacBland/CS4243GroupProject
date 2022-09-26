/*
Group: B
Name: Blake Barton
Email: blake.barton@okstate.edu
Date: 9/25/22
Description:

This file currently has three primary functions:
1 - take user input on which input file and column (temporary)
2 - read the input file and save them into an array
3 - traverse array and find unique values in column and count occurence of each

Future functionality:
1 - create process for each unique value
2 - communicate server to clients using message queue

*/
#include <stdio.h>
#include <stdlib.h>

typedef char* String;

char bookInfo[703][6][210];
char amazonBestsellers[550][7][210];

//readFile method that reads specified input file and stores in static-sized array
void readFile(char inputFile[25], int cols) {

    char (*array)[cols][210];
    if (cols == 6) array = bookInfo; //determines which matrix to store in
    else array = amazonBestsellers;

    FILE* f;
    char ch;

    f = fopen(inputFile, "r");

    if (NULL == f) {
        printf("file could not be opened.\n");
    }

    int count = 0;
    int row = 0;
    int col = 0;

    char str[210];
    //do-while loop reads file character by character, parses it, and stores whole column in array
    do {
        ch = fgetc(f);
        if (ch == '"') {
            count = count + 1; //counter to tell if reading inside a quotation so it will treat commas as normal characters
            strncat(str, &ch, 1);
        } else if (ch == ',') {
            if (count % 2 == 1) { //comma used in quotation
                strncat(str, &ch, 1);
            } else { //comma used to separate columns
                sprintf(array[row][col], "%s", str);
                memset(str, 0, 210);
                col++;
            }
        } else if (ch == '\n') { //end of row
            sprintf(array[row][col], "%s", str);
            memset(str, 0, 210);
            col = 0;
            row++;
        } else { //normal character
            strncat(str, &ch, 1);
        }
    } while (ch != EOF);

    fclose(f);
}


//Process function will look at the selected column and divide it up by unique categories
//Currently just prints off unique names and how many items are in that category
//Eventually will split them into processes (work in progress)
int process(int rows, int columns, int col, int processes) {

    //selects file array to read from
    char (*array)[columns][210];
    if (rows == 703) array = bookInfo;
    else array = amazonBestsellers;

    //creates arrays to store category/process name (example: each book genre or year) and the number of items per category
    String category[processes];
    int amount[processes];

    //initializes the new arrays
    for (int k = 0; k < processes; k++) {
        category[k] = "";
        amount[k] = 0;
    }

    int index = 0; //counts through the new arrays
    int flag = 0; //0: name not in array, 1: name already in array

    //iterates through file array
    for (int i = 1; i < rows; i++) {

        //searches through new array to check if category from file is already present, if so flags and increases the count
        for (int k = 0; k < index; k++) {
            if (strcmp(category[k], array[i][col]) == 0) {
                amount[k]++;
                flag = 1;
            }
        }

        //adds category to the array if flag is not raised
        if (flag == 0) {
            category[index] = array[i][col];
            amount[index] = 1;
            index++;
        }
        flag = 0; //clears flag for next row
    }

    //prints unique categories and number of items associated (TEMP)
    for (int k = 0; k < processes; k++) {
        printf("%s %d\n", category[k], amount[k]);
    }


    //now start dividing up into processes and print those items:


    return 0;

}
/*
int main() {

    char input[25];
    printf("Enter a file (bookInfo.txt or amazonBestsellers.txt):\n");
    scanf("%s", input);

    if (strcmp(input, "bookInfo.txt") == 0) {
        printf("Which category: Book category, Star rating, or Stock?\n");
        scanf("%s", input);

        readFile("bookInfo.txt", 6);
        if (strcmp(input, "Book") == 0) {
            process(703, 6, 1, 43);
        } else if (strcmp(input, "Star") == 0) {
            process(703, 6, 2, 5);
        } else if (strcmp(input, "Stock") == 0) {
            process(703, 6, 4, 2);
        } else printf("Incorrect category.\n");

    } else if (strcmp(input, "amazonBestsellers.txt") == 0) {
        printf("Which category: User rating, Year, or Genre?\n");
        scanf("%s", input);

        readFile("amazonBestsellers.txt", 7);
        if (strcmp(input, "User") == 0) {
            process(550, 7, 2, 10);
        } else if (strcmp(input, "Year") == 0) {
            process(550, 7, 5, 11);
        } else if (strcmp(input, "Genre") == 0) {
            process(550, 7, 6, 2);
        } else printf("Incorrect category.\n");

    } else {
        printf("Incorrect file name.\n");
    }

    return 0;
}
*/

