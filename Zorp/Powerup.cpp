#include "pch.h"
#include "Powerup.h"
#include <cstring>


Powerup::Powerup() : m_healthMultiplier{ 1 }, m_attackMultiplier{ 1 },
m_defenceMultiplier{ 1 }
{
	m_name[0] = 0;
}



Powerup::Powerup(const char name[30], float health, float attack, float defence) //implement the rest of this constructor
{
	strcpy_s(m_name, name);
	m_healthMultiplier = health;
	m_attackMultiplier = attack;
	m_defenceMultiplier = defence;
}

Powerup::~Powerup()
{

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
