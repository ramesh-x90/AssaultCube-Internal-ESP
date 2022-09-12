#pragma once
#include "PlayerEnt.h"


class EntityEntry
{
private:
	int _entityCount = 100;
	PlayerEnt* _localPlayer;
public: 
	uintptr_t * dmAddress;


	EntityEntry(int count , PlayerEnt* localPlayer);
	EntityEntry(int count, uintptr_t* dmAdd , PlayerEnt* localPlayer);
	~EntityEntry();

	std::vector<PlayerEnt*> getPlayers();
};

