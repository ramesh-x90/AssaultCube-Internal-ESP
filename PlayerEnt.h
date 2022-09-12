#pragma once

class PlayerEnt
{
public:
	uintptr_t vTable; //0x0000
	Vector3 vHead; //0x0004
	char pad_0010[36]; //0x0010
	Vector3 vPosition; //0x0034
	Vector2 viewAngel; //0x0040
	char pad_0048[176]; //0x0048
	int32_t health; //0x00F8
	int32_t armor; //0x00FC
	char pad_0100[64]; //0x0100
	int ammoArray[5]; //0x0140
	char pad_0154[209]; //0x0158
	char name[7]; //0x0225
	char pad_022C[256]; //0x022C
	int32_t teamId; //0x032C
}; 