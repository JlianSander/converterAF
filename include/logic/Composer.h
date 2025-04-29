#ifndef COMPOSER_H
#define COMPOSER_H

#include <fstream>

#include "../util/FileSystemInclude.h"
#include "AF.h"

using namespace std;

/// <summary>
/// This class is responsible for composing an abstract argumentation framework as a file.
/// </summary>
class Composer {
public:

	static void write_query(fs::__cxx11::path dirPath, uint32_t query, fs::__cxx11::directory_entry af_file, string query_file_extension);

	static void write_framework(fs::__cxx11::path dirPath, AF framework, fs::__cxx11::directory_entry original_instance_file);
};
#endif
