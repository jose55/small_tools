/* A little C++ Programm to test pointers.
2012-09-10, With the help of "The C++ Standard Library 2nd edition.*/

#include <vector>
#include <iostream>
#include <memory>

using namespace std;

// create a type that saves pointers in a vector
typedef vector<const int*> PointerVect;

// overload output operator << to be able to print this construct. Note that we are not printing elem, but the assigned value of this pointer
std::ostream& operator<< (std::ostream& os, PointerVect& pv) {
    for (auto elem : pv) {
        os << *elem << " "; // *elem prints the assigned int!
    }
    return os;
}

// main program starts here
int main ()
{
	//define a PointVector in the program
	PointerVect pointers;
	// defind some random integers
	int x(1), y(2), z(3);
	// print the integers
	cout << "Defined int: " << endl;
	for (auto elem : {x,y,z}) {
		cout << elem << " ";
	}
	cout << endl;

	// define a as a pointer to x
	int* pA = &x;

	// insert pointers to these integers into our container
	pointers.push_back(pA);
	pointers.push_back(&y);
	pointers.push_back(&z);
	pointers.push_back(pA);
	// print the container to cout using the overloader at the beginning
	cout << "Vector contains pointers to: " << endl << pointers << endl;

	// overwrite x through a
	*pA = 6;
	cout << "x is now: "<< x << endl;
	// print the container to cout again
	cout << "Vector now contains: " << endl << pointers << endl;

	//shared pointers
	// make share pointer
	shared_ptr<int> pB(new int(7));
	// another shared pointer with declaring own deleter. writes deleted <number> when deleted
	shared_ptr<int> pC(new int(5),
					[](int *p) {
						cout << "deleted " << *p << endl;
						delete p;
					});


	shared_ptr<int> pD = make_shared<int>(*pA+*pC);
	// fill this pointers also into a vector
	vector<shared_ptr<int>> smart_pointers;

	for (auto elem : {pB, pC, pD, pC, pC, pC, pC}) {
		smart_pointers.push_back(elem);
	}

	// change something
	*pB = *pA-*pC;
	// print the shared pointers
	cout << "Shared Pointers: " << endl;
	for (auto elem : smart_pointers) {
		cout << *elem << " ";
	}

	// tell us how often pB is used
	cout << endl << "pC used: " << pC.use_count() << endl;
	// resize vector
	smart_pointers.resize(2);
	// tell us how often pB is used now
	cout << "pC used after resizing vector: " << pC.use_count() << endl;
	// assign nullptr to pB
	cout << "assign nullptr to pC" << endl;
	pC = nullptr;
	// tell us how often pB is used now
	cout << "pC used after assigning nullptr: " << pC.use_count() << endl;

	return 0;
}
