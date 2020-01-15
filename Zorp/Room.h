#pragma once
#include "Point2D.h"

class Powerup;
class Player;

class Room
{
public:
	Room();
	~Room();


	void setPosition(Point2D position);
	void setType(int type);
	int getType();

	void draw();
	int drawDescription();

	bool executeCommand(int command, Player* pPlayer);

private:
	Point2D m_mapPosition;
	int m_type;

	bool pickup(Player* pPlayer);

	Powerup* m_powerup;

};

