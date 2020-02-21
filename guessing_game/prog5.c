/*   INTRO PARAGRAPH: We completed the assignment of coding setseed, makeguess, and
 * startgame. set_seed takes the inputted seed value and passes it as a parameter to sscanf to
 * to take the seed value from seed_str and put it into the variable seed. Then, seed is passed to
 * srand to be used as the seed value for rand. start_game sets the four numbers to be guessed
 * using the rand function and sets the pointers one through four to point to values of those
 * solutions. It also sets guess_number to one. Make_guess calculates the number of misplaced
 * and perfect matches using if-else statements and prints how many perfect matches, guesses,
 * and misplaced matches there are. We check to make sure there are only four integers inputted
 * using the return value of sscanf
 * partners: edhar2, dilanp2
 */

/*
 *
 * prog5.c - source file adapted from UIUC ECE198KL Spring 2013 Program 4
 *           student code -- GOLD VERSION by Steven S. Lumetta
 */


/*
 * The functions that you must write are defined in the header file.
 * Blank function prototypes with explanatory headers are provided
 * in this file to help you get started.
 */



#include <stdio.h>
#include <stdlib.h>

#include "prog5.h"


/*
 * You will need to keep track of the solution code using file scope
 * variables as well as the guess number.
 */

static int guess_number;
static int solution1;
static int solution2;
static int solution3;
static int solution4;


/*
 * set_seed -- This function sets the seed value for pseudorandom
 * number generation based on the number the user types.
 * The input entered by the user is already stored in the string seed_str by the code in main.c.
 * This function should use the function sscanf to find the integer seed value from the
 * string seed_str, then initialize the random number generator by calling srand with the integer
 * seed value. To be valid, exactly one integer must be entered by the user, anything else is invalid.
 * INPUTS: seed_str -- a string (array of characters) entered by the user, containing the random seed
 * OUTPUTS: none
 * RETURN VALUE: 0 if the given string is invalid (string contains anything
 *               other than a single integer), or 1 if string is valid (contains one integer)
 * SIDE EFFECTS: initializes pseudo-random number generation using the function srand. Prints "set_seed: invalid seed\n"
 *               if string is invalid. Prints nothing if it is valid.
 */
int set_seed (const char seed_str[])
{
    //    Example of how to use sscanf to read a single integer and check for anything other than the integer
    //    "int seed" will contain the number typed by the user (if any) and the string "post" will contain anything after the integer
    //    The user should enter only an integer, and nothing else, so we will check that only "seed" is read.
    //    We declare
    //    int seed;
    //    char post[2];
    //    The sscanf statement below reads the integer into seed.
    //    sscanf (seed_str, "%d%1s", &seed, post)
    //    If there is no integer, seed will not be set. If something else is read after the integer, it will go into "post".
    //    The return value of sscanf indicates the number of items read succesfully.
    //    When the user has typed in only an integer, only 1 item should be read sucessfully.
    //    Check that the return value is 1 to ensure the user enters only an integer.
    //    Feel free to uncomment these statements, modify them, or delete these comments as necessary.
    //    You may need to change the return statement below
    int seed = 0; // sets the seed value to 0
    char post[2]; // creates an array to store spaces after the sequence
    int number = 0;
    number = sscanf (seed_str, "%d%1s", &seed, post); // stores the value of the seed into the variable seed
    if (number == 1)
    {
        srand(seed); // sets the seed for the rand() function
        return 1;
    }
    else
    {
        printf("set_seed: invalid seed\n");
        return 0;
    }
}


