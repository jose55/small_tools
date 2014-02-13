/* A little C++ Programm to test things */

// Include standard library
#include <iostream>
#include <algorithm>
using namespace std;

// print list with pointer
void print (initializer_list<int> vars)
{
    for (auto p = vars.begin(); p != vars.end(); ++p)
    {
      std::cout << *p << " ";
    }
    cout << endl;


}

// c++11 range based for loop to print list
void print2 (initializer_list<int> vars)
{
    for (int i : vars)
      cout << i << " ";
    cout << endl;

}

struct algo
{
  algo(initializer_list<int> v)
    {
      //the algorithm for_each() of the STL
      for_each(v.begin(),v.end(),[](int element){cout<<element<<" "; });

    cout<<endl;

    }
};

// Main programm code starts here
int main ()
{
    // new c++11 initialization
    initializer_list<int> numbers {12,4,5,64,12,75,35,75};

    print(numbers);
    print2({3,4,1,2,5,3,1,2});

    algo algorithm{3,2,3,6,7,4};//executes the constructor

    return 0;
}
