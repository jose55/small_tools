/* A little C++ Programm to test the calling of ViennaRNA library functions
2013-12-03,
You need the newest ViennaRNA library installed globally or adjust the paths!
(https://www.tbi.univie.ac.at/~ronny/RNA/index.html)
Compile with: g++ -fopenmp -g -Wall --std=c++11 -I/usr/include/ViennaRNA/ -L/usr/lib64/ testRNAlib.cc -lRNA -lm -o testRNAlib
*/

#include <vector>
#include <string>
#include <iostream>

extern "C" {
	#include "fold.h"
}

// typedefs


// global variables


// main program starts here
int main () {
	
	std::string sequence;
	std::string structure;
	
	std::cout << "Input a Sequence (AUGC) followed by a Structure (dot-bracket): " << std::endl;
	std::cin >> sequence;
	std::cin >> structure;

	if (sequence.length() != 0 && structure.length() != 0) {
		float energy;
		energy = energy_of_structure(sequence.c_str(), structure.c_str(), 0); 
		std::cout << "Energy of structure is: " << energy << std::endl;
	}	
}
