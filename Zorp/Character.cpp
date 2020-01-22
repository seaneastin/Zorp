#include "pch.h"
#include "Powerup.h"
#include "Character.h"
#include <algorithm>
#include <fstream>



Character::Character() : GameObject{{0, 0}}, m_healthPoints{ 0 },
m_attackPoints{ 0 }, m_defendPoints{ 0 }
{}

Character::Character(Point2D position, int health, int attack, int defend) :
	GameObject{ position }, m_healthPoints{health},
	m_attackPoints{ 0 }, m_defendPoints{ 0 }
{}




Character::~Character()
{}


void Character::addPowerup(Powerup* pPowerup)
{
	m_powerups.push_back(pPowerup);
	std::sort(m_powerups.begin(), m_powerups.end(), Powerup::compare);
}

void Character::save(std::ofstream & out)
{
	if (!out.is_open())
		return;


	out << m_priority << ",";
	out << m_mapPosition.x << ",";
	out << m_mapPosition.y << ",";
	out << m_healthPoints << ",";
	out << m_attackPoints << ",";
	out << m_defendPoints << ",";


	out << m_powerups.size() << std::endl;

	for (int i = 0; i < m_powerups.size(); i++)
	{
		//save only the name of each powerup
		//becasue each powerup will be saved by the Game class
		// (the charecter only stores a pointer to these powerups)
		//when loading the game calas will need to re-link the pointers
		out << m_powerups[i]->getName() << std::endl;
	}
}
