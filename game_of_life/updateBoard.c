/* Intro Paragraph:
	countLiveNeighbour: we initialized position to the position of the current cell using the formula given, and created a variable called liveCount to count the number of live neighbours per cell.
  Then, we intiialized integers a through h to be the 8 neighbours of the current cell. Using a series of if statmenets, we then calculated the number of live neighbours a cell had by checking that
  the neighbour being checked a) exists and b) was live. If both (a) and (b) were met, we incremented live count.
  updateBoard: We created the array 'boardCopy', which is used to be the temporary game board during the update process. We also created varibles for the current position on the board (position)
  and for the number of live neighbours of the current cell (numLive). We used nested for loops to loop through the board. Then, using the countLiveNeighbour function, we found the number of live
  neighbours a cell on 'board' had, and used that to update the corresponding cell. This updated value (1 or 0) was placed in 'boardCopy'. Finally, when each cell had been updated and placed in
  'boardCopy', we put the values from 'boardCopy' (the updated board) in 'board'.
  aliveStable: We loop through the 'board' using nested for loops. Then, we used the countLiveNeighbour functions for each cell to see how many live neighbours each cell in 'board'. Then, we used an if
  statement to see if the cell would change if updated. If the cell needed updating, we return 0. If the loop goes through the entire board and doesn't require updating, we return 1

  partners: edhar2, dilanp2
*/


#include <stdlib.h>
#include <unistd.h>
#include "updateBoard.h"
/*
 * countLiveNeighbor
 * Inputs:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * row: the row of the cell that needs to count alive neighbors.
 * col: the col of the cell that needs to count alive neighbors.
 * Output:
 * return the number of alive neighbors. There are at most eight neighbors.
 * Pay attention for the edge and corner cells, they have less neighbors.
 */

int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col){


    int position = (row * boardColSize) + col; //initiaize current position in 1D array
    int liveCount = 0; //initialize counter of live neighbors

    int a = (position - boardColSize) - 1; //initialize neighbor A location - topleft neighbour
    int b = a +1; //initialize neighbor B location - top neighbour
    int c = b +1; //initialize neighbor C location - topright neighbour
    int d = position - 1; //initialize neighbor D location - left neighbour
    int e = position + 1; //initialize neighbor E location - right neighbour
    int f = (position + boardColSize) - 1; //initialize neighbor F location - bottomleft neighbour
    int g = f + 1; //initialize neighbor G location - bottom neighbour
    int h = g +1; //initialize neighbor H location - bottomright neighbour

    if((row != 0) && (col != 0) && (board[a] == 1)) // makes sure the neighbor a exists and checks if it is alive
    {
        liveCount++ ;
    }

    if((row != 0) && (board[b] == 1)) // makes sure the neighbor b exists and checks if it is alive
    {
        liveCount++ ;
    }

    if((row != 0) && (col != (boardColSize-1)) && (board[c] == 1)) // makes sure the neighbor c exists and checks if it is alive
    {
        liveCount++ ;
    }

    if((col != 0) && (board[d] ==1)) // makes sure the neighbor d exists and checks if it is alive
    {
        liveCount++;
    }
    if((col != (boardColSize-1)) && (board[e]==1)) // makes sure the neighbor e exists and checks if it is alive
    {
        liveCount++;
    }
    if((row != (boardRowSize-1)) && (col != 0) && (board[f] == 1)) // makes sure the neighbor f exists and checks if it is alive
    {
        liveCount ++;
    }
    if((row != (boardRowSize-1)) && (board[g] == 1)) // makes sure the neighbor g exists and checks if it is alive
    {
        liveCount++;
    }
    if((row != (boardRowSize-1)) && (col != (boardColSize-1)) && (board[h] == 1)) // makes sure the neighbor h exists and checks if it is alive
    {
        liveCount++;
    }
    return liveCount; // returns number of alive neighbors
}

/*
 * Update the game board to the next step.
 * Input:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: board is updated with new values for next step.
 */
void updateBoard(int* board, int boardRowSize, int boardColSize) {
    int numLive = 0; // creates variable to store number of live neighbors
    int boardCopy [boardRowSize*boardColSize - 1];    // creates a copy board of the board
    int pos = 0; // variable to hold position of cell in array

    for(int i = 0; i < boardRowSize; i++) // loops through rows
    {
        for(int j = 0; j < boardColSize; j++)    //loops through columns
        {
            pos = (i*boardColSize) + j;        // calculates current position on board
            numLive = countLiveNeighbor(board, boardRowSize, boardColSize, i, j); // counds number of live neighbours for each position on a board
            if((numLive < 2 || numLive > 3) && (board[pos] == 1)) //checks to see if an alive cell needs to die
            {
                boardCopy[pos] = 0;
            }
            else if((numLive == 3) && (board[pos] == 0)) // checks to see if a dead cell needs to come alive
            {
                boardCopy[pos] = 1;
            }
            else
            {
                boardCopy[pos] = board[pos]; // copies the cells from board into boardCopy that don't get inputted by the above if/else-if statements
            }
        }
    }

    for (int k = 0; k < boardRowSize*boardColSize - 1; k++) //uses the for loop to update board with the values from boardCopy
    {
        board[k] = boardCopy[k];
    }



}

/*
 * aliveStable
 * Checks if the alive cells stay the same for next step
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: return 1 if the alive cells for next step is exactly the same with
 * current step or there is no alive cells at all.
 * return 0 if the alive cells change for the next step.
 */
int aliveStable(int* board, int boardRowSize, int boardColSize){
    int numLive = 0; // initializes the variable to store the number of alive neighbors
    int pos = 0; // initializes the variable to store the position of the current cell in the 1D array
    for(int i = 0; i < boardRowSize; i++) // loops through rows
    {
        for(int j = 0; j < boardColSize; j++) // loops through columns
        {
            numLive = countLiveNeighbor(board, boardRowSize, boardColSize, i, j); // sets numLive equal to the number of alive neighbors for the current cell
            pos = (i*boardColSize + j); // sets position equal to the current cell's position in the 1D array
            if (((numLive < 2 || numLive > 3) && (board[pos] == 1))||((numLive == 3) && (board[pos] == 0))) // conditions for a cell changing
            {
                return 0; // if a cell changes, the board must change, meaning 0 is returned
            }
        }
    }
    return 1; // if 0 is never returned above, then 1 is returned here, implying that the board stayed the same
}
