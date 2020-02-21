 
#include "game.h"
/*  INTRO PARAGRAPH:
 make_game: We accessed items within the struct and gave them the values passed to make game (rows and cols) and set the score to 0. We also looped through all the cells to set every cell to -1 initially
 remake_game: We accessed the fields in _cur_game_ptr and set them to the values passed (new_rows and new_cols) and reset the score to 0. We alos looped through all the cells to set them to -1
 get_cell: We created a pointer variable to the current cell. Then, we used an if statement to make sure the cell being requested was in the board. If it was, we assigned the current cell pointer to have the address of that cell.
 move_w and move_s: We loop through the cols first, and then the rows (top --> bot for move_w, bot-->top for move). Essentially, we check for a non-empty cell, and then loop again (using temprow) to see if there are any empty cells above or below it, respectively. If there are, we swap those values (making the topmost/bottommost empty cell get the value of the cell being moved up/down, and emptying the cell that needed to be moved. Retflag is set if anything is moved or merged so we can return the correct value at the end of the function
 move_a and move_d: We loop through the cols first, and then the rows (left --> right for move_w, right --> left for move). Essentially, we check for a non-empty cell, and then loop again (using temprow) to see if there are any empty cells to the left or right of it, respectively. If there are, we swap those values (making the leftmost/rightmost empty cell get the value of the cell being moved left/right, and emptying the cell that needed to be moved. Retflag is set if anything is moved or merged so we can return the correct value at the end of the function
 legal_move_check: We loop through to find any empty cells, if there are, a flag is raised. The, we loop through to see if any two adjacent cells are of the same value. If there are, we set a different flag. If either flag is raised, we return 1 (meaning that a legal move is possible). If not, we return 0.
 The homies, aka
 partners: dilanp2, edhar2
 */
 
game * make_game(int rows, int cols)
/*! Create an instance of a game structure with the given number of rows
 and columns, initializing elements to -1 and return a pointer
 to it. (See game.h for the specification for the game data structure)
 The needed memory should be dynamically allocated with the malloc family
 of functions.
 */
{
    //Dynamically allocate memory for game and cells (DO NOT modify this)
    game * mygame = malloc(sizeof(game));
    mygame->cells = malloc(rows*cols*sizeof(cell));
    
    //YOUR CODE STARTS HERE:  Initialize all other variables in game struct
    mygame->rows = rows;                // initializes mygame.rows to rows
    mygame->cols = cols;                // initializes mygame.cols to cols
    mygame->score = 0;                  // initializes mygame.score to 0
    for(int i = 0; i < rows*cols; i++)  // loops through all cells of mygame
    {
        mygame->cells[i] = -1;            // gives each cell of mygame value of -1
    }
    
    return mygame;                      // returns pointer to current game
}
 
void remake_game(game ** _cur_game_ptr,int new_rows,int new_cols)
/*! Given a game structure that is passed by reference, change the
 game structure to have the given number of rows and columns. Initialize
 the score and all elements in the cells to -1. Make sure that any
 memory previously allocated is not lost in this function.
 */
{
    /*Frees dynamically allocated memory used by cells in previous game,
     then dynamically allocates memory for cells in new game.  DO NOT MODIFY.*/
    free((*_cur_game_ptr)->cells);
    (*_cur_game_ptr)->cells = malloc(new_rows*new_cols*sizeof(cell));
    
    //YOUR CODE STARTS HERE:  Re-initialize all other variables in game struct
    (*_cur_game_ptr)->rows = new_rows;   // re-initializes game's rows to new_rows
    (*_cur_game_ptr)->cols = new_cols;   // re-initializes game's cols to new_cols
    (*_cur_game_ptr)->score = 0 ;        // resets game's score to 0
    for(int i = 0; i < new_rows*new_cols; i++)   // loops through cells of current game
    {
        (*_cur_game_ptr)->cells[i] = -1;   // resets each tile to -1
    }
    
    return;
}
 
