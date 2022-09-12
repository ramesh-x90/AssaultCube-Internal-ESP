#include "pch.h"
#include "Esp.h"
#include "PlayerEnt.h"


#define MAX_HEALTH 100

Esp::Esp(Graphics** graphics, GAME_DATA** gameData)
{
	_graphics = graphics;
	_gameData = gameData;
}


Esp::~Esp()
{

}

void Esp::setGraphics(Graphics** graphics)
{
	_graphics = graphics;
}


void Esp::setGameData(GAME_DATA** gameData)
{
	_gameData = gameData;
}

void Esp::drawPlayers(std::vector<PlayerEnt*> list)
{
	if (*_graphics == nullptr) return;


	for (auto& ent : list)
	{
		if (ent->health <= 0) continue;

		Vector3 Head_sPos , feet_sPos;
		if ( ! w2s(ent->vHead, &Head_sPos) || ! w2s(ent->vPosition, &feet_sPos) ) continue;

		int health = ent->health;
		int dis = getDistence( (*_gameData)->localPayerEnt->vPosition, ent->vPosition);
		std::string name = ent->name;

		std::string sHealth = std::to_string(health);
		std::string sdis = std::to_string(dis);

		int boxHight = (int)( feet_sPos.y - Head_sPos.y);
		int boxWidth = (int)(boxHight / 2);

		if (boxWidth > 200)
			boxWidth = 200;


		Graphics::COLOR color;

		if ((*_gameData)->localPayerEnt->teamId == ent->teamId)
		{
			color = WHITE;
		}
		else
		{
			color = RED;

		}

		//_grahics->drawText((char*)name.c_str(), hVec.x - boxWidth / 2, hVec.y - 13, color);
		//_grahics->drawText((char*)sHealth.c_str(), pVec.x - boxWidth / 2, pVec.y + 5, color);
		//_graphics->drawText((char*)sdis.c_str(), pVec.x - boxWidth / 2, pVec.y + 13, color);
		(*_graphics)->DrawBox(Head_sPos.x - boxWidth / 2, Head_sPos.y, boxWidth, boxHight, 1, color);

		drawHealthBar( health, boxHight, Head_sPos.x - boxWidth / 2 - 2, Head_sPos.y);

	}
}



bool Esp::w2s(Vector3 pos, Vector3* sPos)
{
	ClipCOORD clipCoords{ 0,0,0,0 };
	Vector3 NDC;

	float mX = (float)(*_graphics)->windowWidth / 2.0f;
	float mY = (float)(*_graphics)->windowHeight / 2.0f;

	float* mvpMetrix = (*_gameData)->mvpMatrix->mvpArray;
	
	{
		clipCoords.x = pos.x * mvpMetrix[0] + pos.y * mvpMetrix[4] + pos.z * mvpMetrix[8] + mvpMetrix[12];
		clipCoords.y = pos.x * mvpMetrix[1] + pos.y * mvpMetrix[5] + pos.z * mvpMetrix[9] + mvpMetrix[13];
		clipCoords.z = pos.x * mvpMetrix[2] + pos.y * mvpMetrix[6] + pos.z * mvpMetrix[10] + mvpMetrix[14];
		clipCoords.w = pos.x * mvpMetrix[3] + pos.y * mvpMetrix[7] + pos.z * mvpMetrix[11] + mvpMetrix[15];
	}

	if (clipCoords.z < 0.1f)
		return false;

	NDC.x = clipCoords.x / clipCoords.w;
	NDC.y = clipCoords.y / clipCoords.w;
	NDC.z = clipCoords.z / clipCoords.w;


	sPos->x = ( mX + NDC.x) + (mX * NDC.x);
	sPos->y = (mY + NDC.y) - (mY * NDC.y) + 5 ;


	return true;
}


int Esp::getDistence(Vector3 lP, Vector3 eP)
{
	return ceil(
		sqrt(
			std::pow(lP.x - eP.x, 2) + std::pow(lP.y - eP.y, 2) + std::pow(lP.z - eP.z, 2)
		)
	);
}


void Esp::drawHealthBar(int health, float  phight, float x, float y)
{
	float gonehealth = MAX_HEALTH - health;

	float scaledHealth = std::ceil(gonehealth / MAX_HEALTH * phight);

	(*_graphics)->DrawLine(x, y, x, y + scaledHealth, 3 , RED);
	(*_graphics)->DrawLine(x, y + scaledHealth, x, y + phight, 3 , GREEN );
}