#include <stdlib.h>
#include <stdio.h>


int is_prime(int number);
int print_semiprimes(int a, int b);


int main(){   
   int a, b;
   printf("Input two numbers: ");
   scanf("%d %d", &a, &b);
   if( a <= 0 || b <= 0 ){
     printf("Inputs should be positive integers\n");
     return 1;
   }

   if( a > b ){
     printf("The first number should be smaller than or equal to the second number\n");
     return 1;
   }

   // TODO: call the print_semiprimes function to print semiprimes in [a,b] (including a and b)
}


/*
 * TODO: implement this function to check the number is prime or not.
 * Input    : a number
 * Return   : 0 if the number is not prime, else 1
 */
int is_prime(int number)
{
  // 2 is a prime
  if (number == 2) return 1;
  else
  {
    // if the number is divisible by anything, we return false
    for(int i = 2; i < number; i++)
      if (number % i == 0)  return 0;
  }
  // else, it is only divisible by 1 and itself, so it is prime
  return 1;
}


/*
 * TODO: implement this function to print all semiprimes in [a,b] (including a, b).
 * Input   : a, b (a should be smaller than or equal to b)
 * Return  : 0 if there is no semiprime in [a,b], else 1
 */
int print_semiprimes(int a, int b)
{
  // keeps track of whether a semiprime exists within the range
  int has_semiprimes = 0;
  for(int n = a; n < b+1; n++)
  {
    int repeat = 0;
    for(int k = 2; k < n; k++)
    {
      // if n is an unprinted semiprime, we print it
      if((n % k == 0) && is_prime(k) && is_prime(n/k) && (repeat == 0))
        printf("%d", n);
    }
  }
  return has_semiprimes;
}



