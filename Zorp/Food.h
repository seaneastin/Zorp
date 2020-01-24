#pragma once
#include "GameObject.h"
#include <iostream>
#include <fstream>

class Food : public GameObject
{
public:

	bool load(std::ifstream& in, const Game* game);
	Food();
	Food(Point2D position);
	~Food() {}

	int getHP() { return m_healthPoints; }

	void draw();
	void drawDescription();
	void lookAt();

	virtual void save(std::ofstream& out);


private:
	int m_healthPoints;
};

