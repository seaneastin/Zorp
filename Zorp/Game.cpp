#include "pch.h"
#include "Game.h"
#include <iostream>
#include <windows.h>
#include <random>
#include <time.h>
#include "Enemy.h"
#include "Food.h"
#include "Powerup.h"
#include <fstream>

Game::Game() : m_gameOver{ false }
{

}


Game::~Game()
{
	delete[] m_powerups;
	delete[] m_enemies;
	delete[] m_food;
}

bool Game::startup()
{
	if (enableVirtualTerminal() == false)
	{
		std::cout << "The virutal terminal processing mode could not be activated" << std::endl;
		std::cout << "Press 'Enter' to exit." << std::endl;

		std::cin.get();
		return false;
	}
	srand(time(nullptr));

	initializeMap();
	initializePowerups();
	initializeEnemies();
	initializeFood();

	m_player.setPosition(Point2D{ 0,0 });

	draWelcomeMessage();

	return true;
}

void Game::update()
{
	Point2D playerPos = m_player.getPosition();

	if (m_map[playerPos.y][playerPos.x].getType() == EXIT)
	{
		m_gameOver = true;
		return;
	}
	int command = getCommand();

	if (command == QUIT)
	{
		m_gameOver = true;
		return;
	}

	m_player.executeCommand(command, &m_map[playerPos.y][playerPos.x]);

 	for (int i = 0; i < m_enemyCount; i++)
	{
		if (m_enemies[i].isAlive() == false)
		{
			Point2D pos = m_enemies[i].getPosition();
			m_map[pos.y][pos.x].removeGameObject(&m_enemies[i]);
		}
	}
}

void Game::draw()
{
	Point2D playerPos = m_player.getPosition();

	//list the directions the player can take
	drawValidDirections();

	//draw the descripiton of the current room
	m_map[playerPos.y][playerPos.x].drawDescription();

	//redraw the map
	drawMap();

	//draw the player on the map
	m_player.draw();
}

bool Game::isGameOver()
{
	return m_gameOver;
}

bool Game::enableVirtualTerminal()
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

void Game::initializeMap()
{
	//fill the arrays with random room type

	for (int y = 0; y < MAZE_HEIGHT; y++)
	{
		for (int x = 0; x < MAZE_WIDTH; x++)
		{


			
			m_map[y][x].setPosition(Point2D{ x, y });
			

		}

	}

	//set the entrance and exit of the maze
	m_map[0][0].setType(ENTRANCE);
	m_map[MAZE_HEIGHT - 1][MAZE_WIDTH - 1].setType(EXIT);
}

void Game::initializeEnemies()
{
	//create a dynamic array of enemies
	// (the num ber of enemies iwill change every game)
	m_enemyCount = 1 + rand() % 4;
	m_enemies = new Enemy[m_enemyCount];

	// randomly place the enemies in rooms on the map
	for (int i = 0; i < m_enemyCount; i++)
	{
		// a bit of math ensures the enemies wont spawn directly
		// on or next to the entrance
		int x = 2 + (rand() % (MAZE_WIDTH - 3));
		int y = 2 + (rand() % (MAZE_HEIGHT - 3));

		m_enemies[i].setPosition(Point2D{ x, y });
		m_map[y][x].addGameObject(&m_enemies[i]);
	}
}

void Game::initializePowerups()
{
	//create some powerups
	m_powerupCount = 3;
	m_powerups = new Powerup[m_powerupCount];
	//randomdly place the food int the map

	{

		// abit of math ensures the enemies wont spanw directly
			//on or next to the entrance
		int x = 2 + (rand() % (MAZE_WIDTH - 3));
		int y = 2 + (rand() % (MAZE_HEIGHT - 3));

		float HP = 1;
		float AT = 1;
		float DF = 1;
		
		for (int i = 0; i < m_powerupCount; i++)
		{
			char name[30] = "";
			int x = rand() % (MAZE_WIDTH - 1);
			int y = rand() % (MAZE_HEIGHT - 1);

			float HP = 1;
			float AT = 1;
			float DF = 1;

			switch (i)
			{
			case 0:
				strcpy_s(name, "potion of ");

				m_powerups[i].setHealthMultiplier(1.1f);
				break;
			case 1:
				strcpy_s(name, "sword of ");
				m_powerups[i].setAttackMultiplier(1.1f);
				break;

			case 2:
				strcpy_s(name, "shield of ");
				m_powerups[i].setDefenceMultiplier(1.1f);
				break;

			}
			strncat_s(name, itemNames[(rand() % 15)], 30);
			m_powerups[i].setName(name);
			m_powerups[i].setPosition(Point2D{ x, y });
			m_map[y][x].addGameObject(&m_powerups[i]);
		}
	}

	
}



