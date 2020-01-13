#include "pch.h"
#include "GameDefines.h"
#include "Room.h"
#include "Player.h"



Player::Player() : m_mapPosition{0,0}, m_healthPoints{100}, m_attackPoints{20}, m_defendPoints{20}
{

}

Player::Player(int x, int y) : m_mapPosition{ x , y}, m_healthPoints{ 100 }, m_attackPoints{ 20 }, m_defendPoints{ 20 }
{

}


Player::~Player()
{
}

void Player::setPosition(Point2D position)
{
	m_mapPosition = position;
}

Point2D Player::getPosition()
{
	return m_mapPosition;
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
		std::cout << (*it).getName() << "\t";
	}

}


bool Player::executeCommand(int command, int roomType)
{

	switch (command)
	{
	case EAST:
		if (m_mapPosition.x < MAZE_WIDTH - 1)
			m_mapPosition.x++;
		return true;
	case WEST:
		if (m_mapPosition.x > 0)
			m_mapPosition.x--;
		return true;
	case NORTH:
		if (m_mapPosition.y > 0)
			m_mapPosition.y--;
		return true;
	case SOUTH:
		if (m_mapPosition.y < MAZE_HEIGHT - 1)
			m_mapPosition.y++;
		return true;
	case PICKUP:
		return pickup(roomType);
	}
	return false;
}

bool Player::pickup(int roomType)
{
	static const char itemNames[15][30] = { "indifference", "invisibility", "invulnerability", "incontinence",
											"improbability", "impatience", "indecision", "inspiration",
											"independence", "incurability", "integration", "invocation",
											"inferno", "indigestion", "inoculation" };
	int item = rand() % 15;
	char name[30] = "";

	switch(roomType)
	{
	case TREASURE_HP:
		strcpy_s(name, "potion of ");
		break;
	case TREASURE_AT:
		strcpy_s(name, "sword of ");
		break;
	case TREASURE_DF:
		strcpy_s(name, "shield of ");
		break;
	default:
		return false;
	}
	// append the item name to the string
	strncat_s(name, itemNames[item], 30);
	std::cout << EXTRA_OUTPUT_POS << RESET_COLOR <<
		"YOU pick up the " << name << std::endl;
	m_powerups.push_back(Powerup(name, 1, 1, 1.1f));

	std::cout << INDENT << "Press 'Enter' to continue.";
	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	std::cin.get();
	return true;
}
