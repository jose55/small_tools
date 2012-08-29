/* A little C++ Programm implementing depth first search.
2012-08-20, Stefan Hammer <j.4@gmx.at>, GPLv3.*/

#include "OptionParser.hh"
#include "OptionParser.cc"
#include "version.hh"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
using namespace std;
using namespace biu;

//variables
//Vertex Number
int vertex;
typedef std::vector<int> vertexList;
//list of neighbouring verteces
vertexList neighbours;
//adjacency List (vertex numver, list of neighbouring verteces)
std::map<int,vertexList> adjacencyList;

//table to store discoverytime and finishtime
struct time_table {
    time_table(int d, int f = 0) : discoverytime(d), finishtime(f) {
    }
    int discoverytime;
    int finishtime;
    //friend std::ostream& operator<< (std::ostream& os, const struct time_table& t);
};
// map of time_tables of all vertices
typedef map<int,time_table> time_table_map;
time_table_map times;

// overload << operator to be able to print time_table and vertexLists
std::ostream& operator<< (std::ostream& os, time_table& t) {
    os << "(" << t.discoverytime << "," << t.finishtime << ")";
    return os;
}

std::ostream& operator<< (std::ostream& os, vertexList& vL) {
    for(auto pos =vL.begin(); pos != vL.end(); ++pos) {
        const auto& item = *pos;
        cout << item;
        if(pos != vL.end()-1) {
            cout << ",";
        }
    }
    return os;
}

std::ostream& operator<< (std::ostream& os, time_table_map& m) {
    for (auto elem : m) {
        os << "{" << elem.first << ":" << elem.second << "}" << endl;
    }
    return os;
}

//function declaration
void printAdjacencyList(std::map<int,vertexList> adjacencyList);
time_table_map DFS(std::map<int,vertexList> adjacencyList, int startVertex);
void changeTime(int vertex, int discoverytime, int finishtime);


int main(int argc, char ** argv) {

    //define arguments and input/output stream
	std::istream* input = &std::cin;
	std::ifstream* inputFile = NULL;
	std::ostream* out = &std::cout;
	std::ofstream* outFile = NULL;

	OptionMap allowedArgs;
	allowedArgs.push_back(biu::COption("in", false, COption::STRING, "Input file name or 'STDIN' when to read from standard input", "STDIN"));
	allowedArgs.push_back(biu::COption("out", true, biu::COption::STRING, "Output file name or 'STDOUT' when to write to standard output", "STDOUT"));
	allowedArgs.push_back(biu::COption("max", true, COption::INT, "maximal degeneration that is used"));
	allowedArgs.push_back(biu::COption("help", true, biu::COption::BOOL, "Displays help on all parameters"));
	allowedArgs.push_back(biu::COption("version", true, biu::COption::BOOL, "Version information"));

	COptionParser opts = COptionParser(allowedArgs, argc, argv, "infotext");

	// arguments parseable and all mandatory arguments given
	if (opts.argExist("help")) {
		opts.coutUsage();
		return 0;
	}

	if (opts.argExist("version")) {
		giveVersion();
		return 0;
	}

	if (opts.noErrors()) {
        //maybe take variables from options here
	} else {
            return -1;
	}

    try {

       // set input stream
		if (opts.getStrVal("in").size() == 0) {
			throw 1;
		} else if (opts.getStrVal("in").compare("STDIN") != 0) {
			inputFile = new std::ifstream(opts.getStrVal("in").c_str(), ios::in);
			if (!inputFile->is_open()) {
				cout <<"Cannot open input file '" <<opts.getStrVal("in") << endl;
				throw 1;
			}
			input = inputFile;
		}

        // set output stream
		if (opts.getStrVal("out").size() == 0) {
			throw 1;
		} else if (opts.getStrVal("out").compare("STDOUT") != 0) {
			outFile = new std::ofstream(opts.getStrVal("out").c_str(), ios::out);
			if (!outFile->is_open()) {
				cout <<"Cannot open output file '" <<opts.getStrVal("out") << endl;
				throw 1;
			}
			out = outFile;
		}

        // read input file to Adjacency-List
        string line;
        while (!inputFile->eof()) {
            getline (*inputFile,line);

            stringstream(line.substr(0,line.find(":"))) >> vertex;
            string connections = line.substr((line.find(":")+1));

            std::stringstream ss(connections);
            while( ss.good() )
            {
                string substr;
                int subint;
                getline( ss, substr, ',' );
                (stringstream(substr)) >> subint;
                neighbours.push_back(subint);
            }
            adjacencyList.insert(pair<int,vertexList>(vertex,neighbours));
            neighbours = {};
        }

        //print input
        printAdjacencyList(adjacencyList);

        // call search here
        time_table_map ttm = DFS(adjacencyList, 1);


        // close files on exit
        out->flush();
        if (opts.getStrVal("in").compare("STDIN") != 0) {
            inputFile->close();
        }
        if (opts.getStrVal("out").compare("STDOUT") != 0) {
            outFile->close();
        }



    } catch (std::exception& ex) {
		(*out) <<"\n\n ERROR : " <<ex.what() <<"\n"<<std::endl;
		return -1;

	} catch (int e) {
	    switch (e) {
	        // throw 1 - input output file error
	        case 1: (*out) <<"Input or Output file could not be opened!" <<std::endl; break;
	    }
		return -1;
    }
}

// Print Acjacency list to cout
void printAdjacencyList(std::map<int,vertexList> adjacencyList)
{
    // print input to cout
    // iterate over adjacencyList
    for (auto elem : adjacencyList) {
        cout << elem.first << ": " << elem.second << endl;
    }
}

// Algorithmus Depth-Fist-Search
time_table_map DFS(std::map<int,vertexList> adjacencyList, int startVertex)
{
    /* PSEUDOCODE (http://en.wikipedia.org/wiki/Depth-first_search)
        1  procedure DFS(G,v):
        label v as explored
        for all edges e in G.incidentEdges(v) do
        if edge e is unexplored then
            w ← G.opposite(v,e)
            if vertex w is unexplored then
                label e as a discovery edge
                    recursively call DFS(G,w)
                else
                    label e as a back edge */


    // initialize


    //add entry to times
    time_table newtime(3,4);
    times.insert(pair<int,time_table>(1,newtime));
    cout << times;
    changeTime(1,5,6);
    cout << times;

    return times;
}

void changeTime(int vertex, int discoverytime, int finishtime)
{
    auto it = times.find(vertex);
    it->second.discoverytime = 2;
    it->second.finishtime = 8;
    //times.erase(it);
    //times.insert(pair<int,time_table>(vertex,(discoverytime,finishtime)));
}
