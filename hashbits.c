/* A little C++ Programm to testing hashbit sizes for the barriers program. 
16.01.2013 Stefan Hammer
compile with g++ -std=c++0x -o hashbits hashbits.c 
no input, not much output :-) */

// Include standard library
#include <iostream>
using namespace std;

// Main programm code starts here
int main ()
{

typedef struct _hash_entry {
  char *structure;    /* my structure */ 
  float energy;       /* my energy */
  int basin;          /* which basin do I belong to */
  int GradientBasin;  /* for Gradient Basins */
  int ccomp;          /* in which connected component am I */
  int n;              /* my index in energy sorted list */
  struct _hash_entry *down;  /* pointer to lowest neighbor */
  int *POV;           /* for Posets only */
} hash_entry;


cout << "hash_entry " << sizeof(hash_entry) << endl;
cout << "char " << sizeof(char) << endl;
cout << "4x int " << sizeof(int) << endl;
cout << "1x char pointer " << sizeof(char*) << endl;
cout << "1x int pointer " << sizeof(int*) << endl;
cout << "1x float " << sizeof(float) << endl;
cout << "1x hash_entry pointer " << sizeof(_hash_entry*) << endl;


}
