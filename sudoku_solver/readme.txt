This is a program that solves a sudoku board. My team wrote the functions is_val_in_row, is_val_in_col, is_val_in_3x3_zone, is_val_valid and solve_sudoku.  
is_val_in_row, is_val_in_col, and is_val_in_3x3_zone are helper functions to is_val_valid, and check if the input value is repeated in the row, column, or 3x3 sudoku subsection respectively.
is_val_valid checks if a guessed value works at a given position on the sudoku board.
solve_sudoku uses recursive backtracking to solve a 9x9 sudoku board. It checks the board for empty cells and guesses values in the range 1-9 for each spot, calling is_val_valid. It then checks if the board can be solved with the guess in place, and if it cannot, it backtracks and changes the guess.
This was a project for ECE220