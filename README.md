# CS4243GroupProject

from Blake:

I just uploaded the first draft of process.c. This file contains:

- Two static 3D char (2D String) arrays storing the contents of the file. One for each file. (The hardcoded portion).

- Main function that acts as a tempory menu that requests file name and the column to focus on

  - This menu is just for interfacing with my program. I know someone else is making the full menu.

- Process function that searches through the specified file array for the specified column and collects the unique categories and counts the number of items within it.

  - This will be used to make a process per unique category and define the array size for each of those processes

- Next goal is to actually make the forking processes. Not sure if it'll happen by tonight but I will at least get started.
