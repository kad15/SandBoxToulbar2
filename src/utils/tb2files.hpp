/** \file tb2wcsp.hpp
 *  \brief General purpose class to play with files
 *
 *
 *  Created on: 24 mai 2019
 *      Author: abeldjilali
 */

#ifndef SRC_UTILS_TB2FILES_HPP_
#define SRC_UTILS_TB2FILES_HPP_
#include <string>
#include <fstream>
//#include "toulbar2lib.hpp"
//#include "utils/tb2store.hpp"

class Tb2Files {





public:
static long nbProcess(const std::string nbProcessFic, const int nbCores, const int nbProcPerCore);
static void write_file(const std::string fileName , const std::string textToWrite);
static void read_file(const std::string );

	Tb2Files();
	virtual ~Tb2Files();
};

#endif /* SRC_UTILS_TB2FILES_HPP_ */
