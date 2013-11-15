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
	
			for (auto elem : k) {
				boost::hash_combine(hash, boost::hash_value(elem.first));
				boost::hash_combine(hash, boost::hash_value(elem.second));
			}
	
			std::cerr << "hash is: " << hash << std::endl;
	
			return hash;
		}
};

// global variables
std::vector< std::unordered_map < MyKey , unsigned long long , MyKeyHash>> n;

// main program starts here
int main () {
	std::vector< std::unordered_map < MyKey , unsigned long long , MyKeyHash>> n(10);
	
	MyKey mykey;
	
	mykey.insert(std::make_pair(1,3));
	mykey.insert(std::make_pair(5,1));
	
	n[0][mykey] = 10;
	
	mykey.insert(std::make_pair(23,18));
	n[9][mykey] = 1234;
}
