/* A little C++ Programm to test iterators.
2012-09-10, With the help of "The C++ Standard Library 2nd edition.*/

// includes
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iterator>
#include <map>
#include <list>
#include <sstream>
using namespace std;

// user definded generic function to print containers as arrays, vectors,...
template <typename T>
inline void PRINT_ELEMENTS (const T& container, const string& delimiter = "")
{
	for (const auto& elem : container) {
		cout << elem << delimiter;
	}
	cout << endl;
}

// overload output operator << to be able to print maps
std::ostream& operator<< (std::ostream& os, map<int, string>& m) {
    for (auto elem : m) {
        os << elem.first << ": " << elem.second << endl;
    }
    return os;
}

// The program starts here
int main ()
{
	//container to save input
	vector<string> input;
	list<string> list;
	map<int, string>map;
	// copy iterator reads from istream_iteratur(standard in) and back_inserter writes strings to end of container. end is eof.
	copy (istream_iterator<string>(cin), istream_iterator<string>(), back_inserter(input));

	// print raw input with user defined generic function, which should print any array, vector, list...
	cout << "Raw input: " << endl;
	PRINT_ELEMENTS(input, ", ");
	cout << endl << "---------------------------------------------------" << endl;

	// write words also into list to see the difference.
	copy (input.begin(), input.end(), back_inserter(list));

	// print words as list with user defined generic function, which should print any container
	cout << "As a List: " << endl;
	PRINT_ELEMENTS(list, ", ");
	cout << endl << "---------------------------------------------------" << endl;

	// also make a map to have fun, fill using range based for loop
	int i = 0;
	for (auto item : list) {
		map.insert(pair<int, string>(i, move(item)));
		++i;
	}

	// print print map with overloading the output operator <<
	cout << "Map input: " << endl;
	cout << map << endl << "---------------------------------------------------" << endl;

	//sort elements from input
	sort (input.begin(), input.end());

	// delete all strings #include and #c++11 from the vector using remove_if and lambdas
	// as the elements are not erased, they will appear on the end (delete just moves elements)
	// therefore we remember the new logical end in an iterator provided by the remove function
	// this new end is then used as end for printing the list in the next step
	vector<string>::iterator end = remove_if (input.begin(), input.end(),
								[] (string str) {									//the lambda starts here
									return str == "#include" || str == "c++11" || str == "!=";
								});

	cout << "OUTPUT:" << endl;
	//print all elements to cout using unique_copy iterator (no duplicates) and constant iterators begin/end
	unique_copy (input.begin(), end, ostream_iterator<string>(cout, ", "));
	cout << endl << "---------------------------------------------------" << endl;
	// if you want to completely delete some entries, you have to erase them from behind.
	input.erase(end, input.end());
	// The output should be the same as before
	unique_copy (input.begin(), input.end(), ostream_iterator<string>(cout, ", "));
	cout << endl;

	return 0;

}
