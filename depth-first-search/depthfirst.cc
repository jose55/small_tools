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

//variable definitions
typedef std::vector<int> vertexList;

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

// discovered edges
struct edge {
    edge(int a, int b = 0, string t = "") : parent(a), daughter(b), type(t) {
    }
    int parent;
    int daughter;
    string type;
};
// vector of edges
typedef vector<edge> edge_vector;


// overload << operator to be able to print time_table, vertexLists, edge and edge_vector
std::ostream& operator<< (std::ostream& os, time_table& t) {
    os << "(" << t.discoverytime << "," << t.finishtime << ")";
    return os;
}

std::ostream& operator<< (std::ostream& os, vertexList& vL) {
    for(auto pos =vL.begin(); pos != vL.end(); ++pos) {
        const auto& item = *pos;
        os << item;
        if(pos != vL.end()-1) {
            os << ",";
        }
    }
    return os;
}

std::ostream& operator<< (std::ostream& os, edge& e) {
    os << e.type << ": " << e.parent << " - " << e.daughter;
    return os;
}

std::ostream& operator<< (std::ostream& os, edge_vector& eV) {
    for(auto item : eV) {
        os << item << endl;
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
void DFS(int startVertex);
int getStartVertex();
void initializeTimes();
void setDiscovered(int vertex);
void setFinished(int vertex);
bool isDiscovered(int vertex);
bool isFinished(int vertex);
int getDiscoveryTime(int vertex);
int getFinishTime(int vertex);
vertexList getNeighbours (int vertex);
int getVertexColour(int vertex);

//global variables
// map of time_tables of all vertices
time_table_map times;
//adjacency List (vertex numver, list of neighbouring verteces)
std::map<int,vertexList> adjacencyList;
//Time of search
int searchtime;
// vector of edges
edge_vector edges;


int main(int argc, char ** argv) {

    // local varaibles
    //Vertex Number
    int vertex;
    //list of neighbouring verteces
    vertexList neighbours;

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
        cout << "You have inserted following graph:" <<endl;
        printAdjacencyList(adjacencyList);

        // fill time_table times with vertex names and zeros
        initializeTimes();
        cout << "Initialized times with zero:" << endl << times;

        // call search algorithm here
        searchtime = 1;
        while (int startVertex = getStartVertex() != 0) {
            cout << "--> Starting a new search at vertex: " << startVertex << endl;
            DFS(startVertex);
        }
        cout << endl << "-- Finished depth first search! --" << endl;
        (*out) << "Final times are:" << endl << times << endl;
        (*out) << "Detected Edges are:" << endl;
        (*out) << edges << endl;


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
	        case 2: (*out) <<"Trying to overwrite Discoverytime or Finishtime" <<std::endl; break;
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
void DFS(int startVertex)
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
    setDiscovered(startVertex);

    vertexList neighbours = getNeighbours(startVertex);
    cout << "Neighbours of vertex "
	 << startVertex
	 << " are: "
	 << neighbours
	 << endl;

    for (int vertex : neighbours)
    {
        // vertex is white
        if (getVertexColour(vertex) == 0) {
            // add tree edge to edges vector
            edge myedge(startVertex,vertex,"tree edge");
            edges.push_back(myedge);
            cout << "added " << myedge << endl;
            // show times table
            cout << "current times:" << endl << times;
            // recursively call DFS
            DFS(vertex);
        }
        // vertex is gray
        else if (getVertexColour(vertex) == 1) {
            cout << "vertex " << vertex << " is gray -> ignore." << endl;
            // add tree edge to edges vector
            bool edgeexists = false;
            for (auto elem : edges)
            {
                if ((elem.daughter == vertex && elem.parent == startVertex) || (elem.parent == vertex && elem.daughter == startVertex)) {
                    edgeexists = true;
                }
            }
            if (!edgeexists) {
                edge myedge(startVertex,vertex,"back edge");
                edges.push_back(myedge);
                cout << "added " << myedge << endl;
            }
        }
    }
    setFinished(startVertex);
}

int getStartVertex()
{
    //get an unexplored vertex to start.
    for (auto elem : adjacencyList) {
        auto it = times.find(elem.first);
        if (it->second.discoverytime == 0)
            return elem.first;
    }
    return 0;
}

void initializeTimes()
{
    // initialize timetable
    for (auto elem : adjacencyList) {
        time_table zero(0,0);
        times.insert(pair<int,time_table>(elem.first,zero));
    }
}

void setDiscovered(int vertex)
{
    auto it = times.find(vertex);

    if (it->second.discoverytime == 0) {
        it->second.discoverytime = searchtime;
        cout << searchtime << ") discovered vertex: " << vertex << endl;
        searchtime++;
    }
    else {
      cout << searchtime << ") vertex: " << vertex << endl;
      throw 2;
    }
}

void setFinished(int vertex)
{
    auto it = times.find(vertex);

    if (it->second.finishtime == 0 && it->second.discoverytime > 0) {
        it->second.finishtime = searchtime;
        cout << searchtime << ") finished vertex: " << vertex << endl;
        searchtime++;
    }
    else {
      cout << searchtime << ") vertex: " << vertex << endl;
      throw 2;
    }
}

bool isDiscovered(int vertex)
{
  auto it = times.find(vertex);
  if (it->second.discoverytime > 0)
    return true;
  else
    return false;
}

bool isFinished(int vertex)
{
  auto it = times.find(vertex);
  if (it->second.finishtime > 0)
    return true;
  else
    return false;
}

int getDiscoveryTime(int vertex)
{
    auto it = times.find(vertex);
    return it->second.discoverytime;
}

int getFinishTime(int vertex)
{
    auto it = times.find(vertex);
    return it->second.finishtime;
}

vertexList getNeighbours (int vertex)
{
    auto it = adjacencyList.find(vertex);
    return it->second;
}

int getVertexColour(int vertex)
{
    auto it = times.find(vertex);
    // vertex is white
    if (it->second.discoverytime == 0 && it->second.finishtime == 0)
        return 0;
    // vertex is grey
    else if (it->second.discoverytime > 0 && it->second.finishtime == 0)
        return 1;
    // vertex is black
    else if (it->second.discoverytime > 0 && it->second.finishtime > 0)
        return 2;
}

