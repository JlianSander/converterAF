#include "../include/Main.h"

using namespace std;

/*===========================================================================================================================================================*/
/*===========================================================================================================================================================*/

void static print_usage()
{
	cout << "Usage: " << PROGRAM_NAME << " -d <directory> -q <query-file-extension> -s <save_to> \n\n";
	cout << "  <directory>    container of  argumentation frameworks" << endl;
	cout << "  <query-file-extension>    extension of the query argument; e.g. '.arg'" << endl;
	cout << "  <save_to>    location to save the converted files" << endl;
	cout << "Options:" << endl;
	cout << "  --help      Displays this help message." << endl;
	cout << "  --version   Prints version and author information." << endl;
	cout << "  --formats   Prints available file formats." << endl;
}

/*===========================================================================================================================================================*/
/*===========================================================================================================================================================*/

void static print_version()
{
	cout << PROGRAM_NAME << " (version "<< VERSIONNUMBER <<")\n"
		<< "Lars Bengel, University of Hagen <lars.bengel@fernuni-hagen.de>\n" 
		<< "Julian Sander, University of Hagen <julian.sander@fernuni-hagen.de>\n"
		<< "Matthias Thimm, University of Hagen <matthias.thimm@fernuni-hagen.de>\n";
}

/*===========================================================================================================================================================*/
/*===========================================================================================================================================================*/

void static print_formats()
{
	cout << "{[tgf -> i23]}" << endl;
}

/*===========================================================================================================================================================*/
/*===========================================================================================================================================================*/

static string read_query(fs::directory_entry &file, string query_file_extension)
{
	fs::path query_file{ file.path() }, extension_query{ query_file_extension };
	query_file.replace_extension(query_file_extension);
	ifstream input;
	input.open(query_file);

	if (!input.good()) {
		cerr << "Cannot open query file at: " << query_file << endl;
		exit(1);
	}

	string line, query;

	getline(input, line);
	std::istringstream iss(line);
	iss >> query;

	return query;
}

/*===========================================================================================================================================================*/
/*===========================================================================================================================================================*/

int main(int argc, char **argv)
{
	// read command arguments
	if (argc == 1) {
		print_version();
		return 0;
	}

	int option_index = 0;
	int opt = 0;
	string dir, output_dir, query_file_extension;

	while ((opt = getopt_long_only(argc, argv, "", longopts, &option_index)) != -1) {
		switch (opt) {
		case 0:
			break;
		case 'd':
			dir = optarg;
			break;
		case 's':
			output_dir = optarg;
			break;
		case 'q':
			query_file_extension = optarg;
			break;
		default:
			return 1;
		}
	}

	if (version_flag) {
		print_version();
		return 0;
	}

	if (usage_flag) {
		print_usage();
		return 0;
	}

	if (formats_flag) {
		print_formats();
		return 0;
	}

	if (dir.empty()) {
		cerr << argv[0] << ": Input directory must be specified via -d flag\n";
		return 1;
	}

	if (query_file_extension.empty()) {
		cerr << argv[0] << ": The extension of the query argument must be specified via -q flag e.g. '.arg'" << endl;
		return 1;
	}

	if (output_dir.empty()) {
		cerr << argv[0] << ": Output directory must be specified via -s flag\n";
		return 1;
	}
	fs::__cxx11::path output_dir_path = fs::__cxx11::path(output_dir);

	cout << "Process files in " << dir << endl;

	//prepare iterating through directory
	typedef vector<fs::directory_entry> vec;
	vec v;
	

	copy(fs::directory_iterator(dir), fs::directory_iterator(), back_inserter(v));
	sort(v.begin(), v.end());				// sort, since directory iteration is not ordered on some file systems
	int num_files = v.size() / 2;

	//iterate through files
	int idx_file = 0;
	for (vec::const_iterator it(v.begin()), it_end(v.end()); it != it_end; ++it)
	{
		fs::directory_entry file = *it;
		// skip argument files
		string extension = file.path().extension();
		string arg_extension = fs::path("abc" + query_file_extension).extension();
		if (file.path().extension() == fs::path("abc" + query_file_extension).extension())
		{
			continue;
		}

		int percentage = (idx_file * 100) / num_files;
		cout << "[" << percentage << "%] Processing " << file.path().filename() << endl;
		idx_file++;

		// parse the framework
		AF framework;
		string file_format = file.path().extension();
		uint32_t query_argument;

		// parse framework and query argument
		switch (Enums::string_to_format(file_format)) {
			case I23:
				framework = Parser::parse_af_i23(file.path(), read_query(file, query_file_extension), query_argument);
				break;
			case TGF:
				framework = Parser::parse_af_tgf(file.path(), read_query(file, query_file_extension), query_argument);
				break;
			default:
				cerr << file_format << ": Unsupported file format\n";
				return 1;
		};

		if (query_argument == 0){
			cout << "ERROR query argument could not be parsed in file: " << file.path() << endl;
			exit(1);
		}

		// save query argument in file
		Composer::write_query(output_dir_path, query_argument, file ,query_file_extension);
		Composer::write_framework(output_dir_path, framework, file);
	}

	cout << "Saved results in " << output_dir << endl;

	return 0;
}