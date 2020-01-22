#include "pch.h"
#include "Enemy.h"
#include "GameDEfines.h"
#include <iostream>

Enemy::Enemy() : Character({ 0,0 }, 20, 10, 5)
{
	m_priority = PRIORITY_ENEMY;
}


void Enemy::onAttacked(int attackPoints)
{
	m_healthPoints = attackPoints - m_defendPoints;
	if (m_healthPoints < 0)
		m_healthPoints = 0;
}

void Enemy::draw()
{
	std::cout << "[ " << RED << "\x94" << RESET_COLOR << " ] ";
}

void Enemy::drawDescription()
{
	std::cout << INDENT << RED << "BEWARE." << RESET_COLOR << " An enemy is approaching." << std::endl;
}

void Enemy::lookAt()
{
	std::cout << EXTRA_OUTPUT_POS << RESET_COLOR << "LOOK OUT! An ememy is approaching." << std::endl;
}
