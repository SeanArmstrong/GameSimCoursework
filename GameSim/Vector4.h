/*
Class:Vector4
Author:Rich Davison
*/

#pragma once

class Vector4	{
public:
	Vector4(void) {
		x = y = z = w = 1.0f;
	}
	Vector4(float x, float y, float z, float w) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	~Vector4(void){}

	float x;
	float y;
	float z;
	float w;
};

