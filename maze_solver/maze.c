/* INTRO PARAGRAPH
Hi Mr./Ms. TA I hope your day's going well.
createMaze: We opens and reads the maze file and initializes it into the maze_t struct. We used dynamic memory allocation, as well as File I/O functions to do this.
destroyMaze: This function destroys the maze and frees the space associated with it.
printMaze: This function traverses the maze's cells and displays them
solveMazeDFS: This function uses a depth-first-search algorithm to solve the maze, using a series of if statements to either mark each space in the maze as 'visited' or a part of the 'path' from the start to the end. 

the bois aka
partners: dilanp2, edhar2
*/

#include <stdio.h>
#include <stdlib.h>
#include "maze.h"


/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
maze_t * createMaze(char * fileName)
{
    // Your code here. Make sure to replace following line with your own code.
    int width, height;                                              // variables for the width and height of the maze
    FILE* mazeText;                                                 // creates a FILE pointer for the text file containing the maze 
    mazeText = fopen(fileName, "r");                                // opens the maze file and has mazeText point to it
    fscanf(mazeText, "%d %d", &height, &width);                     // scans the maze's first two values for width and height
    maze_t* maze = (maze_t*) malloc(sizeof(maze_t));            //dynamically allocates     
    maze->height = height;                                          //  initializes the height of the maze
    maze->width = width + 1;                                        // initalizes the width of the maze, accounting for the newline character
    maze->cells = (char **)malloc(height * sizeof(char *));         // allocates memory for the rows of the maze
    int i, w, h;                                                    // counter variables
    for (i = 0; i < height; i++)
    {
        maze->cells[i] = (char *) malloc((width+1) * sizeof(char)); // loops through the maze's columns and allocates memory for them
    }
    for (h = 0; h < height; h++)                                    // loop through cols
    {
        for (w = 0; w < (width+1); w++)                             // loops through rows
        {
            fscanf(mazeText, "%c", &(maze->cells[h][w]));           // scans the maze file and initalizes the cells
            if (maze->cells[h][w] == START)                         // sets the start point of the maze
            {
                maze->startRow = h;
                maze->startColumn = w;
            }
            if (maze->cells[h][w] == END)                           // sets the end of the maze
            {
                maze->endRow = h;
                maze->endColumn = w;
            }
        }
    }
    fclose(mazeText);                                               // closes maze info text file
    return maze;                                        
}

/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze)
{
    int i;  
    for (i = 0; i < maze->height; i++)                              // loops throught the maze
    {
        free(maze->cells[i]);                                       // frees maze columns
    }
    free(maze->cells);                                              // frees maze columns                  
    if(maze != NULL)
    {
        free(maze);                                                 // frees the struct
    }
}

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{
    int i, j;
    for (i = 0; i < maze->height; i++)                              // loops through cols
    {
        for (j = 0; j < maze->width; j++)                           // loops through rows
        {
            printf("%c", maze->cells[i][j]);                        // prints cells
        }
    }
    printf("\n");
}

/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search,
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */
int solveMazeDFS(maze_t * maze, int col, int row)
{
    if (maze->cells[row][col] == END || (maze->endRow == row && maze->endColumn == col))                                                   // if we at the endof the maze, return finished
    {
        return 1;
    }
    if (col < 0 || row < 0 || col >= maze->width || row >= maze->height || (maze->cells[row][col] != EMPTY && maze->cells[row][col] != START))
    // if we aren't at the start, but also out of the bounds, we return 0
    {
        return 0;
    }
    if(maze->cells[row][col] != START)                  
    // if we visit a place that isn't a start, we mark it with PATH (*)
    {
        maze->cells[row][col] = PATH;
    }
    if (solveMazeDFS(maze, col + 1, row) == 1)
    {
    // move right one column and try to solve
        return 1;
    }
    if (solveMazeDFS(maze, col, row + 1) == 1)
    {
    // move down one row and try to solve
        return 1;
    }
    if (solveMazeDFS(maze, col, row - 1) == 1)
    {
    // move up one row and try to solve
        return 1;
    }
    if (solveMazeDFS(maze, col-1, row) == 1)
    {
    // move left one column and try to solve
        return 1;
    }
    maze->cells[row][col] = VISITED;                // mark the place as visited
    return 0;
}



