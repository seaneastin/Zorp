#pragma once
#include "GameDefines.h";
#include "room.h";
#include "Player.h"
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
private:
	bool enableVirtualTerminal();
	void initializeMap();

	void draWelcomeMessage();
	void drawMap();
	void drawValidDirections();

	int getCommand();

private:
	bool m_gameOver;
	Room m_map[MAZE_HEIGHT][MAZE_WIDTH];
	Player m_player;
};

