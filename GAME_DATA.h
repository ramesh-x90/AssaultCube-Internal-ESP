#pragma once
#include "PlayerEnt.h"
#include "EntityEntry.h"
#include "MvpMatrix.h"

class GAME_DATA
{
public:
	PlayerEnt* localPayerEnt;
	EntityEntry* entityEntry;
	MvpMatrix* mvpMatrix;

public:
	GAME_DATA(PlayerEnt* localPlayer, EntityEntry* entityEntry , MvpMatrix* mvpMatrix);
	~GAME_DATA();

};

