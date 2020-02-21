This is a program that allows the user to play the game 2048. My team wrote the game.c. We implemented the functions make_game, destroy_game, get_cell, move_w, move_s, move_a, move_d, legal_move_check, and remake_game.
make_game, destroy_game, and remake_game are fairly self explanatory. make_game allocates a 2D array with a user-inputted size and stores it as a 1D array. remake_game accepts a pointer to a game and a new set of board dimensions, and reallocates memory for the new game state. destroy_game frees all memory associated with the game.
get_cell returns the cell requested by input parameters. This is a helper function.
the various move_(letter) functions perform the core function of the 2048, sliding the tiles up, down, left, or right. It ensures that sliding of values occurs properly, and equal numbers are combined.
This was a project I completed for ECE220.
