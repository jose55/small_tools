#ifndef VERSION_HH
#define VERSION_HH

#include <iostream>

void giveVersion()
{
    std::string PACKAGE_NAME = "Depth-First-Search";
    std::string PACKAGE_VERSION = "0.1";
    std::string PACKAGE_URL = "http://www.tbi.univie.ac.at";

	std::cout	<<"\n " <<PACKAGE_NAME <<" version " <<PACKAGE_VERSION
				<<"\n"
				<<"\n " <<PACKAGE_URL
				<<"\n"
				<<std::endl;
}

#endif /*VERSION_HH*/
