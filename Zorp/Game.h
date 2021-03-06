#pragma once
#include "GameDefines.h";
#include "room.h";
#include "Player.h"

class Enemy;
class Powerup;


class Game
{
public:
	Game();
	~Game();

public:
	bool startup();
	void update();
	void draw();
	bool isGameOver();


	Powerup* findPowerup(const char* name, bool isLoading = false) const;
private:
	bool enableVirtualTerminal();
	void initializeMap();
	void initializeEnemies();
	void initializePowerups();
	void initializeFood();


	void draWelcomeMessage();
	void drawMap();
	void drawValidDirections();

	int getCommand();

	void save();
	bool load();


private:
	bool m_gameOver;
	Room m_map[MAZE_HEIGHT][MAZE_WIDTH];

	int m_enemyCount;
	Enemy* m_enemies;

	int m_foodCount;
	Food* m_food;

	int m_powerupCount;
	Powerup* m_powerups;

	int m_tempPowerupCount;
	Powerup* m_tempPowerups; // a place to store temporary powerups during loading

	Player m_player;
};