/*
 * start_game -- This function is called by main.c after set_seed but before the user makes guesses.
 *               This function creates the four solution numbers using the approach
 *               described in the wiki specification (using rand())
 *               The four solution numbers should be stored in the static variables defined above.
 *               The values at the pointers should also be set to the solution numbers.
 *               The guess_number should be initialized to 1 (to indicate the first guess)
 * INPUTS: none
 * OUTPUTS: *one -- the first solution value (between 1 and 8)
 *          *two -- the second solution value (between 1 and 8)
 *          *three -- the third solution value (between 1 and 8)
 *          *four -- the fourth solution value (between 1 and 8)
 * RETURN VALUE: none
 * SIDE EFFECTS: records the solution in the static solution variables for use by make_guess, set guess_number
 */
void
start_game (int* one, int* two, int* three, int* four)
{
    solution1 = (rand()%8)+1; // sets solution1 equal to a random number between 1 and 8
    solution2 = (rand()%8)+1;// sets solution2 equal to a random number between 1 and 8
    solution3 = (rand()%8)+1;// sets solution3 equal to a random number between 1 and 8
    solution4 = (rand()%8)+1;// sets solution4 equal to a random number between 1 and 8
    *one = solution1; // sets one to point to the value at solution1
    *two = solution2; // sets two to point to the value at solution2
    *three = solution3; // sets three to point to the value at solution3
    *four = solution4; // sets four to point to the value at solution4
    guess_number = 1; // sets the variable guess_number to 1
}

/*
 * make_guess -- This function is called by main.c after the user types in a guess.
 *               The guess is stored in the string guess_str.
 *               The function must calculate the number of perfect and misplaced matches
 *               for a guess, given the solution recorded earlier by start_game
 *               The guess must be valid (contain only 4 integers, within the range 1-8). If it is valid
 *               the number of correct and incorrect matches should be printed, using the following format
 *               "With guess %d, you got %d perfect matches and %d misplaced matches.\n"
 *               If valid, the guess_number should be incremented.
 *               If invalid, the error message "make_guess: invalid guess\n" should be printed and 0 returned.
 *               For an invalid guess, the guess_number is not incremented.
 * INPUTS: guess_str -- a string consisting of the guess typed by the user
 * OUTPUTS: the following are only valid if the function returns 1 (A valid guess)
 *          *one -- the first guess value (between 1 and 8)
 *          *two -- the second guess value (between 1 and 8)
 *          *three -- the third guess value (between 1 and 8)
 *          *four -- the fourth color value (between 1 and 8)
 * RETURN VALUE: 1 if the guess string is valid (the guess contains exactly four
 *               numbers between 1 and 8), or 0 if it is invalid
 * SIDE EFFECTS: prints (using printf) the number of matches found and increments guess_number(valid guess)
 *               or an error message (invalid guess)
 *               (NOTE: the output format MUST MATCH EXACTLY, check the wiki writeup)
 */

