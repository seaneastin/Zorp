#pragma once
#include "GameObject.h"
#include <iostream>
#include <fstream>
class Food : public GameObject
{
public:
	Food();
	Food(Point2D position);
	~Food() {}

	int getHP() { return m_healthPoints; }

	void draw();
	void drawDescription();
	void lookAt();

	void save(std::ofstream& out);


private:
	int m_healthPoints;
};

