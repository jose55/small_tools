/* A little C++ Programm implementing depth first search.
2012-08-20, Stefan Hammer <j.4@gmx.at>, GPLv3.*/

#include "OptionParser.hh"
#include "OptionParser.cc"
#include "version.hh"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
using namespace biu;


int main(int argc, char ** argv) {

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
        //maybe take variables from options
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
				cout <<"Cannot open input file '" <<opts.getStrVal("in") <<"'\n";
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
				cout <<"Cannot open output file '" <<opts.getStrVal("out") <<"'\n";
				throw 1;
			}
			out = outFile;
		}

        // do calculations here
        string line;
        while (!inputFile->eof())
        {
            getline (*inputFile,line);
            (*out) <<line <<std::endl;
        }


        // close files on exit
        out->flush();
        inputFile->close();
        outFile->close();


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
