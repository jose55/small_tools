/* A little C++ Programm to try out a custom hash function.
2013-11-15,

Compile with: g++ --std=c++11 CustomHashFunction.cc -o CustomHashFunction
*/

#include <vector>
#include <unordered_map>
#include <functional>
#include <iostream>
#include <memory>
#include <boost/functional/hash.hpp>


// typedefs
typedef std::unordered_map < int, int > MyKey;

class MyKeyHash {
	public:
		std::size_t operator() (const MyKey& k) const {
			// Start with 0 as a hash value   .
			std::size_t hash = 0;
			// include all the items of the key in the hash_value to make it unique
			for (auto elem : k) {
				boost::hash_combine(hash, boost::hash_value(elem.first));
				boost::hash_combine(hash, boost::hash_value(elem.second));
			}
	
			std::cerr << "hash is: " << hash << std::endl;
			// return the hash value
			return hash;
		}
};

// global variables
std::vector< std::unordered_map < MyKey , unsigned long long , MyKeyHash>> n;

// main program starts here
int main () {
	// construct the map
	std::vector< std::unordered_map < MyKey , unsigned long long , MyKeyHash>> n(10);
	// generate a key
	MyKey mykey;
	// add items to the key
	mykey.insert(std::make_pair(1,3));
	mykey.insert(std::make_pair(5,1));
	// now add a first item to the container at pos 0, mykey
	n[0][mykey] = 10;
	// make the key somehow different
	mykey.insert(std::make_pair(23,18));
	// add another value
	n[9][mykey] = 1234;
	
	// not get the item again:
	// 1) the easy way:
	std::cerr << n[9][mykey] << std::endl;
	// 2) and the hard way
	std::unordered_map < MyKey , unsigned long long , MyKeyHash>::const_iterator item = n[9].find(mykey);
	
	if (item != n[9].end()) {
		std::cerr << item->second << std::endl;
	}
	
}