void destroy_game(game * cur_game)
/*! Deallocate any memory acquired with malloc associated with the given game instance.
 This includes any substructures the game data structure contains. Do not modify this function.*/
{
    free(cur_game->cells);
    free(cur_game);
    cur_game = NULL;
    return;
}
 
cell * get_cell(game * cur_game, int row, int col)
/*! Given a game, a row, and a column, return a pointer to the corresponding
 cell on the game. (See game.h for game data structure specification)
 This function should be handy for accessing game cells. Return NULL
 if the row and col coordinates do not exist.
 */
{
    //YOUR CODE STARTS HERE
    cell *current_cell;                                                              // creates a pointer for current cell
    if(((row*col) < (cur_game->rows * cur_game->cols)) && row >= 0 && col >= 0)      // makes sure that location is within the
    {
        current_cell = &(cur_game->cells[(row*(cur_game->cols)) + col]);                  // assigns the current cell pointer the current cell
        return current_cell;
    }
    return NULL;
}
 
int move_w(game * cur_game)
/*!Slides all of the tiles in cur_game upwards. If a tile matches with the
 one above it, the tiles are merged by adding their values together. When
 tiles merge, increase the score by the value of the new tile. A tile can
 not merge twice in one turn. If sliding the tiles up does not cause any
 cell to change value, w is an invalid move and return 0. Otherwise, return 1.
 */
{
    int row_bound = cur_game->rows;//variable for row bounds
    int col_bound = cur_game->cols;//variable for col bounds
    int row, col, tempRow; //temp variables
    int retflag; //variable for return value
    cell *currentCellPtr; //pointer for current cell
    cell *comparison; //pointer for comparison cell
    //move
    for (col = 0; col<col_bound; col++) //loop to move the cells upwards
    {
        for(row = 1; row<row_bound; row++)
        {
            currentCellPtr = get_cell(cur_game, row, col); //sets current cell
            if(*currentCellPtr != -1) //only goes in if cell is not empty
            {
                for(tempRow = 0; tempRow<row; tempRow++)
                {
                    comparison = get_cell(cur_game, tempRow, col); //sets comparison cell
                    if (*comparison == -1) //only goes in if comparison is empty so we can switch the two cells
                    {
                        retflag = 1; //sets return flag to 1
                        *comparison = *currentCellPtr; //swaps current and comparison cells
                        *currentCellPtr = -1; //sets current cell to empty
                        break; //breaks out of the loop
                    }
                }
            }
        }
    }
    //merge
    cell *currentCell;
    int doubleCell;
    cell *aboveCell;
    int col1, row1, row2;
    for(col1 = 0; col1 < col_bound; col1++)                                    //loops through columsn
    {
        for(row1 = 1; row1 < row_bound; row1++)                                //loop through rows
        {
            row2 = row1 - 1;
            currentCell = get_cell(cur_game, row1, col1);                      // pointer to current cell
            aboveCell = get_cell(cur_game, row2, col1);                        // pointer to cell below
            if((*currentCell == *aboveCell) && (*currentCell != -1))           // if current cell is the same as the one directly below it
            {
                doubleCell = (*currentCell) + (*currentCell);                  // double the cell value
                cur_game->score = (cur_game->score) + (doubleCell);            // updates the score
                *aboveCell = doubleCell;
                *currentCell = -1;                                             // empties cell below
                retflag  = 1;
                
            }
        }
    }
    //move
    for (col = 0; col<col_bound; col++) //same exact thing as previous move function
    {
        for(row = 1; row<row_bound; row++)
        {
            currentCellPtr = get_cell(cur_game, row, col);
            if(*currentCellPtr != -1)
            {
                for(tempRow = 0; tempRow<row; tempRow++)
                {
                    comparison = get_cell(cur_game, tempRow, col);
                    if (*comparison == -1)
                    {
                        retflag = 1;
                        *comparison = *currentCellPtr;
                        *currentCellPtr = -1;
                        break;
                    }
                }
            }
        }
    }
    if (retflag == 1) //decides what to return based on return flag variable
    {
        return 1;
    }
    else
    {
        return 0;
    }
};
 
