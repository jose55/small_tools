/* A little C++ Programm to test things */

// Include standard library
#include <iostream>
using namespace std;

// print list with pointer
void print (std::initializer_list<int> vars)
{
    for (auto p = vars.begin(); p != vars.end(); ++p)
    {
        std::cout << *p << endl;
    }
}

// c++11 range based for loop to print list
void print2 (std::initializer_list<int> vars)
{
    for (int i : vars)
    cout << i << endl;
}

// Main programm code starts here
int main ()
{
    // new c++11 initialization
    initializer_list<int> numbers {12,4,5,64,12,75,35,75};

    print(numbers);
    print2({3,4,1,2,5,3,1,2});
}
