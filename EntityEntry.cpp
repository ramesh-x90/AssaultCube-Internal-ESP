#include "pch.h"
#include "EntityEntry.h"


EntityEntry::EntityEntry(int count, PlayerEnt* localPlayer)
{
	_entityCount = count;
	_localPlayer = localPlayer;

}


EntityEntry::EntityEntry(int count, uintptr_t* dmAdd, PlayerEnt* localPlayer)
{
	_entityCount = count;
	dmAddress = dmAdd;
	_localPlayer = localPlayer;
}

EntityEntry::~EntityEntry()
{
}

std::vector<PlayerEnt*> EntityEntry::getPlayers()
{
	uintptr_t enityListAddress = *dmAddress;

	std::vector<PlayerEnt*> playerEnts;
	unsigned int i = 0;

	while (i < (unsigned)_entityCount && dmAddress != nullptr && *dmAddress != 0)
	{
		try
		{
			PlayerEnt* entPtr = *(PlayerEnt**)(enityListAddress + sizeof(int) * i);
			i++;

			if (entPtr == 0 && i != 1) break;

			if ((int)entPtr < 0) continue;

			if ((int)entPtr>>25 == 0 ||  (int)entPtr >> 29 > 0) continue;

			uintptr_t* vTableAdd = * (uintptr_t**)entPtr;

			if ( (uintptr_t)vTableAdd == 0x4E4A98 || (uintptr_t)vTableAdd == 0x4E4AC0)
			{
				if (*(uintptr_t*)entPtr != *(uintptr_t*)_localPlayer)
				{
					playerEnts.push_back(entPtr);
				}

			}
		}
		catch (const std::exception&)
		{
			continue;
		}



	}
	return playerEnts;
}