int move_s(game * cur_game) //slide down
{
    int row_bound = cur_game->rows;//variable for row bounds
    int col_bound = cur_game->cols;//variable for col bounds
    int row, col, tempRow; //temp variables
    int retflag; //variable for return value
    cell *currentCellPtr; //pointer for current cell
    cell *comparison; //pointer for comparison cell
    //move
    for (col = 0; col<col_bound; col++) //moves all the cells downwards
    {
        for(row = (row_bound-2); row >= 0; row--)
        {
            currentCellPtr = get_cell(cur_game, row, col); //sets current cell pointer
            if(*currentCellPtr != -1) //only goes in if current cell is not empty
            {
                for(tempRow = (row_bound-1); tempRow>row; tempRow--)
                {
                    comparison = get_cell(cur_game, tempRow, col); //sets comparison cell
                    if (*comparison == -1) //only goes in if comparison is empty
                    {
                        retflag = 1; //sets return flag to 1
                        *comparison = *currentCellPtr; //swaps current and comparison cells
                        *currentCellPtr = -1; //sets current cell to be empty
                        break; //breaks out of loop
                    }
                }
            }
        }
    }
    //merge
    cell *currentCell;
    int doubleCell;
    cell *aboveCell;
    int col1, row1, row2;
    for(col1 = 0; col1 < col_bound; col1++)                          //loops through column
    {
        for(row1 = (row_bound-1); row1 > 0; row1--)                  //loop through rows
        {
            row2 = row1 - 1;
            currentCell = get_cell(cur_game, row1, col1);       // pointer to current cell
            aboveCell = get_cell(cur_game, row2, col1);     // pointer to cell below
            if((*currentCell == *aboveCell) && (*currentCell != -1))                          // if current cell is the same as the one directly below it
            {
                doubleCell = (*currentCell) + (*currentCell);                  // double the cell value
                cur_game->score = (cur_game->score) + (doubleCell);                // updates the score
                *aboveCell = doubleCell;
                *currentCell = -1;                                    // empties cell below
                retflag  = 1;
                
            }
        }
    }
    //move
    for (col = 0; col<col_bound; col++) //same exact thing as previous move above
    {
        for(row = (row_bound-2); row >= 0; row--)
        {
            currentCellPtr = get_cell(cur_game, row, col);
            if(*currentCellPtr != -1)
            {
                for(tempRow = (row_bound-1); tempRow>row; tempRow--)
                {
                    comparison = get_cell(cur_game, tempRow, col);
                    if (*comparison == -1)
                    {
                        retflag = 1;
                        *comparison = *currentCellPtr;
                        *currentCellPtr = -1;
                        break;
                    }
                }
            }
        }
    }
    if (retflag == 1) //returns the value of retflag
    {
        return 1;
    }
    else
    {
        return 0;
    }
};
 