int
make_guess (const char guess_str[], int* one, int* two,
            int* three, int* four)
{
    //  One thing you will need to read four integers from the string guess_str, using a process
    //  similar to set_seed
    //  The statement, given char post[2]; and four integers w,x,y,z,
    //  sscanf (guess_str, "%d%d%d%d%1s", &w, &x, &y, &z, post)
    //  will read four integers from guess_str into the integers and read anything else present into post
    //  The return value of sscanf indicates the number of items sucessfully read from the string.
    //  You should check that exactly four integers were sucessfully read.
    //  You should then check if the 4 integers are between 1-8. If so, it is a valid guess
    //  Otherwise, it is invalid.
    //  Feel free to use this sscanf statement, delete these comments, and modify the return statement as needed
    char post[2];
    int w = 0; // intialize 4 input digits of user guess
    int x = 0;
    int y = 0;
    int z = 0;
    int a = sscanf (guess_str, "%d%d%d%d%1s", &w, &x, &y, &z, post); /*take in 4 digits of user guess*/
    if (a == 4&& w>0 && w<9 && x>0 && x<9 && y>0 && y<9 && z>0 && z<9)
    {
        {
            int perf_match = 0; //intialize perfect match counter
            int misp_match = 0; //intialize misplaced match counter
            int match1 = 0;
            int match2 = 0;
            int match3 = 0;
            int match4 = 0;
            if (w == solution1) // check user digit 1 for perfect match
            {
                perf_match = perf_match + 1;
                match1 = 1;
            }
            else if (w == solution2 && match2 == 0) /* check if digit 2 is matched and compares with user digit 1 for misplaced match*/
            {
                match2 = 1;
                misp_match = misp_match + 1;
            }
            else if (w == solution3 && match3 == 0) /*check if digit 3 is matched and compares with user digit 1 for misplaced match*/
            {
                match3 = 1;
                misp_match = misp_match + 1;
            }
            else if (w == solution4 && match4 == 0) /* check if digit 2 is matched and compares with user digit 4 for misplaced match*/
            {
                match4 = 1;
                misp_match = misp_match + 1;
            }
            if (x == solution2 && match2 == 1)
            {
                perf_match = perf_match + 1;
                misp_match = misp_match - 1;
            }
            else if (x == solution2) // check user digit 2 for perfect match
            {
                perf_match = perf_match + 1;
                match2 = 1;
            }
            else if (x == solution1 && match1 == 0) /* check if digit 2 is matched and compares with user digit 2 for misplaced match*/
            {
                match1 = 1;
                misp_match = misp_match + 1;
            }
            else if (x == solution3 && match3 == 0) /* check if digit 3 is matched and compares with user digit 2 for misplaced match*/
            {
                match3 = 1;
                misp_match = misp_match + 1;
            }
            else if (x == solution4 && match4 == 0) /* check if digit 4 is matched and compares with user digit 2 for misplaced match*/
            {
                match4 = 1;
                misp_match = misp_match + 1;
            }
            if (y == solution3 && match3 == 1)
            {
                perf_match = perf_match + 1;
                misp_match = misp_match - 1;
            }
            else if (y == solution3) // check user digit 3 for perfect match
            {
                perf_match = perf_match + 1;
                match3 = 1;
            }
            else if (y == solution1 && match1 == 0) /* check if digit 1 is matched and compares with user digit 3 for misplaced match*/
            {
                match1 = 1;
                misp_match = misp_match + 1;
            }
            else if (y == solution2 && match2 == 0) /* check if digit 2 is matched and compares with user digit 3 for misplaced match*/
            {
                match2 = 1;
                misp_match = misp_match + 1;
            }
            else if (y == solution4 && match4 == 0) /* check if digit 4 is matched and compares with user digit 3 for misplaced match*/
            {
                match4 = 1;
                misp_match = misp_match + 1;
            }
            if (z == solution4 && match4 == 1)
            {
                perf_match = perf_match + 1;
                misp_match = misp_match - 1;
            }
            else if (z == solution4) // check user digit 4 for perfect match
            {
                perf_match = perf_match + 1;
                match4 = 1;
            }
            else if (z == solution2 && match2 == 0) /* check if digit 2 is matched and compares with user digit 4 for misplaced match*/
            {
                match2 = 1;
                misp_match = misp_match + 1;
            }
            else if (z == solution3 && match3 == 0) /* check if digit 3 is matched and compares with user digit 4 for misplaced match*/
            {
                match3 = 1;
                misp_match = misp_match + 1;
            }
            else if (z == solution1 && match1 == 0) /* check if digit 1 is matched and compares with user digit 4 for misplaced match*/
            {
                match4 = 1;
                misp_match = misp_match + 1;
            }
            //print the counted amounts misplaced and perfect matches
            printf("With guess %d, you got %d perfect matches and %d misplaced matches.\n", guess_number, perf_match, misp_match);
            guess_number = guess_number + 1; // increment guess
            *one = w;
            *two = x;
            *three = y;
            *four = z;
            return 1;
        }
    }
    else
    {
        printf("make_guess: invalid guess\n"); //if 4 digits not inputed, prompt user input in invalid
        return 0;
    }
}
