// Zorp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <windows.h>

int main()
{
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
	// Set output mode to handle virtual terminal sequences
	DWORD dwMode = 0;
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleMode(hOut, &dwMode);
	dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	SetConsoleMode(hOut, dwMode);
	int height = 0;
	char firstLetterOfName = 0;
	int avatarHP = 0;
	std::cout << TITLE << MAGENTA <<"Welcome to ZORP!" << RESET_COLOR <<std::endl;
	std::cout << INDENT << "ZORP is a game of adventure, danger, and low cunning." << std::endl;
	std::cout << INDENT << "it is definitely not related to any other text-based adventure game." << std::endl << std::endl;
	std::cout << INDENT << "First, some questions..." << std::endl;


	//save cursor position
	std::cout << SAVE_CURSOR_POS;

	std::cout << INDENT <<"How tall are you, in centimeters?" << std::endl;
	std::cin >> height;
	if (std::cin.fail())
	{
		std::cout << INDENT << "You have failed the first challenge are are eaten by a grue." << std::endl;
	}
	else
	{
		std::cout << INDENT << "You entered " << height << std::endl;
	}

	//clear input buffer
	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	std::cin.get();
	//move the cursor to the start of the 1st question
	std::cout << RESTORE_CURSOR_POS;
	//delete the next 4 lines of text
	std::cout << CSI << "4M";


	std::cout << INDENT << "What is the first letter of your name? " << INDENT << YELLOW;

	std::cin >> firstLetterOfName;
	std::cout << RESET_COLOR << std::endl;

	if (std::cin.fail() || !isalpha(firstLetterOfName))
	{
		std::cout <<  INDENT <<"You have failed the second challenge and are eaten by a grue." << std::endl;
	}
	else
	{
		std::cout << INDENT <<"You entered " << firstLetterOfName << std::endl;
	}

	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	std::cin.get();


	//move the curosr to the start of the 1st question

	std::cout << RESTORE_CURSOR_POS;
	std::cout << CSI << "A"; //cursor up 1
	std::cout << CSI << "4m"; //DELETE THE NEXT 4 LINES OF TEXT

	if (firstLetterOfName != 0)
	{
		avatarHP = (float)height / (firstLetterOfName * 0.02f);
	}
	else
	{
		avatarHP = 0;
	}
	

	std::cout << INDENT << "Using a complex deterministic algorithm, it has been calculated that you have " << avatarHP << " hit point(s)." << std::endl;


	std::cout <<  std::endl << INDENT << "Press 'Enter' to exit the program." << std::endl;
	std::cin.get();
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