int move_a(game * cur_game) //slide left
{
    int row_bound = cur_game->rows; //variable for row bound
    int col_bound = cur_game->cols; //variable for col bound
    int row, col, tempCol; //temp variables for row and col
    int retflag; //sets return flag variable
    cell *currentCellPtr; //sets pointer for current cell
    cell *comparison; //sets pointer for comparison cell
    //move
    for (row = 0; row<row_bound; row++) //moves all the cells left
    {
        for(col = 1; col<col_bound; col++)
        {
            currentCellPtr = get_cell(cur_game, row, col); //sets the current cell
            if(*currentCellPtr != -1) //only goes in if current cell is not empty
            {
                for(tempCol = 1; tempCol<=col; tempCol++) //loop to actually swap the cell with an empty cell
                {
                    int tempTempCol = tempCol - 1;
                    comparison = get_cell(cur_game, row, tempTempCol); //sets the comparison cell
                    if (*comparison == -1) //only goes in if current cell is empty
                    {
                        retflag = 1; //sets return flag to 1
                        *comparison = *currentCellPtr; //swaps current and comparison cells
                        *currentCellPtr = -1; //sets current cell to be empty
                        break; //breaks out of loop
                    }
                }
            }
        }
    }
    //merge
    cell *currentCell;
    int doubleCell;
    cell *leftCell;
    int col1, row1, col2;
    for(row1 = 0; row1 < row_bound; row1++)                          //loops through columsn
    {
        for(col1 = 1; col1 < col_bound; col1++)                  //loop through rows
        {
            col2 = col1 - 1;
            currentCell = get_cell(cur_game, row1, col1);       // pointer to current cell
            leftCell = get_cell(cur_game, row1, col2);     // pointer to cell below
            if((*currentCell == *leftCell) && (*currentCell != -1))                          // if current cell is the same as the one directly below it
            {
                doubleCell = (*currentCell) + (*currentCell);                  // double the cell value
                cur_game->score = (cur_game->score) + (doubleCell);                // updates the score
                *leftCell = doubleCell;
                *currentCell = -1;                                    // empties cell below
                retflag  = 1;
                
            }
        }
    }
    //move
    for (row = 0; row<row_bound; row++) //same exact thing as previous move loop
    {
        for(col = 1; col<col_bound; col++)
        {
            currentCellPtr = get_cell(cur_game, row, col);
            if(*currentCellPtr != -1)
            {
                for(tempCol = 0; tempCol<col; tempCol++)
                {
                    comparison = get_cell(cur_game, row, tempCol);
                    if (*comparison == -1)
                    {
                        retflag = 1;
                        *comparison = *currentCellPtr;
                        *currentCellPtr = -1;
                        break;
                    }
                }
            }
        }
    }
    if (retflag == 1) //returns the value of return flag
    {
        return 1;
    }
    else
    {
        return 0;
    }
};
 
int move_d(game * cur_game) //slide right
{
    int row_bound = cur_game->rows; //variable for row bound
    int col_bound = cur_game->cols; //variable for col bound
    int row, col, tempCol; //temp variables for row and col
    int retflag; //sets return flag variable
    cell *currentCellPtr; //sets pointer for current cell
    cell *comparison; //sets pointer for comparison cell
    //move
    for (row = 0; row<row_bound; row++) //loop to move the cells right
    {
        for(col = (col_bound-2); col >= 0; col--)
        {
            currentCellPtr = get_cell(cur_game, row, col); //sets the current cell pointer
            if(*currentCellPtr != -1) //only goes in if current cell is not empty
            {
                for(tempCol = (col_bound-1); tempCol>col; tempCol--)
                {
                    comparison = get_cell(cur_game, row, tempCol); //sets comparison cell pointer
                    if (*comparison == -1) //only goes in if comparison is empty
                    {
                        retflag = 1; //sets return flag to be 1
                        *comparison = *currentCellPtr; //swaps comparison and current cells
                        *currentCellPtr = -1; //sets current cell to be 1
                        break; //breaks out of loop
                    }
                }
            }
        }
    }
    //merge
    cell *currentCell;
    int doubleCell;
    cell *aboveCell;
    int col1, row1, col2;
    for(row1 = 0; row1 < row_bound; row1++)                          //loops through columsn
    {
        for(col1 = (col_bound-1); col1 > 0; col1--)                  //loop through rows
        {
            col2 = col1 - 1;
            currentCell = get_cell(cur_game, row1, col1);       // pointer to current cell
            aboveCell = get_cell(cur_game, row1, col2);     // pointer to cell below
            if((*currentCell == *aboveCell) && (*currentCell != -1))                          // if current cell is the same as the one directly below it
            {
                doubleCell = (*currentCell) + (*currentCell);                  // double the cell value
                cur_game->score = (cur_game->score) + (doubleCell);                // updates the score
                *aboveCell = doubleCell;
                *currentCell = -1;                                    // empties cell below
                retflag  = 1;
                
            }
        }
    }
    //move
    for (row = 0; row<row_bound; row++) //same exact code as previous move loop
    {
        for(col = (col_bound-2); col >= 0; col--)
        {
            currentCellPtr = get_cell(cur_game, row, col);
            if(*currentCellPtr != -1)
            {
                for(tempCol = (col_bound-1); tempCol>col; tempCol--)
                {
                    comparison = get_cell(cur_game, row, tempCol);
                    if (*comparison == -1)
                    {
                        retflag = 1;
                        *comparison = *currentCellPtr;
                        *currentCellPtr = -1;
                        break;
                    }
                }
            }
        }
    }
    if (retflag == 1) //returns the value of return flag
    {
        return 1;
    }
    else
    {
        return 0;
    }
};
 
