#ifndef MAIN_H
#define MAIN_H

#include <getopt.h>
#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>

#include "../include/util/FileSystemInclude.h"

#include "../include/logic/AF.h"
#include "../include/logic/Composer.h"
#include "../include/logic/Enums.h"
#include "../include/logic/Parser.h"


using namespace std;

/// <summary>
/// Name of the program
/// </summary>
constexpr auto PROGRAM_NAME = "ConverterAF";
constexpr auto VERSIONNUMBER = "1.0";

/// <summary>
/// Flags used for internal processing.
/// </summary>
static int version_flag = 0;
static int usage_flag = 0;
static int formats_flag = 0;

/// <summary>
/// Different options that can be added to a execution call of this application.
/// </summary>
const struct option longopts[] =
{
	{"help", no_argument, &usage_flag, 1},
	{"version", no_argument, &version_flag, 1},
	{"formats", no_argument, &formats_flag, 1},
	{"d", required_argument, 0, 'd'},
	{"q", required_argument, 0, 'q'},
	{"s", required_argument, 0, 's'},
	{0}
};

/// <summary>
/// This method is used to start the program.
/// </summary>
/// <param name="argc">Number of arguments with which the program got started.</param>
/// <param name="argv">Array of strings, containing the different starting arguments of this progam.</param>
/// <returns>0 iff the program exited without error. 1 otherwise.</returns>
int main(int argc, char **argv);

#endif