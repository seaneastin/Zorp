// Zorp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <windows.h>
#include <random>
#include <time.h>


using namespace std;


const char* ESC = "\x1b";  //put what this does sometime
const char* CSI = "\x1b["; //– this acronym stands for Control Sequence Introducer. 
//This character sequence is at the start of every command we’ll pass to the console. 
//It’s defined here for situations where we can’t use a pre-defined command. 
const char* TITLE = "\x1b[5;20H"; // this command moves our cursor to the x,y coordinate (20, 5)
const char* INDENT = "\x1b[5C"; //moves the cursor right by 5 characters
const char* YELLOW = "\x1b[93m"; //sets the text colour to yellow.
const char* MAGENTA = "\x1b[95m"; //sets the text colour to magenta.
const char* RESET_COLOR = "\x1b[0m"; //resets the text colour to the default colour.
const char* SAVE_CURSOR_POS = "\x1b[s"; //save’s the cursor’s current position to memory
const char* RESTORE_CURSOR_POS = "\x1b[u"; //set the cursor to the last saved position.

int main()
{
	const int EMPTY = 0;
	const int ENEMY = 1;
	const int Treasure = 2;
	const int FOOD = 3;
	const int ENTRANCE = 4;
	const int EXIT = 5;
	const int MAX_RANDOM_TYPE = FOOD + 1;

	const int MAZE_WIDTH = 10;
	const int MAZE_HEIGHT = 6;

	//create a 2D array
	int rooms[MAZE_HEIGHT][MAZE_WIDTH];

	srand(time(nullptr));

	//fill the arrays with random room type
	for (int y = 0; y < MAZE_HEIGHT; y++)
	{
		for (int x = 0; x < MAZE_WIDTH; x++)
		{
			rooms[y][x] = rand() % MAX_RANDOM_TYPE;
		}
	}

	//set the entrance and exit of the maze
	rooms[0][0] = ENTRANCE;
	rooms[MAZE_HEIGHT - 1][MAZE_WIDTH - 1] = EXIT;


	// Set output mode to handle virtual terminal sequences
	DWORD dwMode = 0;
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleMode(hOut, &dwMode);
	dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	SetConsoleMode(hOut, dwMode);
	int height = 0;
	char firstLetterOfName = 0;
	int avatarHP = 0;
	cout << TITLE << MAGENTA <<"Welcome to ZORP!" << RESET_COLOR <<endl;
	cout << INDENT << "ZORP is a game of adventure, danger, and low cunning." << endl;
	cout << INDENT << "it is definitely not related to any other text-based adventure game." << endl << endl;
	cout << INDENT << "First, some questions..." << endl;


	//save cursor position
	cout << SAVE_CURSOR_POS;

	// output the map
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	for (int y = 0; y < MAZE_HEIGHT; y++)
	{
		cout << INDENT;
		for (int x = 0; x < MAZE_WIDTH; x++)
		{
			cout << "[ " << rooms[y][x] << " ] ";

		}
		cout << endl;
	}


	//move the cursor back to the top of the map
	cout << RESTORE_CURSOR_POS;
	cout << INDENT <<"How tall are you, in centimeters?" << INDENT << YELLOW;
	cin >> height;
	if (std::cin.fail())
	{
		cout << INDENT << "You have failed the first challenge are are eaten by a grue.";
	}
	else
	{
		cout << INDENT << "You entered " << height;
	}

	//clear input buffer
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	cin.get();
	//move the cursor to the start of the 1st question
	cout << RESTORE_CURSOR_POS;
	//delete the next 3 lines of text
	cout << CSI << "3M";
	//inster 3 lines (so lines stay in the same place
	cout << CSI << "3L";

	cout << INDENT << "What is the first letter of your name? " << INDENT << YELLOW;


	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	cin >> firstLetterOfName;
	cout << RESET_COLOR << endl;

	if (cin.fail() || !isalpha(firstLetterOfName))
	{
		cout <<  INDENT <<"You have failed the second challenge and are eaten by a grue.";
	}
	else
	{
		cout << INDENT <<"You entered " << firstLetterOfName;
	}

	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	cin.get();


	// move the curosr to the start of the 1st question, then up 1,
	// then delete and inster 4 lines
	cout << RESTORE_CURSOR_POS << CSI << "A" << CSI << "4M" << CSI << "4L";

	//move the curosr to the start of the 1st question

	cout << RESTORE_CURSOR_POS;
	cout << CSI << "A"; //cursor up 1
	cout << CSI << "4M"; //DELETE THE NEXT 4 LINES OF TEXT

	if (firstLetterOfName != 0)
	{
		avatarHP = (float)height / (firstLetterOfName * 0.02f);
	}
	else
	{
		avatarHP = 0;
	}
	

	cout << INDENT << "Using a complex deterministic algorithm, it has been calculated that you have " << avatarHP << " hit point(s)." << std::endl;


	cout <<  endl << INDENT << "Press 'Enter' to exit the program.";

	cin.clear();
	cin.ignore(cin.rdbuf() -> in_avail());
	cin.get();
	return 1;

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
