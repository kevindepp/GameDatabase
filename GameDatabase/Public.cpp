/**********************************************************
** Public.cpp
**
** Known Issues:
**
** FindUnitAfterNumber
** -- buffer created by 'new' but not deleted before return
**
** FileLineCounter
** -- '\n' may not work at some time, consider to use 'r'
**********************************************************/

#include <iostream>
using namespace std;
#include <io.h>

#include "Public.h"

int AccessFile(char *file_path) {

	/***********************
	** Check File Existence
	** 0: File Exists
	** 1: File Doesn't Exist
	***********************/

	if (_access(file_path, 00) == -1) {
		return 1;
	}

	return 0;
}

int AccessFile2(char *file_path) {

	/***********************
	** Check File Existence
	** 0: File Exists
	** 1: File Doesn't Exist
	***********************/

	FILE *fp;

	if(fopen_s(&fp, file_path, "r") != 0) {
		return 1;
	}
	fclose(fp);

	return 0;
}

int AccessDirectory(char *directory_path) {

	/****************************
	** Check Directory Existence
	** 0: Directory Exists
	** 1: Directory Doesn't Exist
	****************************/

	if (_access(directory_path, 00) == -1) {
		return 1;
	}
	
	return 0;
}

int CopyFile(char *source_file_path, char *destination_file_path) {

	if (AccessFile(source_file_path) != 0) {
		cout << "Cannot Locate Source File:" << endl;
		return 1;
	}

	char *command = new char [MAX_COMMAND];
	sprintf_s(command, MAX_COMMAND, "%s%s%s%s%s", "copy \"", source_file_path, "\" \"", destination_file_path, "\" > nul");

	system(command);

	delete [] command;

	if (AccessFile(destination_file_path) != 0) {
		cout << "Cannot Locate Destination File:" << endl;
		return 1;
	}

	return 0;
}

int AppendFile(char *source_file_path_1, char *source_file_path_2) {

	if (AccessFile(source_file_path_1) != 0) {
		cout << endl << "Cannot Locate Source File 1:" << endl;
		cout << source_file_path_1 << endl;
		return 1;
	}

	if (AccessFile(source_file_path_2) != 0) {
		cout << endl << "Cannot Locate Source File 2:" << endl;
		cout << source_file_path_2 << endl;
		return 1;
	}

	char *command = new char [MAX_COMMAND];
	sprintf_s(command, MAX_COMMAND, "%s%s%s%s%s%s%s", "copy /b \"", source_file_path_1, "\" + \"", source_file_path_2, "\" \"", source_file_path_1, "\" > nul");

	system(command);

	delete [] command;

	return 0;

}

int AppendFile(char *source_file_path_1, char *source_file_path_2, char *destination_file_path) {

	if (AccessFile(source_file_path_1) != 0) {
		cout << endl << "Cannot Locate Source File 1:" << endl;
		cout << source_file_path_1 << endl;
		return 1;
	}

	if (AccessFile(source_file_path_2) != 0) {
		cout << endl << "Cannot Locate Source File 2:" << endl;
		cout << source_file_path_2 << endl;
		return 1;
	}

	char *command = new char [MAX_COMMAND];
	sprintf_s(command, MAX_COMMAND, "%s%s%s%s%s%s%s", "copy /b \"", source_file_path_1, "\" + \"", source_file_path_2, "\" \"", destination_file_path, "\" > nul");

	system(command);

	delete [] command;

	return 0;
}

int DeleteFile(char *file_path) {

	if (AccessFile(file_path) != 0) {
		cout << endl << "Cannot Locate File:" << endl;
		cout << file_path << endl;
		return 1;
	}

	char *command = new char [MAX_COMMAND];
	sprintf_s(command, MAX_COMMAND, "%s%s%s", "del \"", file_path, "\"");

	system(command);

	delete [] command;

	if (AccessFile(file_path) == 0) {
		cout << endl << "Failed to Delete File:" << endl;
		cout << file_path << endl;
		return 1;
	}

	return 0;
}

int MoveFile(char *source_file_path, char *destination_file_path) {

	if (AccessFile(source_file_path) != 0) {
		cout << endl << "Cannot Locate Source File:" << endl;
		cout << source_file_path << endl;
		return 1;
	}

	char *command = new char [MAX_COMMAND];
	sprintf_s(command, MAX_COMMAND, "%s%s%s%s%s", "move \"", source_file_path, "\" \"", destination_file_path, "\" > nul");

	system(command);

	delete [] command;

	if (AccessFile(destination_file_path) != 0) {
		cout << endl << "Fail to Move File to Destination Path:" << endl;
		cout << destination_file_path << endl;
		return 1;
	}

	if (AccessFile(source_file_path) == 0) {
		cout << endl << "Fail to Delete Source File:" << endl;
		cout << source_file_path << endl;
		return 1;
	}

	return 0;
}

