#include "../../include/logic/Composer.h"

using namespace std;

/*===========================================================================================================================================================*/
/*===========================================================================================================================================================*/

void Composer::write_query(fs::__cxx11::path dirPath, uint32_t query, fs::__cxx11::directory_entry af_file, string query_file_extension)
{
	string query_filename = fs::__cxx11::path(af_file.path().filename()).replace_extension(query_file_extension);
	fs::__cxx11::path query_file_path = fs::__cxx11::path(dirPath).append(query_filename);
	std::ofstream query_file_ofs(query_file_path);
	query_file_ofs.clear();
	query_file_ofs << query;
	query_file_ofs.close();
}

/*===========================================================================================================================================================*/
/*===========================================================================================================================================================*/

void Composer::write_framework(fs::__cxx11::path dirPath, AF framework, fs::__cxx11::directory_entry original_instance_file) {

	string new_filename = fs::__cxx11::path(original_instance_file.path().filename()).replace_extension("i23");
	fs::__cxx11::path new_file_path = fs::__cxx11::path(dirPath).append(new_filename);
	std::ofstream file_ofs(new_file_path);
	file_ofs.clear();
	file_ofs << "p af " << framework.num_args << endl;

	for (const pair<uint32_t, uint32_t> &attack : framework.attacks) {
		int32_t attacker = attack.first;
		int32_t victim = attack.second;
		file_ofs << attacker << " " << victim << endl;
	}

	file_ofs.close();
	return;
}