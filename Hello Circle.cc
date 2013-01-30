/* A little C++ Programm to calculate circle values.
2012-06-25, Stefan Hammer <j.4@gmx.at>, GPLv3.
With the help of http://www.cplusplus.com/files/tutorial.pdf */

// Include standard library
#include <iostream>
#include <string>
using namespace std;
// Define Pi as it is needed very often and is a constant
#define Pi 3.14159

// Global variables
float r = 5;					// A float variable
string question = "Give me a radius: ";		// A string
char answer;					// A character
bool sphere;					// A boolean (true/false)

// Main programm code starts here
int main ()
{
	// Prints Hello Message
	cout << question;
	// Get radius from input
	cin >> r;
	// Get answer to my question
	cout << "Do you want to calculate sherical values? (y/n): ";
	cin >> answer;
	cout << "\n";
	// Convert answer from char to bool with an conditional operator (condition ? result if true : result if false;)
	answer == 'y' ? sphere = true : sphere = false;

	// Calculate Values
	float circumfence = 2*r*Pi;
	float area = r*r*Pi;
	
	// Output Values (<< connects outputs, endl prints a newline character: \n)
	cout << "Your radius: " << r << endl;
	cout << "The circumfence is: " << circumfence << endl;
	cout << "The area is: " << area << endl;

	// Sphereical values (again with conditional operator)
	sphere==true ? cout << "Sphere Surface: " << 4*Pi*r*r << endl : cout << "No spherical values!" << endl;
	sphere==true ? cout << "Sphere Volume: " << 4/3*Pi*r*r*r << endl : cout << endl;

	// Return no error
	return 0;
}