int BackUpFile(char *file_path) {

	if (AccessFile(file_path) != 0) {
		return 1;
	}

	char *backup_file_path = new char [MAX_PATH];
	sprintf_s(backup_file_path, MAX_PATH, "%s%s", file_path, ".bak");

	CopyFile(file_path, backup_file_path);

	if (AccessFile(backup_file_path) != 0) {
		cout << endl << "Fail to Back Up File to Destination Path:" << endl;
		cout << backup_file_path << endl;
		delete [] backup_file_path;
		return 1;
	}

	delete [] backup_file_path;
	
	return 0;
}

int DeleteBackUpFile(char *file_path) {

	char *backup_file_path = new char [MAX_PATH];
	sprintf_s(backup_file_path, MAX_PATH, "%s%s", file_path, ".bak");

	if (AccessFile(backup_file_path) != 0) {
		return 1;
	}

	DeleteFile(backup_file_path);

	if (AccessFile(backup_file_path) == 0) {
		cout << endl << "Fail to Delete Back Up File:" << endl;
		cout << backup_file_path << endl;
		delete [] backup_file_path;
		return 1;
	}

	delete [] backup_file_path;

	return 0;
}

int CopyDirectory(char *source_directory_path, char *destination_directory_path) {

	if (AccessDirectory(source_directory_path) != 0) {
		cout << endl << "Cannot Locate Source Directory:" << endl;
		cout << source_directory_path << endl;
		return 1;
	}

	char *command = new char [MAX_COMMAND];
	sprintf_s(command, MAX_COMMAND, "%s%s%s%s%s", "xcopy \"", source_directory_path, "\" \"", destination_directory_path, "\" /i /q /y /s /e > nul");

	system(command);

	delete [] command;

	if (AccessDirectory(destination_directory_path) != 0) {
		cout << endl << "Fail to Copy Directory to Destination Path:" << endl;
		cout << destination_directory_path << endl;
		return 1;
	}

	return 0;
}

int DeleteDirectory(char *directory_path) {

	if (AccessDirectory(directory_path) != 0) {
		return 1;
	}

	char *command = new char [MAX_COMMAND];
	sprintf_s(command, MAX_COMMAND, "%s%s%s", "rd /S /Q \"", directory_path, "\"");

	system(command);

	delete [] command;

	if (AccessDirectory(directory_path) == 0) {
		cout << endl << "Fail to Delete Directory:" << endl;
		cout << directory_path << endl;
		return 1;
	}

	return 0;
}

int FileCharCounter(char *file_path) {

	if (AccessFile(file_path) != 0) {
		cout << endl << "Fail to Locate File:" << endl;
		cout << file_path << endl;
		return 0;
	}

	int num_char = 0;
	FILE *fp;

	fopen_s(&fp, file_path, "r");
	while(!feof(fp)){
		fgetc(fp);
		num_char++;
	}
	fclose(fp);

	return num_char;
}

int ReadFileToBuffer( char *buffer, int buffer_size, char *file_path) {

	if (AccessFile(file_path) != 0) {
		cout << endl << "Fail to Locate File:" << endl;
		cout << file_path << endl;
		return 0;
	}

	int i = 0;
	FILE *fp;
	fopen_s(&fp, file_path, "r");
	while(!feof(fp)){
		buffer[i] = fgetc(fp);
		i++;
	}
	fclose(fp);

	buffer[i - 1] = '\0';

	return 0;

}

int FileLineCounter(char *file_path, const int start_line_num) {

	if (AccessFile(file_path) != 0) {
		cout << endl << "Fail to Locate File:" << endl;
		cout << file_path << endl;
		return 0;
	}

	int num_line = 0;

	FILE *fp;

	fopen_s(&fp, file_path, "r");

	//Test if File is Empty
	if (fgetc(fp) == EOF) {
		num_line = 0;
		cout << "Empty File Provided:" << endl;
		cout << file_path << endl;
		fclose(fp);
		return 0;
	}

	//Test if First Line Contains Return Only
	fseek(fp, 0, SEEK_SET);
	if (fgetc(fp) == '\n') {
		num_line = 0;
		cout << "Wrong File Format:" << endl;
		cout << file_path << endl;
		fclose(fp);
		return 0;
	}

	//Calculate Number of Newline Characters (\n)
	fseek(fp, 0, SEEK_SET);
	num_line = 1;
	while(!feof(fp)) {
		if (fgetc (fp) == '\n') {
			num_line++;
		}
	}

	//Eliminate Extra Newline Characters (\n)
	fseek(fp, -2L, SEEK_END);
	while(fgetc(fp) == '\n') {
		num_line--;
		fseek(fp, -3L, SEEK_CUR);
	}

	//Eliminate Lines before Starting Line Number
	num_line -= (start_line_num - 1);

	fclose(fp);

	return num_line;
}

