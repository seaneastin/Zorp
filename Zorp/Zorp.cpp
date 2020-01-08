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


const int EMPTY = 0;
const int ENEMY = 1;
const int TREASURE = 2;
const int FOOD = 3;
const int ENTRANCE = 4;
const int EXIT = 5;
const int MAX_RANDOM_TYPE = FOOD + 1;

const int MAZE_WIDTH = 10;
const int MAZE_HEIGHT = 6;



const int INDENT_X = 5; //how many spaces to use to indent all text. This can also be used as a tab.
const int ROOM_DESC_Y = 8; //the line to use for our room descriptions. Each type of room will have a description. 
//For example, for the empty room the description
//will be “You are in an empty meadow. There is nothing of interest here.”
const int MOVEMENT_DESC_Y = 9;

const int MAP_Y = 13; //the first line where the map is drawn.


const char* EXTRA_OUTPUT_POS = "\1b[25;6H";

const int PLAYER_INPUT_X = 30; //the character column where the player will type their input. 
const int PLAYER_INPUT_Y = 23; // the line where the player will type their input.


//input commands
const int WEST = 4; //
const int EAST = 6; //
const int NORTH = 8; //
const int SOUTH = 2; //
const int LOOK = 9; //
const int FIGHT = 10; //




bool enableVirtualTerminal()
{
	// Set output mode to handle virtual terminal sequences
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hOut == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	


	DWORD dwMode = 0;
	if (!GetConsoleMode(hOut, &dwMode))
	{
		return false;
	}


	dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	if (!SetConsoleMode(hOut, dwMode))
	{
		return false;
	}
	return true;
}



int initialize(int map[MAZE_HEIGHT][MAZE_WIDTH])
{



	srand(time(nullptr));

	//fill the arrays with random room type
	for (int y = 0; y < MAZE_HEIGHT; y++)
	{
		for (int x = 0; x < MAZE_WIDTH; x++)
		{

			int type = rand() % (MAX_RANDOM_TYPE * 2);
			if (type < MAX_RANDOM_TYPE)
				map[y][x] = type;
			else
				map[y][x] = EMPTY;
		}
	}

	//set the entrance and exit of the maze
	map[0][0] = ENTRANCE;
	map[MAZE_HEIGHT - 1][MAZE_WIDTH - 1] = EXIT;

	return 1;
}

int drawWelcomeMessage()
{


	cout << TITLE << MAGENTA << "Welcome to ZORP!" << RESET_COLOR << endl;
	cout << INDENT << "ZORP is a game of adventure, danger, and low cunning." << endl;
	cout << INDENT << "it is definitely not related to any other text-based adventure game." << endl << endl;


	return 1;
}

int drawRoom(int map[MAZE_HEIGHT][MAZE_WIDTH], int x, int y)
{
	//find the console output position
	int outX = INDENT_X + (6 * x) + 1;
	int outY = MAP_Y + y;

	cout << CSI << outY << ";" << outX << "H";

	switch (map[y][x])
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
	return 1;
}




int drawMap(int map[MAZE_HEIGHT][MAZE_WIDTH])
{
	//reset draw colors
	cout << RESET_COLOR;
	for (int y = 0; y < MAZE_HEIGHT; y++)
	{
		cout << INDENT;
		for (int x = 0; x < MAZE_WIDTH; x++)
		{
			drawRoom(map, x, y);
		}
	}
	return 1;
}

int drawRoomDescription(int roomType)
{
	

	//reset draw colors
	cout << RESET_COLOR;
	//jump to the correct location
	cout << CSI << ROOM_DESC_Y << ";" << 0 << "H";
	//delete and insert 4 lines
	cout << CSI << "4M" << CSI << "4L" << endl;

	//write description of current room

	switch (roomType)
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
	}
	return 1;
}


int drawPlayer(int x, int y)
{
	x = INDENT_X + (6 * x) + 3;
y = MAP_Y + y;

//draw the player's position on the map
//move cursor to map pos and delete character at current position
cout << CSI << y << ";" << x << "H";
cout << MAGENTA << "\x81" << RESET_COLOR;
return 1;
}


