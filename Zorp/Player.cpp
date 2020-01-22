#include "pch.h"
#include "GameDefines.h"
#include "Room.h"
#include "Player.h"
#include <algorithm>
#include "Powerup.h"
#include "Enemy.h"
#include "Food.h"

Player::Player() : Character({0, 0}, 100, 20 , 20)
{
	m_priority = PRIORITY_PLAYER;
}

Player::Player(int x, int y) : Character({x,y}, 100, 20 , 20)
{

}


Player::~Player()
{

}







void Player::draw()
{
	Point2D outPos =
	{

		INDENT_X + (6 * m_mapPosition.x) + 3,
		MAP_Y + m_mapPosition.y

	};
	// draw the player's position on the map
	// move cursor to map pos and delete character at current position
	std::cout << CSI << outPos.y << ";" << outPos.x << "H";
	std::cout << MAGENTA << "\x81" << RESET_COLOR;

	std::cout << INVENTORY_OUTPUT_POS;
	for (auto it = m_powerups.begin(); it < m_powerups.end(); it++)
	{
		std::cout << (*it)->getName() << "\t";
	}

}

void Player::pickup(Room * pRoom)
{

	if (pRoom->getPowerup() != nullptr)
	{
		Powerup* powerup = pRoom->getPowerup();
std::cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You pick up the " << powerup->getName() << std::endl;	
	//add the powerup to the player's inventory
	addPowerup(powerup);
	//remove the powerup from the room
	// (but don't delete it, the player owns it now
	pRoom->removeGameObject(powerup);
	}
	else if (pRoom->getFood() != nullptr)
	{
		Food* food = pRoom->getFood();
		//east the food
		m_healthPoints += food->getHP();
		std::cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You feel refresehd you health is now " << m_healthPoints << std::endl;
		//remove the food from the room
		pRoom->removeGameObject(food);
	}
	else
	{
		std::cout << EXTRA_OUTPUT_POS << RESET_COLOR << "There is nothing here to pick up." << std::endl;
	}

}

void Player::attack(Enemy * pEnemy)
{
	if (pEnemy == nullptr)
	{
		std::cout << EXTRA_OUTPUT_POS << RESET_COLOR << "There is no one here you can fight with." << std::endl;
	}
	else
	{
		pEnemy->onAttacked(m_attackPoints);

		if (pEnemy->isAlive() == false)
		{
			std::cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You fight a grue and kill it." << std::endl;
		}
		else
		{
			int damage = pEnemy->getAT() - m_defendPoints;
			if (damage < 1)
			{
				damage = 1;
			}
				m_healthPoints -= damage;

			std::cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You fight a grue and take " << damage << " points damage. Your health is now at " << m_healthPoints << std::endl;
			std::cout << INDENT << "The grue has " << pEnemy->getHP() << " health remaining." << std::endl;
		}

	}
}


void Player::executeCommand(int command, Room* pRoom)
{

	switch (command)
	{
	case EAST:
		if (m_mapPosition.x < MAZE_WIDTH - 1)
			m_mapPosition.x++;
		return;
	case WEST:
		if (m_mapPosition.x > 0)
			m_mapPosition.x--;
		return;
	case NORTH:
		if (m_mapPosition.y > 0)
			m_mapPosition.y--;
		return;
	case SOUTH:
		if (m_mapPosition.y < MAZE_HEIGHT - 1)
			m_mapPosition.y++;
		return;
	case LOOK:
		pRoom->lookAt();
		break;

	case FIGHT:
		attack(pRoom->getEnemy());
		break;
	case PICKUP:
		pickup(pRoom);
		break;

	default:
		//the direction was not valid
		//do nothing, go back to the top of the loop and ask again
		std::cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You try, but you just can't do it." << std::endl;

		
		break;
		}

	
	std::cout << INDENT << "Press 'Enter' to continue.";
	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	std::cin.get();
}

void Player::drawDescription()
{

}

void Player::lookAt()
{
	std::cout << EXTRA_OUTPUT_POS << RESET_COLOR << "Hmm, I look good!" << std::endl;
}

