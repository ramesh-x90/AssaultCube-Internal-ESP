#pragma once

struct Vector3
{
	float x;
	float y;
	float z;


	Vector3()
	{
		x = 0;
		y = 0;
		z = 0;
	}

};

struct Vector2
{
	float x;
	float y;


	Vector2()
	{
		x = 0;
		y = 0;
	}
	Vector2(float _x , float _y)
	{
		x = _x;
		y = _y;
	}

};


struct ClipCOORD
{
	float x;
	float y;
	float z;
	float w;
};
