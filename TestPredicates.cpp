/* A little C++ Programm to test pointers.
2012-09-10, With the help of "The C++ Standard Library 2nd edition.*/

#include <deque> // is a vector which is open on both ends!
#include <iostream>
#include <string>
#include <algorithm> //for sort()

using namespace std;

// class to store Title and Year of Movies
class Movie {
	public:
		string Title;
		long Year;
		void print();
};

// Function to print Information to cout
void Movie::print()
{
	cout << "    " << Title << " (" << Year << ")" << endl;
}

// Binary predicate is ideal to sort by two criteria
// First by year and if equal, sort by name
bool movieSorting (const Movie& m1, const Movie& m2)
{
	return m1.Year < m2.Year ||
		(m1.Year == m2.Year && m1.Title < m2.Title);
}

// Function to fill the string and long into Movie class
Movie addMovie (string title, long year)
{
	Movie my_movie;
	my_movie.Title = title;
	my_movie.Year = year;
	return my_movie;
}

// main program starts here
int main ()
{
	// a deque is used to store the list of Movies
	deque<Movie> movies;
	// fill the list
	movies.push_back(addMovie("Friede den Huetten",2007));
	movies.push_back(addMovie("Matrix",1976));
	movies.push_back(addMovie("Avatar",2007));
	movies.push_back(addMovie("Lion King",1994));
	movies.push_back(addMovie("Star Wars",1976));

	// print without sorting
	cout << "Without sorting: " << endl;
	for (auto elem : movies) {
		elem.print();
	}

	// sort this list using Predicates as cirterion
	sort(movies.begin(), movies.end(), movieSorting);

	// print the sorted list
	cout << "Sorting done: " << endl;
	for (auto elem : movies) {
		elem.print();
	}
}
