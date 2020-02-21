/* INTRO PARAGRAPH
is_val_in row: We loop through the columns of the board for a given row, if the value 'val' is in the row, we return 1
is_val_in row: We loop through the rows of the board for a given column, if the value 'val' is in the column, we return 1
is_val_in_3x3_zone: We use a series of else-if statements to see which zone needs to be checked.
                    Then, we loop through the given zone, if the value is in the zone, we return 1
is_val_valid: We use if statements to check that is_val_in_row, is_val_in_col, and is_val_in_row return 1.
              If any of them do, is_val_valid returns 0. If not, it returns 1
solve_sudoku: We loop through the board to check for empty cells. If there is one, we set a stop flag to exit the loop.
              Then, we loop through 1-9 (possible guesses) and check a) that the value is valid, and if it is, we check
                                                                     b) that with that value inserted, the rest of the board is sovlable using recursive backtracking
              If both of these conditions are met, the guess stays in its spot and the board gets solved.
  partners: edhar2, dilanp2
*/

#include "sudoku.h"

//-------------------------------------------------------------------------------------------------
// Start here to work on your MP7
//-------------------------------------------------------------------------------------------------

// You are free to declare any private functions if needed.

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

  assert(i>=0 && i<9);
  // BEG TODO

  int col, flag;                // defines cell and col variables
  for(col = 0; col < 9; col++)  // loops through columns
  {
    if(sudoku[i][col] == val)   // if the value is already in a cell (within the row)
        return 1;               // return 1 (true)
  }


  return 0;
  // END TODO
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

  assert(j>=0 && j<9);

  // BEG TODO
  int row, flag;                  // defines row, cell, and flag
  for(row = 0; row < 9; row++)    // loops through rows
  {
    if (sudoku[row][j] == val)    // if the any cell in the column holds val
      return 1;                   // return 1 (true)
  }

  return 0;
  // END TODO
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9);

  // BEG TODO

  if (i<3 && j<3)                         // if index is in the top-left zone
  {
      for (int k = 0; k<3; k++)
          for (int m = 0; m<3; m++)      // loop through its rows and cols
          {
              if (sudoku[k][m] == val)   // if the val exists here
              {
                  return 1;              // return 1 (true)
              }
          }
  }
  else if (i<3 && j<6)                  // if index is in the middle left zone
  {
      for (int k = 0; k<3; k++)
          for (int m = 3; m<6; m++)     // loop through rows and cols
          {
              if (sudoku[k][m] == val)  // if val exists here
              {
                  return 1;             // return 1 (true)
              }
          }
  }
  else if (i<3)                           // if index is in the bottom left zone
  {
      for (int k = 0; k<3; k++)
          for (int m = 6; m<9; m++)        // loop through rows and cols
          {
              if (sudoku[k][m] == val)    // if val exists here
              {
                  return 1;               // return 1 (true)
              }
          }
  }
  else if (i<6 && j<3)                    // if index is in top middle zone
  {
      for (int k = 3; k<6; k++)
          for (int m = 0; m<3; m++)       // loop through rows and cols
          {
              if (sudoku[k][m] == val)    // if val exists here
              {
                  return 1;               // return 1 (true)
              }
          }
  }
  else if (i<6 && j<6)                    // same as all those above, except with middle zone
  {
      for (int k = 3; k<6; k++)
          for (int m = 3; m<6; m++)
          {
              if (sudoku[k][m] == val)
              {
                  return 1;
              }
          }
  }
  else if (i<6)                            // same as all those above, except with middle bottom zone
  {
      for (int k = 3; k<6; k++)
          for (int m = 6; m<9; m++)
          {
              if (sudoku[k][m] == val)
              {
                  return 1;
              }
          }
  }
  else if (i<9 && j<3)                      // same as all those above, except with top right zone
  {
      for (int k = 6; k<9; k++)
          for (int m = 0; m<3; m++)
          {
              if (sudoku[k][m] == val)
              {
                  return 1;
              }
          }
  }
  else if (i<9 && j<6)                    // same as all those above, except with middle right zone
  {
      for (int k = 6; k<9; k++)
          for (int m = 3; m<6; m++)
          {
              if (sudoku[k][m] == val)
              {
                  return 1;
              }
          }
  }
  else                                    // same as all those above, except with bottom right zone
  {
      for (int k = 6; k<9; k++)
          for (int m = 6; m<9; m++)
          {
              if (sudoku[k][m] == val)
              {
                  return 1;
              }
          }
  }

  return 0;

  // END TODO
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9 && j>=0 && j<9);

  // BEG TODO
  int cell, row, col;
  row = i;
  col = j;
  //initializes row, col, and cell
  if(is_val_in_col(val, col, sudoku))
    return 0;
  if(is_val_in_row(val, row, sudoku))
    return 0;
  if(is_val_in_3x3_zone(val, row, col, sudoku))
    return 0;

  return 1;
  // END TODO
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {

    int row = 0;
    int i = 0;
    int j = 0;
    int col = 0;
    int stop = 0;

    for(row = 0; (row < 9)&& (stop < 1) ; row++)       // loops through rows
    {
        for(col = 0; col < 9; col++)                   // loops through cols
        {
            if (sudoku[row][col] == 0)                 // if cell is empty
            {
                i = row;                               // i = row
                j = col;                               // j = col
                stop = 2;                              // stop flag set
            }
        }
    }
    if (stop == 0)    // if we never find an empty cell, stop flag remains 0
    {
        return 1;     // so we return 1
    }
    else
    {

        for(int guess = 1; guess <= 9; guess++)
        {
            if(is_val_valid(guess, i, j, sudoku))            //if the guess is valid, and the rest of the sudoku board can be solved
            {
                sudoku[i][j] = guess;                       // we fill the cell with the guess
                if(solve_sudoku(sudoku))
                {
                    return 1;                               // if we can solve it with the guess, return 1
                }
                sudoku[i][j] = 0;                           // else we fill the cell with 0
            }
        }
    }
    return 0;


}
// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}
