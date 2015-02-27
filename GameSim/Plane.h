#pragma once
#include "Vector3.h"
#include "RenderObject.h"
#include "SFMLRenderer.h"
#include "Sphere.h"

class Sphere;

class Plane
{
public:
	Plane(const Vector3& plane, const Vector3& a, const Vector3& b, const Vector3& c, const Vector3& d, const float& distance);
	~Plane();

	inline void update(const float& msec){
		if (rotating){
			rotatePlanes();
			ro->Update(msec);
		}
	}
	inline void draw(SFMLRenderer& renderer) const { renderer.Render(*ro); }

	inline void rotatePlanes(){
		Vector3 unitVector = normal.unitVector();
		Matrix4 mat = Matrix4::Rotation(0.1f, Vector3(1,0,1));
		//Matrix4 mat = Matrix4::Rotation(0.1f, rotatingAxis);
		Vector3 resultnorm = mat * normal;
		//Vector3 resultnorm = (mat * normal).unitVector();
		normal = resultnorm;
		ro->SetModelMatrix(ro->GetModelMatrix() * mat);
	}

	inline float getElasticity() const { return elasticity; }
	inline float getDistance() const { return distance; }
	inline RenderObject* getRenderObject() { return ro; }
	inline Vector3 getNormal() const { return normal; }
	inline bool isRotating() const { return rotating; }
	inline Vector3 getRotatingAxis() const{ return rotatingAxis; }


	inline void setNormal(const Vector3& v){ normal = v; }

	void setRotatingAxis(const Vector3& axis);

	bool isColliding(const Sphere& s) const;
	void resolveCollisions(Sphere& s, const float msec);

private:
	Plane(){}

	Vector3 normal;
	float distance;
	float elasticity; // Friction Sound Heat effect

	bool rotating;
	Vector3 rotatingAxis;

	RenderObject *ro;
};

