#pragma once
/*
Class:Vector3
Author:Rich Davison
Edited by : Sean Armstrong
*/

#include <cmath>
#include <iostream>

class Vector3	{
public:
	Vector3(void) {
		ToZero();
	}

	Vector3(const float x, const float y, const float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	~Vector3(void){}

	float x;
	float y;
	float z;

	void			Normalise() {
		float length = Length();

		if(length != 0.0f)	{
			length = 1.0f / length;
			x = x * length;
			y = y * length;
			z = z * length;
		}
	}

	Vector3 GetNormalised(){
		Vector3 v = *this;
		return v / v.Length();
	}

	Vector3 unitVector(){
		Vector3 newVector;
		float magnitude = this->Length();
		newVector.x = this->x / magnitude;
		newVector.y = this->y / magnitude;
		newVector.z = this->z / magnitude;
		return newVector;
	}

	void		ToZero() {
		x = y = z = 0.0f;
	}

	float			Length() const {
		return sqrt((x*x)+(y*y)+(z*z));	
	}
	float			SquaredLength() const {
		return (x*x) + (y*y) + (z*z);
	}

	void			Invert() {
		x = -x;
		y = -y;	
		z = -z;	
	}

	float Vector3::distanceBetweenTwoPointsSquared(const Vector3& v) const {
		return (x - v.x) * (x - v.x) + (y - v.y) * (y - v.y) + (z - v.z) * (z - v.z);
	}

	Vector3			Inverse() const{
		return Vector3(-x,-y,-z);
	}

	Vector3			Reverse() const {
		return Vector3(z, y, x);
	}

	static float	Dot(const Vector3 &a, const Vector3 &b) {
		return (a.x*b.x)+(a.y*b.y)+(a.z*b.z);
	}

	static Vector3	Cross(const Vector3 &a, const Vector3 &b) {
		return Vector3((a.y*b.z) - (a.z*b.y) , (a.z*b.x) - (a.x*b.z) , (a.x*b.y) - (a.y*b.x));	
	}

	inline friend std::ostream& operator<<(std::ostream& o, const Vector3& v) {
		o << "Vector3(" << v.x << "," << v.y << "," << v.z <<")" << std::endl;
		return o;
	}

	inline Vector3  operator+(const Vector3  &a) const{
		return Vector3(x + a.x,y + a.y, z + a.z);
	}

	inline Vector3  operator-(const Vector3  &a) const{
		return Vector3(x - a.x,y - a.y, z - a.z);
	}

	inline Vector3  operator-() const{
		return Vector3(-x,-y,-z);
	}

	inline void operator+=(const Vector3  &a){
		x += a.x;
		y += a.y;
		z += a.z;
	}

	inline void operator-=(const Vector3  &a){
		x -= a.x;
		y -= a.y;
		z -= a.z;
	}

	inline Vector3  operator*(const float a) const{
		return Vector3(x * a,y * a, z * a);
	}

	inline Vector3  operator*(const Vector3  &a) const{
		return Vector3(x * a.x,y * a.y, z * a.z);
	}

	inline Vector3  operator/(const Vector3  &a) const{
		return Vector3(x / a.x,y / a.y, z / a.z);
	};

	inline Vector3  operator/(const float v) const{
		return Vector3(x / v,y / v, z / v);
	};

	inline bool	operator==(const Vector3 &A)const {return (A.x == x && A.y == y && A.z == z) ? true : false;};
	inline bool	operator!=(const Vector3 &A)const {return (A.x == x && A.y == y && A.z == z) ? false : true;};
};

