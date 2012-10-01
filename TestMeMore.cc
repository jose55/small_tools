/* A little C++ Programm to test more things */

// Include standard library
#include <iostream>
#include <tuple>
#include <functional> //for ref function
#include <deque> //for double ended queue
#include <unordered_map> // for unordered maps


using namespace std;

int foo (int a)
{
    a++;
    return a;
}

int foo1 (int & a)
{
    a++;
    return a;
}

//print any container
template <typename T>
void printContainer (const T& cont)
{
	for (const auto& elem : cont) {
		cout << elem << endl;
	}
}

// Main programm code starts here
int main ()
{
    int a = 1;
	cout << "Print a: " << a << endl;
    cout << "Print Pointer to a: " << &a << endl;
    // passing the variable only changes it in the function, but not in main
    cout << "Print foo(a): " << foo(a) << endl;
    cout << "Print a: " << a << endl;
    // this is passing the variable by reverence: therefore it can be changed
    cout << "Print foo1(&a): " << foo1(a) << endl;
    cout << "Print a: " << a << endl;

	//automatic made tuple
    auto t = make_tuple(43,45,"Hello World!");
	//print hello world with get value at pos 2
    cout << get<2>(t) << endl;

    int c, d;
    //assign c with second tuple value
    tie(ignore,c,ignore) = t;
    // same with d
    d = get<1>(t);
    cout << "this is c: " << c << endl;
    cout << "this is d: " << d << endl;

    //tuple types can be reverences
    string s ("hi");
    int i (42);
    tuple<string&,int&> tup(s,i);
    cout << "tup is: " << get<0>(tup) << ", " << get<1>(tup) << endl;
    s = "hi changed me";
    i = 12;
    cout << "tup is changed: " << get<0>(tup) << ", " << get<1>(tup) << endl;

    //rest reference function ref
    auto tup1 = make_tuple(ref(s),4);
    s = s.append(" again"); //append to string
    cout << "tup1 is: " << get<0>(tup1) << ", " << get<1>(tup1) << endl;


    //deque test
    deque<int> de;
    // fill this thing from the front
    int x{};
    for(x; x<10;++x) {
		de.push_front(x);
    }
    // read it to cout
    for(auto elem : de) {
		cout << elem << " ";
    }
    cout << endl;
    // use printContainer funktion to print again
    printContainer(de);

    unordered_map<float,string> mymap = {
    {1.0,"Hello"},
    {2.1,"unordered"},
    {3.4,"Map!"}
    };

    mymap[1.7] = "wooow";
	mymap[1.7].append(" nice.");

	for (const auto& elem : mymap) {
		cout << elem.first << ": " << elem.second << endl;
	}
}
