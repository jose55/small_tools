/* A little C++ Programm implementing depth first search.
2012-08-20, Stefan Hammer <j.4@gmx.at>, GPLv3.*/

#include "OptionParser.hh"
#include "OptionParser.cc"
#include "version.hh"
#include <iostream>
using namespace std;
using namespace biu;


int main(int argc, char ** argv) {

	OptionMap allowedArgs;
	allowedArgs.push_back(COption("text", false, COption::STRING, "input sequence file with given degeneration"));
	allowedArgs.push_back(COption("max", true, COption::INT, "maximal degeneration that is used"));
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
	    std::string text = opts.getStrVal("text");

		return 0;

	} else {
            return -1;
	}
}
