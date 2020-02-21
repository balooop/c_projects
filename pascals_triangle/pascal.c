#include <stdio.h>
#include <stdlib.h>
/* The program prints a specific row of the Pascal's triangle.
 * The user is prompted to type the row of the triangle
 * The program then stores the inputed value as an integer called row
 * if row is less that 0 or greater than 40, the program prints out an invalid message
 * if the row is a valid input, the program moves onto the loop to calculate the digits of a row
 * the number of terms in a row is equal to row+1 so the int terms in . initialized to row + 1
 * the first loop goes through each digit of the row
 * the first digit is always 1, so the program will not enter the second loop for the first digit
 * the second loop calculates the the value of each digit according to the given equation based on the row number and digit number
 * the digit value is printed and the loop increments to the next digit value
 * partners: dilanp2, edhar2
 * */

int main()
{
    int row;
    
    printf("Enter a row index: ");
    scanf("%d",&row);
    
    if(row <0 || row >40) // if the row choice is outside the parameters...
    {
        printf("iNvALiD rOw cHOicE"); // prints an error message
    }
    
    else{
        
        int terms = row+1; // number of terms in each row is one more than the row number
        
        for (int j=1; j<(terms+1); j++) // sets up K value from expression to print all digits
        {
            unsigned long digit=1;        // initializes digit to be printed
            for (int k=1; k<j; k++)        // program wont enter this loop for first term (just prints 0)
            {
                digit = digit*(terms-k)/k;    // calculates value of digit to be printed via loop
            }
            printf("%lu  ", digit);        // actually prints the coefficient
        }
    }
    printf("\n");    //prints newline after coefficients have indeed been printed
    
    return 0;
}
