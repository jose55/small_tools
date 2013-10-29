/* A little C++ Programm to print prime numbers.
2012-06-26, Stefan Hammer <j.4@gmx.at>, GPLv3.
With the help of http://www.cplusplus.com/files/tutorial.pdf 

Compile with: g++ PrintPrimes.cc -o PrintPrimes
*/

// We just need the iostream
#include <iostream>
// function definition
bool isPrime (int number);

// The program starts here
int main (int argc, char ** argv)
{
	int n;			// The number which gets tested
	int u;			// upper boundary
	bool isprime = true;	// Boolean to determine if the number is a prime
	
	std::cout << "In which range should the prime numbers be calculated? (eg: 1 100) ";
	std::cin >> n >> u;		// Write upper boundary into the value (ask user to determine one)
	std::cout << "Prime numbers are:" << std::endl;
	
	// This for loop starts at the lower bondary, and counts +1 until the upper bondary is reached
	for (n; n<=u; n++)
	{
		// run the function isPrime which returns true or false and only print prime numbers then.
		if (isPrime(n))
			std::cout << n << std::endl;
	}
}

// function 
bool isPrime (int number) {
	// A prime can only be divided by 1 and itself (so I test all numbers between 2 and n-1)
	for (int i = 2; i<number; i++)
	{
		// Calculate modulo to test if number is a prime.
		if (number % i == 0)
		{
			// If number modulo any other number is true only once, number can't be a prime.
			return false;
		}
	}
	// if not able to divide, then it is a prime
	return true;
}
