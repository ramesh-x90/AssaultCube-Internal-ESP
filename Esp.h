#pragma once
#include "Graphics.h"
#include "GAME_DATA.h"


class Esp
{
private:
	Graphics** _graphics;
	GAME_DATA** _gameData;

	void drawHealthBar(int health, float  phight, float x, float y);

public:
	Esp(Graphics ** graphics , GAME_DATA ** gameData);
	~Esp();

	void setGraphics(Graphics** graphics);
	void setGameData(GAME_DATA** gameData);

	void drawPlayers(std::vector<PlayerEnt*> list);

	bool w2s(Vector3 pos, Vector3* sPos);
	int getDistence(Vector3 lP, Vector3 eP);

};

