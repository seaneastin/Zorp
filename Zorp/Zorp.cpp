// Zorp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

int main()
{
	int height = 0;
	char firstLetterOfName = 0;
	int avatarHP = 0;
	std::cout << "Welcome to ZORP!" << std::endl;
	std::cout << "ZORP is a game of adventure, danger, and low cunning." << std::endl;
	std::cout << "it is definitely not related to any other text-based adventure game." << std::endl << std::endl;
	std::cout << "First, some questions..." << std::endl;
	std::cout << "How tall are you, in centimeters?" << std::endl;
	std::cin >> height;
	if (std::cin.fail())
	{
		std::cout << "You have failed the first challenge are are eaten by a grue." << std::endl;
	}
	else
	{
		std::cout << "You entered " << height << std::endl;
	}

	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());


	std::cout << "What is the first letter of your name? " << std::endl;

	std::cin >> firstLetterOfName;

	if (std::cin.fail() || !isalpha(firstLetterOfName))
	{
		std::cout << "You have failed the second challenge and are eaten by a grue." << std::endl;
	}
	else
	{
		std::cout << "You entered " << firstLetterOfName << std::endl;
	}

	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());

	if (firstLetterOfName != 0)
	{
		avatarHP = (float)height / (firstLetterOfName * 0.02f);
	}
	else
	{
		avatarHP = 0;
	}
	

	std::cout << std::endl << "Using a complex deterministic algorithm, it has been calculated that you have " << avatarHP << " hit point(s)." << std::endl;


	std::cout << std::endl << "Press 'Enter' to exit the program." << std::endl;
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
