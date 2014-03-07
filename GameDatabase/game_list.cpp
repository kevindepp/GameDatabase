#include <iostream>
using namespace std;

#include "game_list.h"
#include "Public.h"

int UpdateGameList(char *game_list_file_path) {

	int i;

	const int Length_Game_ID = 10;

	int num_game;

	num_game = FileLineCounter(game_list_file_path);

	cout << "Number of Games on Record: " << num_game << endl;

	//Read Games from Record
	char **game_id = new char *[num_game];
	char **game_title_eng = new char *[num_game];
	for (i = 0; i < num_game; i++) {
		game_id[i] = new char [10];
		game_title_eng[i] = new char [100];
	}



	return 0;
}


