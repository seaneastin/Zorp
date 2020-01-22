#include "pch.h"
#include "Food.h"
#include "GameDefines.h"
#include <iostream>
#include <fstream>

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

void Food::save(std::ofstream& out)
{
	if (!out.is_open())
		return;


	out << m_priority << ",";
	out << m_mapPosition.x << ",";
	out << m_mapPosition.y << ",";
	out << m_healthPoints << ",";
}

