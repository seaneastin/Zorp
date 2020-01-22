#pragma once
#include "Point2D.h"
#include <vector>


class GameObject;
class Powerup;
class Player;
class Enemy;
class Food;

class Room
{
public:
	Room();
	~Room();


	void setPosition(Point2D position);
	void setType(int type);
	
	void addGameObject(GameObject* object);
	void removeGameObject(GameObject* object);
	
	int getType();
	Enemy* getEnemy();
	Powerup* getPowerup();
	Food* getFood();



	void draw();
	int drawDescription();
	void lookAt();




private:
	Point2D m_mapPosition;
	int m_type;


	std::vector < GameObject*> m_objects;
};