int FileLineCounter(char *file_path) {
	return FileLineCounter(file_path, 1);
}

char *FilePathSplitter(char *input_file_path, char* output, int work_mode) {

	/***************************************************
	** Split File Path
	** e.g. Given Path							C:\A.txt
	** 1: File Path Only						C:\
	** 2: File Path and Name without Suffix		C:\A
	** 3: File Name with Suffix					A.txt
	** 4: File Name without Suffix				A
	** 5: File Suffix Only						txt
	** Else: Input File Path					C:\A.txt
	***************************************************/

	if (work_mode == 1)
		strncpy_s(output, MAX_PATH, input_file_path, strlen(input_file_path) - strlen(strrchr(input_file_path, '\\')) + 1);
	else if (work_mode == 2)
		strncpy_s(output, MAX_PATH, input_file_path, strlen(input_file_path) - strlen(strrchr(input_file_path, '.')));
	else if (work_mode == 3)
		strcpy_s(output, MAX_PATH, strrchr(input_file_path, '\\') + 1);
	else if (work_mode == 4)
		strncpy_s(output, MAX_PATH, strrchr(input_file_path, '\\') + 1, strlen(strrchr(input_file_path, '\\') + 1) - strlen(strrchr(input_file_path, '.')));
	else if (work_mode == 5)
		strcpy_s(output, MAX_PATH, strrchr(input_file_path, '.') + 1);
	else
		strcpy_s(output, MAX_PATH, input_file_path);

	return output;
}

char *FilePathParallel(char *input_file_path, char* output, int ref_num, int work_mode) {
	/*****************************************************
	** File Path Parallelization
	** e.g. Given Path and Reference Number: 1	C:\A.txt
	** 1: Parallel File Path with Suffix		C:\A_1.txt
	** 2: Parallel File Path without Suffix		C:\A_1
	** 3: Parallel File Name with Suffix		A_1.txt
	** 4: Parallel File Name without Suffix		A_1
	** Else: Input File Path					C:\A.txt
	*****************************************************/

	char *file_path = new char [MAX_PATH];
	FilePathSplitter(input_file_path, file_path, 1);

	char *file_name = new char [MAX_PATH];
	FilePathSplitter(input_file_path, file_name, 4);

	char *file_suffix = new char [MAX_PATH];
	FilePathSplitter(input_file_path, file_suffix, 5);
	
	if (work_mode == 1)
		sprintf_s(output, MAX_PATH, "%s%s_%d.%s", file_path, file_name, ref_num, file_suffix);
	else if (work_mode == 2)
		sprintf_s(output, MAX_PATH, "%s%s_%d", file_path, file_name, ref_num);
	else if (work_mode == 3)
		sprintf_s(output, MAX_PATH, "%s_%d.%s", file_name, ref_num, file_suffix);
	else if (work_mode == 4)
		sprintf_s(output, MAX_PATH, "%s_%d", file_name, ref_num);
	else
		strcpy_s(output, MAX_PATH, input_file_path);

	delete [] file_path;
	delete [] file_name;
	delete [] file_suffix;

	return output;
}

char *FilePathChangeDirectory(char *input_file_path, char *new_directory_path, char *output) {

	char *file_name = new char [MAX_PATH];
	FilePathSplitter(input_file_path, file_name, 3);

	sprintf_s(output, MAX_PATH, "%s%s", new_directory_path, file_name);

	delete [] file_name;
	
	return output;
}

char *FilePathChangeSuffix(char *input_file_path, char *new_suffix, char *output) {

	char *file_path_no_suffix = new char [MAX_PATH];
	FilePathSplitter(input_file_path, file_path_no_suffix, 2);

	sprintf_s(output, MAX_PATH, "%s.%s", file_path_no_suffix, new_suffix);

	delete [] file_path_no_suffix;

	return output;
}

