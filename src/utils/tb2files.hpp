/*
 * tb2files.hpp
 *
 *  Created on: 24 mai 2019
 *      Author: abeldjilali
 */

#ifndef SRC_UTILS_TB2FILES_HPP_
#define SRC_UTILS_TB2FILES_HPP_
#include <string>
#include <fstream>
class tb2files {





public:
static void write_file(const std::string , const std::string );
static void read_file(const std::string );
	tb2files();
	virtual ~tb2files();
};

#endif /* SRC_UTILS_TB2FILES_HPP_ */
