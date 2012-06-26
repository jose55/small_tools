/* A little C++ Programm to print prime numbers.
2012-06-26, Stefan Hammer <j.4@gmx.at>, GPLv3.
With the help of http://www.cplusplus.com/files/tutorial.pdf */

// We just need the iostream
#include <iostream>
using namespace std;

// The program starts here
int main ()
{
	int n;			// The number which gets tested
	int u;			// upper boundary
	bool isprime = true;	// Boolean to determine if the number is a prime
	
	cout << "In which range should the prime numbers be calculated? (eg: 1 100) ";
	cin >> n >> u;		// Write upper boundary into the value (ask user to determine one)
	cout << "Prime numbers are:" << endl;
	
	// This for loop starts at the lower bondary, and counts +1 until the upper bondary is reached
	for (n; n<=u; n++)
	{
		// A prime can only be divided by 1 and itself (so I test all numbers between 2 and n-1)
		for (int i = 2; i<n; i++)
		{
			// Calculate modulo to test if number is a prime.
			if (n % i == 0)
			{
				// If n modulo any other number is true only once, n can't be a prime.
				isprime = false;
				// leave the loop (no need to test other numbers)
				break;
			}
		}
		// only print prime numbers.
		if (isprime)
			cout << n << endl;
		// reset the boolean for the next number.
		isprime = true;
	}
}
