#include "pch.h"
#include "Room.h"
#include "Powerup.h"
#include "Player.h"
#include "Food.h"
#include <iostream>
#include "GameDefines.h"
#include "GameObject.h"
#include "Enemy.h"
#include <algorithm>





Room::Room() : m_type(EMPTY), m_mapPosition{0, 0}
{}


Room::~Room()
{

}

void Room::clearGameObject()
{
	m_objects.clear();
}

void Room::setPosition(Point2D position)
{
	m_mapPosition = position;
}

void Room::setType(int type)
{
	m_type = type;
}

void Room::addGameObject(GameObject* object)
{
	m_objects.push_back(object);
	std::sort(m_objects.begin(), m_objects.end(), GameObject::compare);
}

void Room::removeGameObject(GameObject* object)
{
	for (auto it = m_objects.begin(); it != m_objects.end(); it++)
	{
		if (*it == object)
		{
			//reset the objects room number
			//there is an error with this line
			(*it)->setPosition(Point2D{ -1,-1 });
			m_objects.erase(it);
			return;
		}
	}
}

int Room::getType()
{
	return m_type;
}

Enemy * Room::getEnemy()
{
	for (GameObject* pObj : m_objects)
	{
		Enemy* enemy = dynamic_cast<Enemy*>(pObj);
		if (enemy != nullptr)
			return enemy;
	}
	return nullptr;
}

Powerup * Room::getPowerup()
{
	for (GameObject* pObj : m_objects)
	{
		Powerup* powerup = dynamic_cast<Powerup*>(pObj);
		if (powerup != nullptr)
			return powerup;
	}
	return nullptr;
}

Food * Room::getFood()
{
	for (GameObject* pObj : m_objects)
	{
		Food* food = dynamic_cast<Food*>(pObj);
		if (food != nullptr)
			return food;
	}
	return nullptr;
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
		
		if (m_objects.size() > 0)
			m_objects[0]->draw();
		else

		std::cout << "[ " << GREEN << "\xb0" << RESET_COLOR << " ] ";
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

		if (m_objects.size() > 0)
			m_objects[0]->drawDescription();
		else

		std::cout << INDENT << "You are in an empty meadow. There is nothing of note here." << std::endl;
		break;
	case ENTRANCE:
		std::cout << INDENT << "The entrance you used to enter this maze is blocked. There is no going back" << std::endl;
		break;
	case EXIT:
		std::cout << INDENT << "Despite all odds, you made it to the exit. Congratulations." << std::endl;

	}
	
	return 1;
}

void Room::lookAt()
{
	if (m_objects.size() > 0)
		m_objects[0]->lookAt();
	else
		std::cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You look around, but see nothing worth mentioning" << std::endl;
}

//bool Room::pickup(Player * pPlayer)
//{
//	if (m_powerup == nullptr)
//	{
//		std::cout << EXTRA_OUTPUT_POS << RESET_COLOR << "There is nothing here to pick up." << std::endl;
//		return true;
//	}
//
//	std::cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You pick up the " << m_powerup->getName() << std::endl;
//
//
//	//add the powerup to the player's inventory
//	pPlayer->addPowerup(m_powerup);
//
//	//remove the powerup from the room
//	// (but don't delete it, the player owns it now
//	m_powerup = nullptr;
//
//	//change this room type to empty
//	m_type = EMPTY;
//
//	std::cout << INDENT << "Press 'Enter' to continue.";
//	std::cin.clear();
//	std::cin.ignore(std::cin.rdbuf()->in_avail());
//	std::cin.get();
//	return true;
//}
//
//bool Room::executeCommand(int command, Player* pPlayer)
//{
//	std::cout << EXTRA_OUTPUT_POS;
//	switch (command)
//	{
//	case LOOK:
//		if (m_type == TREASURE_HP || m_type == TREASURE_AT || m_type == TREASURE_DF)
//		{
//			std::cout << EXTRA_OUTPUT_POS << RESET_COLOR << "THRE is osme treasure here. It looks small enough to pick up." << std::endl;
//		}
//
//		else
//		{
//			std::cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You look around, but see nothing worth mentioning" << std::endl;
//		}
//		std::cout << INDENT << "Press 'ENTER' to continue.";
//		std::cin.clear();
//		std::cin.ignore(std::cin.rdbuf()->in_avail());
//		return true;
//	case FIGHT:
//		std::cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You could try to fight, but you don't have a weapon" << std::endl;
//		std::cout << INDENT << "Pres 'ENTER' to continue.";
//		std::cin.clear();
//		std::cin.ignore(std::cin.rdbuf()->in_avail());
//		std::cin.get();
//		return true;
//
//	case PICKUP:
//		return pickup(pPlayer);
//
//	default:
//		//the direction was not valid
//		//do nothing, go back to the top of the loop and ask again
//		std::cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You try, but you just can't do it." << std::endl;
//
//		std::cout << INDENT << "Press 'Enter' to continue.";
//		std::cin.clear();
//		std::cin.ignore(std::cin.rdbuf()->in_avail());
//		std::cin.get();
//		break;
//	}
//	return false;
//}
