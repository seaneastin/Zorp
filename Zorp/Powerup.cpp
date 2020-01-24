#include "pch.h"
#include "Powerup.h"
#include "GameDefines.h"
#include <cstring>
#include <iostream>
#include <fstream>
#include <string>


Powerup::Powerup() : m_healthMultiplier{ 1 }, m_attackMultiplier{ 1 },
m_defenceMultiplier{ 1 }
{
	m_priority = PRIORITY_POWERUP;
	m_name[0] = 0;
}



Powerup::Powerup(const char name[30], float health, float attack, float defence) //implement the rest of this constructor
{

	m_priority = PRIORITY_POWERUP;
	strcpy_s(m_name, name);
}

Powerup::~Powerup()
{

}

bool Powerup::load(std::ifstream & in, const Game * game)
{
	if (!in.is_open())
		return false;

	char buffer[50] = { 0 };

	in.get(buffer, 50, ',');

	if (in.rdstate() || buffer[0] == 0)
		return false;
	m_priority = std::stoi(buffer);

	in.ignore(1);
	in.get(buffer, 50, ',');
	if (in.rdstate() || buffer[0] == 0)
		return false;
	m_mapPosition.x = std::stoi(buffer);

	in.ignore(1);

	in.get(buffer, 50, ',');
	if (in.rdstate() || buffer[0] == 0)
		return false;
	m_mapPosition.y = std::stoi(buffer);

	in.ignore(1);

	in.get(buffer, 50, ',');

	if (in.rdstate() || buffer[0] == 0)
		return false;


	strcpy_s(m_name, buffer);

	in.ignore(1);
	in.get(buffer, 50, ',');

	if (in.rdstate() || buffer[0] == 0)
		return false;

	//these values are floats, so use stof()
	m_healthMultiplier = std::stof(buffer);
	in.ignore(1);
	in.get(buffer, 50, ',');
	if (in.rdstate() || buffer[0] == 0)
		return false;
	m_attackMultiplier = std::stof(buffer);

	in.ignore(1);

	in.getline(buffer, 50);

	if (in.rdstate() || buffer[0] == 0)
		return false;
	m_defenceMultiplier = std::stof(buffer);

	return true;


}




char * Powerup::getName()
{
	return m_name;
}

float Powerup::getHealthMultiplier()
{
	return m_healthMultiplier;
}

float Powerup::getAttackMultiplier()
{
	return m_attackMultiplier;
}

float Powerup::getDefenceMultiplier()
{
	return m_defenceMultiplier;
}

void Powerup::setName(const char * pStr)
{
	strncpy_s(m_name, pStr, 30);
}

bool Powerup::compare(const Powerup* p1, const Powerup* p2)
{
	return (strcmp(p1->m_name, p2->m_name) < 0) ? true : false;
}

void Powerup::draw()
{
	std::cout << "[ " << YELLOW << "$" << RESET_COLOR << " ] ";
}

void Powerup::drawDescription()
{
	std::cout << INDENT << "There appears to be some treasure here. Perhaps you should investigate futher." << std::endl;
}



void Powerup::lookAt()
{
	std::cout << EXTRA_OUTPUT_POS << RESET_COLOR << "There is some treasure here. it looks small enough to pick up.";
}

void Powerup::save(std::ofstream & out)
{
	if (!out.is_open())
		return;


	out << m_priority << ",";
	out << m_mapPosition.x << ",";
	out << m_mapPosition.y << ",";
	out << m_name << ",";
	out << m_healthMultiplier << ",";
	out << m_attackMultiplier << ",";
	out << m_defenceMultiplier << std::endl;
}


