#include <iostream>
using namespace std;

#include "Public.h"

int main(int argc, char **argv) {

	FILE *fp;
	
	char *setup_file_name = "Setup.ini";
	if (AccessFile(setup_file_name) != 0) {
		cout << "Fail to Load Setup File:" << endl << setup_file_name << endl;
		return 1;
	}

	char *xbox_record_file_path = new char [MAX_PATH];


	
	fopen_s(&fp, setup_file_name, "r");
	fscanf_s(fp, "%s", xbox_record_file_path, MAX_PATH);
	fclose(fp);

	cout << "xbox_record_file_path = " << xbox_record_file_path << endl;
	if (AccessFile(xbox_record_file_path) != 0) {
		cout << "Fail to Locate Xbox Record File:" << xbox_record_file_path << endl;
		return 1;
	}



	cout << "GameDatabase Successfully Exited!" << endl;

	return 0;
}