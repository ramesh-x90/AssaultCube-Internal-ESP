#include "pch.h"
#include "GAME_DATA.h"


GAME_DATA::GAME_DATA(PlayerEnt* localPlayer, EntityEntry* entityEntry , MvpMatrix* mvpMatrix)
{
	this->localPayerEnt = localPlayer;
	this->entityEntry = entityEntry;
	this->mvpMatrix = mvpMatrix;
}


GAME_DATA::~GAME_DATA()
{
	delete entityEntry;
}
