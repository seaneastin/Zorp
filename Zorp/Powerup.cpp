#include "pch.h"
#include "Powerup.h"
#include <cstring>


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