int drawValidDirections(int x, int y)
{
	//reset draw colors
	cout << RESET_COLOR;
	// jump to the correct location
	cout << CSI << MOVEMENT_DESC_Y + 1 << ";" << 0 << "H";
	cout << INDENT << "You can see paths leading to the " <<
		((x > 0) ? "west, " : "") <<
		((x < MAZE_WIDTH - 1) ? "east, " : "") <<
		((y > 0) ? "north, " : "") <<
		((y < MAZE_HEIGHT - 1) ? "south, " : "") << endl;

	return 1;
}

int getMovementDirection()
{
	cout << CSI << PLAYER_INPUT_Y << ";" << 0 << "H";
	cout << INDENT << "Where to now?";
	int direction;
	//move cursor to position for player to enter input
	cout << CSI << PLAYER_INPUT_Y << ";" << PLAYER_INPUT_X << "H" << YELLOW;

	//clear the input buffer, ready fro player input
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());

	cin >> direction;
	cout << RESET_COLOR;


	if (cin.fail())
	{
		return 0;
	}

	return direction;

}


int getCommand()
{
	//for now, we can't read commands longer than 50 characters
	char input[50] = "\0";
	// jump to the correct location
	cout << CSI << PLAYER_INPUT_Y << ";" << 0 << "H";
	//clear any existing text
	cout << CSI << "4M";

	cout << INDENT << "Enter a command.";

	//move cursor to position for player to enter input
	cout << CSI << PLAYER_INPUT_Y << ";" << PLAYER_INPUT_X << "H" << YELLOW;


	//clear the input buffer, ready for player input

	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());

	cin >> input;
	cout << RESET_COLOR;


	bool bMove = false;
	while (input)
	{
		if (strcmp(input, "move") == 0)
		{
			bMove = true;
		}
		else if (bMove == true)
		{
			if (strcmp(input, "north") == 0)
				return NORTH;
			if (strcmp(input, "south") == 0)
				return SOUTH;
			if (strcmp(input, "east") == 0)
				return EAST;
			if (strcmp(input, "west") == 0)
				return WEST;
		}
		if (strcmp(input, "look") == 0)
		{
			return LOOK;
		}
		if (strcmp(input, "fight") == 0)
		{
			return FIGHT;
		}

		char next = cin.peek();
		if (next == '\n' || next == EOF)
			break;
		cin >> input;

	}
	return 0;

}

int main()
{

	//create a 2D array
	int rooms[MAZE_HEIGHT][MAZE_WIDTH];


	bool gameOver = false;
	int playerX = 0;
	int playerY = 0;


	int height = 0;
	char firstLetterOfName = 0;
	int avatarHP = 0;


	if (enableVirtualTerminal() == false)
	{
		cout << "The virutal terminal processing mode could not be activated" << endl;
		cout << "Press 'Enter' to exit." << endl;

		cin.get();
		return 0;
	}


	initialize(rooms);
	drawWelcomeMessage();


	//output the map
	drawMap(rooms);








	while (!gameOver)
	{

		drawRoomDescription(rooms[playerY][playerX]);


		drawPlayer(playerX, playerY);

		if (rooms[playerY][playerX] == EXIT)
		{
			gameOver = true;
			continue;
		}

		//list the direction the player can take
		drawValidDirections(playerX, playerY);
		int command = getCommand();


		//before updating the player position, redraw the old room
		// character over the old position

		drawRoom(rooms, playerX, playerY);

		//update the player's position using the input movement data
		switch (command)
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
		case LOOK:
			drawPlayer(playerX, playerY);
			cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You look around, but see nothing worth mentioning" << endl;
			cout << INDENT << "Press 'ENTER' to continue.";
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
		case FIGHT:
			drawPlayer(playerX, playerY);
			cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You could try to fight, but you don't have a weapon" << endl;
			cout << INDENT << "Pres 'ENTER' to continue.";
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			cin.get();
			break;

		default:
			//the direction was not valid
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
