This is a program that uses a DFS algorithm to solve a maze. My team wrote the maze.c file. Its functions are createMaze, destroyMaze, printMaze, and solveMazeDFS.
createMaze reads a text file that contains a set of characters representing a maze, allocates appropriate memory, and creates the maze as array of cells within a "maze" struct based on the text file's specified layout. It also initializes all other members of the maze struct.
destroyMaze frees all memory associated with the maze array and struct.
printMaze prints the maze's cells
solveMazeDFS utilizes a DFS algorithm to solve the maze, checking right, down, up, and left and marking points as visited and/or a part of the solution path along the way. It recursively calls itself.
This was a project I completed for ECE220
