#ifndef PUBLIC_H_
#define PUBLIC_H_

const int MAX_PATH = 260;
const int MAX_COMMAND = 2000;

int AccessFile(char *file_path);
int AccessFile2(char *file_path);
int AccessDirectory(char *directory_path);
int CopyFile(char *source_file_path, char *destination_file_path);
int AppendFile(char *source_file_path_1, char *source_file_path_2);
int AppendFile(char *source_file_path_1, char *source_file_path_2, char *destination_file_path);
int DeleteFile(char *file_path);
int MoveFile(char *source_file_path, char *destination_file_path);
int BackUpFile(char *file_path);
int DeleteBackUpFile(char *file_path);
int CopyDirectory(char *source_directory_path, char *destination_directory_path);
int DeleteDirectory(char *directory_path);
int FileCharCounter(char *file_path);
int FileLineCounter(char *file_path, const int start_line_num);
int FileLineCounter(char *file_path);
char *FilePathSplitter(char *input_file_path, char *output, int work_mode);
char *FilePathParallel(char *input_file_path, char *output, int ref_num, int work_mode);
char *FilePathChangeDirectory(char *input_file_path, char *new_directory_path, char *output);
char *FilePathChangeSuffix(char *input_file_path, char *new_suffix, char *output);
char *DirectoryPathSplitter(char *input_directory_path, char *output, int work_mode);
char *DirectoryPathParallel(char *input_directory_path, char *output, int ref_num, int work_mode);
char FindUnitAfterNumber(char *file_path, char *keyword);
int FileContentModifier(char *file_path, char *keyword, int length_original_string, char stop_search_condition, char *string_to_replace, double number_to_replace, int working_mode);

#endif