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
//colors 
const char* YELLOW = "\x1b[93m"; //sets the text color to yellow.
const char* MAGENTA = "\x1b[95m"; //sets the text color to magenta.
const char* RESET_COLOR = "\x1b[0m"; //resets the text colour to the default color.
const char* RED = "\x1b[91m"; //sets the text color to Red
const char* BLUE = "\x1b[94m"; //sets the text color to blue
const char* WHITE = "\x1b[97m"; //sets the text color to white
const char* GREEN = "\x1b[92m"; //sets the text color to Green
const char* CYAN = "\x1b[96m"; //sets the text color to cyan


const char* SAVE_CURSOR_POS = "\x1b[s"; //save’s the cursor’s current position to memory
const char* RESTORE_CURSOR_POS = "\x1b[u"; //set the cursor to the last saved position.



int main()
{
	bool gameOver = false;
	int playerX = 0;
	int playerY = 0;
	const int EMPTY = 0;
	const int ENEMY = 1;
	const int TREASURE = 2;
	const int FOOD = 3;
	const int ENTRANCE = 4;
	const int EXIT = 5;
	const int MAX_RANDOM_TYPE = FOOD + 1;

	const int MAZE_WIDTH = 10;
	const int MAZE_HEIGHT = 6;

	int height = 0;
	char firstLetterOfName = 0;
	int avatarHP = 0;


	//create a 2D array
	int rooms[MAZE_HEIGHT][MAZE_WIDTH];


	const int INDENT_X = 5; //how many spaces to use to indent all text. This can also be used as a tab.
	const int ROOM_DESC_Y = 8; //the line to use for our room descriptions. Each type of room will have a description. 
	//For example, for the empty room the description
	//will be “You are in an empty meadow. There is nothing of interest here.”
	const int MAP_Y = 13; //the first line where the map is drawn.
	const int PLAYER_INPUT_X = 5; //the character column where the player will type their input. 
	const int PLAYER_INPUT_Y = 8; // the line where the player will type their input.

	const int WEST = 4; //
	const int EAST = 6; //
	const int NORTH = 8; //
	const int SOUTH = 2; //

	// Set output mode to handle virtual terminal sequences
	DWORD dwMode = 0;
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleMode(hOut, &dwMode);
	dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	SetConsoleMode(hOut, dwMode);






	srand(time(nullptr));

	//fill the arrays with random room type
	for (int y = 0; y < MAZE_HEIGHT; y++)
	{
		for (int x = 0; x < MAZE_WIDTH; x++)
		{

			int type = rand() % (MAX_RANDOM_TYPE * 2);
			if (type < MAX_RANDOM_TYPE)
				rooms[y][x] = type;
			else
				rooms[y][x] = EMPTY;
		}
	}

	//set the entrance and exit of the maze
	rooms[0][0] = ENTRANCE;
	rooms[MAZE_HEIGHT - 1][MAZE_WIDTH - 1] = EXIT;



	cout << TITLE << MAGENTA <<"Welcome to ZORP!" << RESET_COLOR <<endl;
	cout << INDENT << "ZORP is a game of adventure, danger, and low cunning." << endl;
	cout << INDENT << "it is definitely not related to any other text-based adventure game." << endl << endl;


	//save cursor position
	cout << SAVE_CURSOR_POS;

	// output the map

	cout << CSI << MAP_Y << ";" << 0 << "H";
	for (int y = 0; y < MAZE_HEIGHT; y++)
	{
		cout << INDENT;
		for (int x = 0; x < MAZE_WIDTH; x++)
		{
			switch (rooms[y][x])
			{
			case EMPTY:
				std::cout << "[ " << GREEN << "\xb0" << RESET_COLOR << " ] ";
				break;
			case ENEMY:
				std::cout << "[ " << RED << "\x94" << RESET_COLOR << " ] ";
				break;
			case TREASURE:
				std::cout << "[ " << YELLOW << "$" << RESET_COLOR << " ] ";
				break;
			case FOOD:
				std::cout << "[ " << CYAN << "\xcf" << RESET_COLOR << " ] ";
				break;
			case ENTRANCE:
				std::cout << "[ " << WHITE << "\x9d" << RESET_COLOR << " ] ";
				break;
			case EXIT:
				std::cout << "[ " << WHITE << "\xFE" << RESET_COLOR << " ] ";
				break;
			}
			

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

	

	if (firstLetterOfName != 0)
	{
		avatarHP = (float)height / (firstLetterOfName * 0.02f);
	}
	else
	{
		avatarHP = 0;
	}
	

	cout << INDENT << "Using a complex deterministic algorithm, it has been calculated that you have " << avatarHP << " hit point(s)." << std::endl;
	cout << endl << INDENT << "Press 'Enter' to continue";
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	cin.get();

	while (!gameOver)
	{
		//prepare screen for output
		//move curosr to start of the 1st Q, then up 1, delete and insert 4 lines

		cout << RESTORE_CURSOR_POS << CSI << "A" << CSI << "4M" << CSI << "4L" << endl;
		
		//write description of current room

		switch (rooms[playerY][playerX])
		{
		case EMPTY:
			cout << INDENT << "You are in an empty meadow. There is nothing of note here." << endl;
			break;
		case ENEMY:
			cout << INDENT << "BEWARE. An enemy is approaching." << endl;
			break;
		case TREASURE:
			cout << INDENT << "Your journey has been rewardewd. You have found some treasure" << endl;
			break;
		case FOOD:
			cout << INDENT << "At last! You collect some food to sustain you on your journey." << endl;
			break;
		case ENTRANCE:
			cout << INDENT << "The entrance you used to enter this maze is blocked. There is no going back" << endl;
			break;
		case EXIT:
			cout << INDENT << "Despite all odds, you made it to the exit. Congratulations." << endl;
			gameOver = true;
			continue;
		}

		cout << INDENT << "You can see paths leading to the " <<
			((playerX > 0) ? "west, " : "") <<
			((playerX < MAZE_WIDTH - 1) ? "east, " : "") <<
			((playerY > 0) ? "north, " : "") <<
			((playerY < MAZE_HEIGHT - 1) ? "south, " : "") << endl;

		cout << INDENT << "Where to now?";

		int x = INDENT_X + (6 * playerX) + 3;
		int y = MAP_Y + playerY;

		// draw the plaeyr's position on the map
		// move cursor to map pos and delete character at current position

		cout << CSI << y << ";" << x << "H";
		cout << MAGENTA << "\x81";

		// move cursor to position for player to enter input
		cout << CSI << PLAYER_INPUT_Y << ";" << PLAYER_INPUT_X << "H" << YELLOW;

		//clear the input buffer, ready for player input
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());

		int direction = 0;

		cin >> direction;

		cout << RESET_COLOR;

		if (cin.fail())
			continue;


		//before updating the player position, redraw the old room character over
		// the old position
		cout << CSI << y << ";" << x << "H";

		switch (rooms[playerY][playerX])
		{
		case EMPTY:
			cout << GREEN << "\xb0" << RESET_COLOR;
			break;
		case ENEMY:
			std::cout << RED << "\x94" << RESET_COLOR;
			break;
		case TREASURE:
			std::cout <<YELLOW << "$" << RESET_COLOR;
			break;
		case FOOD:
			std::cout<< CYAN << "\xcf" << RESET_COLOR;
			break;
		case ENTRANCE:
			std::cout << WHITE << "\x9d" << RESET_COLOR;
			break;
		case EXIT:
			std::cout << WHITE << "\xFE" << RESET_COLOR;
			break;
		}

		switch (direction)
		{
		case EAST:
			if (playerX < MAZE_WIDTH - 1)
				playerX++;
			break;
		case WEST:
			if (playerX > 0)
				playerX--;
			break;
		case SOUTH:
			if (playerY < MAZE_HEIGHT - 1)
				playerY++;
			break;
		case NORTH:
			if (playerY > 0)
				playerY--;
			break;

		default:
			//do nothing, go back to the top of the loop and ask again
			break;
		}

	}



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