int legal_move_check(game * cur_game)
/*! Given the current game check if there are any legal moves on the board. There are
 no legal moves if sliding in any direction will not cause the game to change.
 Return 1 if there are possible legal moves, 0 if there are none.
 */
{
    int row_bound = cur_game->rows; //variable for row bounds
    int col_bound = cur_game->cols; //variable for col bounds
    int isEmpty=0; //variable to check if there is an empty cell on the board
    int hasAdjacent = 0; //variable to check if any two adjacent cells are identical
    cell *currentCell1; //pointer to current cell
    for (int row =0; row<row_bound; row++) //loop to check for an empty cell
    {
        for(int col=0; col<col_bound; col++)
        {
            currentCell1 = get_cell(cur_game, row, col);       // pointer to current cell
            if (*currentCell1==-1) //sets isEmpty to true if there is an empty cell
            {
                isEmpty = 1;
            }
        }
    }
    cell *currentCell; //below 5 variables are for the current cell and its 4 neighbors
    cell *aboveCell;
    cell *belowCell;
    cell *leftCell;
    cell *rightCell;
    for (int row = 1; row< (row_bound-1); row++) //loops through each cell
    {
        for (int col = 1; col < (col_bound-1); col++)
        {
            currentCell = get_cell(cur_game, row, col); //sets the value of current cell and the below 4 lines set the value of each of its neighbors
            aboveCell = get_cell(cur_game, (row-1), col);
            belowCell = get_cell(cur_game, (row+1), col);
            leftCell = get_cell(cur_game, row, (col-1));
            rightCell = get_cell(cur_game, row, (col+1));
            if (((*currentCell)==(*aboveCell))||((*currentCell)==(*belowCell))||((*currentCell)==(*leftCell))||((*currentCell)==(*rightCell))) //sets hasAdjacent to true if two cells are   equal
            {
                hasAdjacent = 1;
            }
        }
    }
    if (isEmpty == 1 || hasAdjacent == 1) //if any cell is empty or two adjacent cells are equal return 1 else return 0
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
 
 
/*! code below is provided and should not be changed */
 
void rand_new_tile(game * cur_game)
/*! insert a new tile into a random empty cell. First call rand()%(rows*cols) to get a random value between 0 and (rows*cols)-1.
 */
{
    
    cell * cell_ptr;
    cell_ptr =     cur_game->cells;
    
    if (cell_ptr == NULL){
        printf("Bad Cell Pointer.\n");
        exit(0);
    }
    
    
    //check for an empty cell
    int emptycheck = 0;
    int i;
    
    for(i = 0; i < ((cur_game->rows)*(cur_game->cols)); i++){
        if ((*cell_ptr) == -1){
            emptycheck = 1;
            break;
        }
        cell_ptr += 1;
    }
    if (emptycheck == 0){
        printf("Error: Trying to insert into no a board with no empty cell. The function rand_new_tile() should only be called after tiles have succesfully moved, meaning there should be at least 1 open spot.\n");
        exit(0);
    }
    
    int ind,row,col;
    int num;
    do{
        ind = rand()%((cur_game->rows)*(cur_game->cols));
        col = ind%(cur_game->cols);
        row = ind/cur_game->cols;
    } while ( *get_cell(cur_game, row, col) != -1);
    //*get_cell(cur_game, row, col) = 2;
    num = rand()%20;
    if(num <= 1){
        *get_cell(cur_game, row, col) = 4; // 1/10th chance
    }
    else{
        *get_cell(cur_game, row, col) = 2;// 9/10th chance
    }
}
 
int print_game(game * cur_game)
{
    cell * cell_ptr;
    cell_ptr =     cur_game->cells;
    
    int rows = cur_game->rows;
    int cols = cur_game->cols;
    int i,j;
    
    printf("\n\n\nscore:%d\n",cur_game->score);
    
    
    printf("\u2554"); // topleft box char
    for(i = 0; i < cols*5;i++)
        printf("\u2550"); // top box char
    printf("\u2557\n"); //top right char
    
    
    for(i = 0; i < rows; i++){
        printf("\u2551"); // side box char
        for(j = 0; j < cols; j++){
            if ((*cell_ptr) == -1 ) { //print asterisks
                printf(" **  ");
            }
            else {
                switch( *cell_ptr ){ //print colored text
                    case 2:
                        printf("\x1b[1;31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4:
                        printf("\x1b[1;32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8:
                        printf("\x1b[1;33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 16:
                        printf("\x1b[1;34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 32:
                        printf("\x1b[1;35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 64:
                        printf("\x1b[1;36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 128:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 256:
                        printf("\x1b[32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 512:
                        printf("\x1b[33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 1024:
                        printf("\x1b[34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 2048:
                        printf("\x1b[35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4096:
                        printf("\x1b[36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8192:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    default:
                        printf("  X  ");
                        
                }
                
            }
            cell_ptr++;
        }
        printf("\u2551\n"); //print right wall and newline
    }
    
    printf("\u255A"); // print bottom left char
    for(i = 0; i < cols*5;i++)
        printf("\u2550"); // bottom char
    printf("\u255D\n"); //bottom right char
    
    return 0;
}
 
int process_turn(const char input_char, game* cur_game) //returns 1 if legal move is possible after input is processed
{
    int rows,cols;
    char buf[200];
    char garbage[2];
    int move_success = 0;
    
    switch ( input_char ) {
        case 'w':
            move_success = move_w(cur_game);
            break;
        case 'a':
            move_success = move_a(cur_game);
            break;
        case 's':
            move_success = move_s(cur_game);
            break;
        case 'd':
            move_success = move_d(cur_game);
            break;
        case 'q':
            destroy_game(cur_game);
            printf("\nQuitting..\n");
            return 0;
            break;
        case 'n':
            //get row and col input for new game
        dim_prompt: printf("NEW GAME: Enter dimensions (rows columns):");
            while (NULL == fgets(buf,200,stdin)) {
                printf("\nProgram Terminated.\n");
                return 0;
            }
            
            if (2 != sscanf(buf,"%d%d%1s",&rows,&cols,garbage) ||
                rows < 0 || cols < 0){
                printf("Invalid dimensions.\n");
                goto dim_prompt;
            }
            
            remake_game(&cur_game,rows,cols);
            
            move_success = 1;
            
        default: //any other input
            printf("Invalid Input. Valid inputs are: w, a, s, d, q, n.\n");
    }
    
    
    
    
    if(move_success == 1){ //if movement happened, insert new tile and print the game.
        rand_new_tile(cur_game);
        print_game(cur_game);
    }
    
    if( legal_move_check(cur_game) == 0){  //check if the newly spawned tile results in game over.
        printf("Game Over!\n");
        return 0;
    }
    return 1;
}
 
 
 
 
 
 
 

