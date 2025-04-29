#ifndef PARSER_ICCMA
#define PARSER_ICCMA

#include <cstdint>
#include <iostream>			
#include <fstream>			
#include <algorithm>
#include <sstream>
#include <unordered_map>

#include <omp.h>

#include "AF.h"

extern "C" {
	#include "../util/MemoryWatchDog.h"
}

using namespace std;

/// <summary>
/// This class is responsible for parsing a file into a data type representing an abstract argumentation framework.
/// </summary>
class Parser {
public:

	/// <summary>
	/// This method parses an abstract argumentation framework from a file, which complies to the ICCMA'23 format, located 
	/// at the specified path.
	/// </summary>
	/// <param name="file">String that describes the location of the file to open.</param>
	/// <param name="query"> String that describes the query argument.</param>
	/// <param name="query_out">[Output] Output-variable of the parsed number of the query argument.</param>
	/// <returns> Object of the framework to create.<\returns>
	static AF parse_af_i23(string file, string query, uint32_t &query_out);

	/// <summary>
	/// This method parses an abstract argumentation framework from a file, which complies to the tgf format, located 
	/// at the specified path.
	/// </summary>
	/// <param name="file">String that describes the location of the file to open.</param>
	/// <param name="query"> String that describes the query argument.</param>
	/// <param name="query_out">[Output] Output-variable of the parsed number of the query argument.</param>
	/// <returns> Object of the framework to create.<\returns>
	static AF parse_af_tgf(string file, string query, uint32_t &query_out);
};

#endif