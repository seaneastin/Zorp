#include "pch.h"
#include "Food.h"
#include "GameDefines.h"
#include <iostream>

Food::Food() : m_healthPoints{ 10 }
{
	m_priority = PRIORITY_FOOD;
};

Food::Food(Point2D position) : GameObject{ position }, m_healthPoints{ 10 }
{
	m_priority = PRIORITY_FOOD;
};

void Food::draw()
{
	std::cout << "[ " << CYAN << "\xcf" << RESET_COLOR << " ] ";
}

void Food::drawDescription()
{
	std::cout << INDENT << "You smell a recently extinguished campfire, perhaps left by a prevoius traveller." << std::endl;
}

void Food::lookAt()
{
	std::cout << EXTRA_OUTPUT_POS << RESET_COLOR << "There is some food here. It should be edible.";
}

