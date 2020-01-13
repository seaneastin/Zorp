#include "pch.h"
#include "Room.h"
#include <iostream>
#include "GameDefines.h"

Room::Room() : m_type(EMPTY), m_mapPosition(Point2D{0,0})
{

}


Room::~Room()
{
}

void Room::setPosition(Point2D position)
{
	m_mapPosition = position;
}

void Room::setType(int type)
{
	m_type = type;
}

int Room::getType()
{
	return m_type;
	return 0;
}

void Room::draw()
{
	//find the console output position
	int outX = INDENT_X + (6 * m_mapPosition.x) + 1;
	int outY = MAP_Y + m_mapPosition.y;
	//jump to the correct location
	std::cout << CSI << outY << ";" << outX << "H";
	//draw the room
	switch (m_type)
	{
	case EMPTY:
		std::cout << "[ " << GREEN << "\xb0" << RESET_COLOR << " ] ";
		break;
	case ENEMY:
		std::cout << "[ " << RED << "\x94" << RESET_COLOR << " ] ";
		break;
	case TREASURE_HP:
	case TREASURE_AT:
	case TREASURE_DF:
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

int Room::drawDescription()
{


	//reset draw colors
	std::cout << RESET_COLOR;
	//jump to the correct location
	std::cout << CSI << ROOM_DESC_Y << ";" << 0 << "H";
	//delete and insert 4 lines
	std::cout << CSI << "4M" << CSI << "4L" << std::endl;

	//write description of current room

	switch (m_type)
	{
	case EMPTY:
		std::cout << INDENT << "You are in an empty meadow. There is nothing of note here." << std::endl;
		break;
	case ENEMY:
		std::cout << INDENT << "BEWARE. An enemy is approaching." << std::endl;
		break;
	case TREASURE:
		std::cout << INDENT << "Your journey has been rewardewd. You have found some treasure" << std::endl;
		break;
	case FOOD:
		std::cout << INDENT << "At last! You collect some food to sustain you on your journey." << std::endl;
		break;
	case ENTRANCE:
		std::cout << INDENT << "The entrance you used to enter this maze is blocked. There is no going back" << std::endl;
		break;
	case EXIT:
		std::cout << INDENT << "Despite all odds, you made it to the exit. Congratulations." << std::endl;
	case TREASURE_HP:
	case TREASURE_AT:
	case TREASURE_DF:
		std::cout << INDENT << "There appears to be some treasure here. Perhaps you should investigate futher." << std::endl;
		break;
	}
	
	return 1;
}

bool Room::executeCommand(int command)
{
	std::cout << EXTRA_OUTPUT_POS;
	switch (command)
	{
	case LOOK:
		if (m_type == TREASURE_HP || m_type == TREASURE_AT || m_type == TREASURE_DF)
		{
			std::cout << EXTRA_OUTPUT_POS << RESET_COLOR << "THRE is osme treasure here. It looks small enough to pick up." << std::endl;
		}

		else
		{
			std::cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You look around, but see nothing worth mentioning" << std::endl;
		}
		std::cout << INDENT << "Press 'ENTER' to continue.";
		std::cin.clear();
		std::cin.ignore(std::cin.rdbuf()->in_avail());
		return true;
	case FIGHT:
		std::cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You could try to fight, but you don't have a weapon" << std::endl;
		std::cout << INDENT << "Pres 'ENTER' to continue.";
		std::cin.clear();
		std::cin.ignore(std::cin.rdbuf()->in_avail());
		std::cin.get();
		return true;

	default:
		//the direction was not valid
		//do nothing, go back to the top of the loop and ask again
		std::cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You try, but you just can't do it." << std::endl;

		std::cout << INDENT << "Press 'Enter' to continue.";
		std::cin.clear();
		std::cin.ignore(std::cin.rdbuf()->in_avail());
		std::cin.get();
		break;
	}
	return false;
}