char *DirectoryPathSplitter(char *input_directory_path, char *output, int work_mode) {
	/***********************************************
	** Split Directory Path
	** e.g. Given Directory Path				C:\A
	** 1: Directory Path Only					C:\
	** 2: Directory Name Only					A
	** Else: Input Directory Path				C:\A
	***********************************************/

	if (work_mode == 1)
		strncpy_s(output, MAX_PATH, input_directory_path, strlen(input_directory_path) - strlen(strrchr(input_directory_path, '\\')) + 1);
	else if (work_mode == 2) 
		strcpy_s(output, MAX_PATH, strrchr(input_directory_path, '\\') + 1);
	else
		strcpy_s(output, MAX_PATH, input_directory_path);

	return output;
}

char *DirectoryPathParallel(char *input_directory_path, char *output, int ref_num, int work_mode) {
	/*****************************************************
	** Directory Path Parallelization
	** e.g. Given Directory and Reference Number: 1	C:\A
	** 1: Parallel Directory Path					C:\A_1
	** 2: Parallel Directory Name					A_1
	** Else: Input Directory Path					C:\A
	*****************************************************/

	char *directory_name = new char [MAX_PATH];
	DirectoryPathSplitter(input_directory_path, directory_name, 2);
//	cout << "directory_name = " << directory_name << endl;


	if (work_mode == 1)
		sprintf_s(output, MAX_PATH, "%s_%d", input_directory_path, ref_num);
	else if (work_mode == 2)
		sprintf_s(output, MAX_PATH, "%s_%d", directory_name, ref_num);
	else
		strcpy_s(output, MAX_PATH, input_directory_path);

	delete [] directory_name;

	return output;
}

char FindUnitAfterNumber(char *file_path, char *keyword) {

	if (AccessFile(file_path) != 0) {
		cout << endl << "Fail to Locate File:" << endl;
		cout << file_path << endl;
		return NULL;
	}
	
	int num_character = 0;
	char output;
	int i;
	FILE *fp;

	//Get Number of Characters of File
	fopen_s(&fp, file_path, "r");
	while (fgetc (fp) != EOF)
		num_character++;

	char *buffer = new char[num_character];

	fseek(fp, 0, SEEK_SET);

	for(i = 0; i < num_character; i++) {
		buffer[i] = fgetc(fp);
	}
	buffer[num_character] = '\0';
	fclose(fp);

	char *buffer_search = strstr(buffer, keyword);

	for(i = (int)strlen(keyword); i < (int)strlen(buffer_search); i++) {
		if(buffer_search[i] >= 65) {
			output = buffer_search[i];
			break;
		}
	}

	return output;
}

int FileContentModifier(char *file_path, char *keyword, int length_original_string, char stop_search_condition, char *string_to_replace, double number_to_replace, int working_mode) {
	//////////////////////
	//String_Modifier
	//1: Replace String
	//2: Replace Number
	//////////////////////
	FILE *fp;
	char ch;
	int i;

	int character_point = 0;
	int num_character_total = 0;
	int num_character_read = 0;
	int num_return_read = 0;
	int num_char_save;

	if (fopen_s(&fp, file_path, "r") != 0) {
		printf("Cannot Open File: %s!\n", file_path);
		return 1;
	}
	else {
		do {
			ch = fgetc (fp);
			num_character_total++;
		} while (ch != EOF);
		num_character_total--;
		fclose (fp);
	}

	fopen_s(&fp, file_path, "r+");
	do{
		ch = fgetc (fp);
		num_character_read ++;
		if (ch == '\n') {
			num_return_read++;
		}
		if(ch == keyword[character_point]) {
			character_point++;
			if(character_point == strlen(keyword)) {
				if (length_original_string == 0) {
					do {
						ch = fgetc (fp);
						length_original_string++;
					} while (ch != stop_search_condition);
					length_original_string--;
				}
				
				num_char_save = num_character_total - num_character_read - length_original_string;

				char *buffer = new char [num_char_save];

				fseek(fp, num_character_read + num_return_read + length_original_string, SEEK_SET);
				for (i = 0; i < num_char_save; i++) {
					buffer[i] = fgetc (fp);
				}

				fseek(fp, num_character_read + num_return_read, SEEK_SET);
				if (working_mode == 1) {
					fprintf_s(fp, "%s", string_to_replace);
/*
					if (length_original_string > int(strlen(string_to_replace))) {
						for (i = 0; i < (length_original_string - int(strlen(string_to_replace)) - int(strlen("\""))); i++) {
							fputc(' ', fp);
						}
					}
*/
				}
				else if (working_mode == 2)
					fprintf(fp, "%lf", number_to_replace);

				for (i = 0; i < num_char_save; i++) {
					fputc(buffer[i], fp);
				}

				delete [] buffer;
				break;
			}
		}
		else
			character_point = 0;
	} while (ch != EOF);
	fclose (fp);

	return 0;
}