void Game::initializeFood()
{
	//create some food
	m_foodCount = 3;
	m_food = new Food[m_foodCount];
	//randomly place the food in the map
	for (int i = 0; i < m_foodCount; i++)
	{
		int x = rand() % (MAZE_WIDTH - 1);
		int y = rand() % (MAZE_HEIGHT - 1);
		m_food[i].setPosition(Point2D{ x, y });
		m_map[y][x].addGameObject(&m_food[i]);
	}
}

void Game::draWelcomeMessage()
{


	std::cout << TITLE << MAGENTA << "Welcome to ZORP!" << RESET_COLOR << std::endl;
	std::cout << INDENT << "ZORP is a game of adventure, danger, and low cunning." << std::endl;
	std::cout << INDENT << "it is definitely not related to any other text-based adventure game." << std::endl << std::endl;
}

void Game::drawMap()
{
	Point2D position = { 0, 0 };
	//reset draw colors
	std::cout << RESET_COLOR;
	for (position.y = 0; position.y < MAZE_HEIGHT; position.y++)
	{
		for (position.x = 0; position.x < MAZE_WIDTH; position.x++)
		{
			m_map[position.y][position.x].draw();
		}
		std::cout << std::endl;
	}
}

void Game::drawValidDirections()
{
	Point2D position = m_player.getPosition();

	//reset draw colors
	std::cout << RESET_COLOR;
	// jump to the correct location
	std::cout << CSI << MOVEMENT_DESC_Y + 1 << ";" << 0 << "H";
	std::cout << INDENT << "You can see paths leading to the " <<
		((position.x > 0) ? "west, " : "") <<
		((position.x < MAZE_WIDTH - 1) ? "east, " : "") <<
		((position.y > 0) ? "north, " : "") <<
		((position.y < MAZE_HEIGHT - 1) ? "south, " : "") << std::endl;
}

int Game::getCommand()
{
	//for now, we can't read commands longer than 50 characters
	char input[50] = "\0";
	// jump to the correct location
	std::cout << CSI << PLAYER_INPUT_Y << ";" << 0 << "H";
	//clear any existing text
	std::cout << CSI << "5M";
	
	// insert 5 blank lines to ensure the inventory output remains correct
	std::cout << CSI << "5L";

	std::cout << INDENT << "Enter a command.";

	//move cursor to position for player to enter input
	std::cout << CSI << PLAYER_INPUT_Y << ";" << PLAYER_INPUT_X << "H" << YELLOW;


	//clear the input buffer, ready for player input

	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());

	std::cin >> input;
	std::cout << RESET_COLOR;


	bool bMove = false;
	bool bPickup = false;
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
		if (strcmp(input, "exit") == 0)
		{
			return QUIT;
		}
		if (strcmp(input, "pick") == 0)
		{
			bPickup = true;
		}
		else if (bPickup == true)
		{
			if (strcmp(input, "up") == 0)
				return PICKUP;
		}

		if (strcmp(input, "save") == 0)
		{
			//process the save command here, as the game class is
			// the only calss with direct access to all the game obje cts

			save();
			return SAVE;
		}
		

		char next = std::cin.peek();
		if (next == '\n' || next == EOF)
			break;
		std::cin >> input;

	}
	return 0;

}

void Game::save()
{
	std::ofstream out;

	// open the file for output, and truncate (any contents that
	// existed in the file before it is open are discarded)
	out.open("zorp_savegame.txt", std::ofstream::out | std::ofstream::trunc);

	if (out.is_open())
	{
		//save the position of every game object, and the player's stats

		if (m_gameOver == true)
		{
			std::cout << EXTRA_OUTPUT_POS <<
				"You have perished. Saving will not save you." << std::endl; 
			std::cout << INDENT << "Your progress has not been saved." << RESET_COLOR << std::endl;
		}
		else
		{
			//output the powerups first, as ethese will need to be loaded before
			//we load any characters (so we can correctly copy the powerup pointers
			// to the characters' powerup list)

			out << m_powerupCount << std::endl;
			for (int i = 0; i < m_powerupCount; i++)
			{
				m_powerups[i].save(out);
			}

			out << m_enemyCount << std::endl;
			for (int i = 0; i < m_enemyCount; i++)
			{
				m_enemies[i].save(out);
			}

			out << m_foodCount << std::endl;
			for (int i = 0; i < m_foodCount; i++)
			{
				m_food[i].save(out);
			}

			m_player.save(out);
		}
	}
	else
	{
		std::cout << EXTRA_OUTPUT_POS << RED << "A grue has corrupted the scroll of rememberance." << std::endl;
		std::cout << INDENT << "Your progress has not been saved." << RESET_COLOR << std::endl;
	}
}
