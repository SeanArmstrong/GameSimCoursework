#pragma once
#include "Vector3.h"
#include "RenderObject.h"
#include "SFMLRenderer.h"
#include "Sphere.h"

class Sphere;

class Plane
{
public:
	Plane();
	Plane(Vector3& plane, Vector3 a, Vector3 b, Vector3 c, Vector3 d, const float& distance);
	~Plane();

	inline void draw(SFMLRenderer& renderer) const {
		renderer.Render(*ro);
	}

	inline float getElasticity() const { return elasticity; }
	inline float getDistance() const { return distance; }
	RenderObject* getRenderObject() { return ro; }
	inline Vector3 getNormal() const { return normal; }
	inline void setNormal(Vector3 v){
		normal = v;
	}


	bool isColliding(const Sphere& s) const;
	void resolveCollisions(Sphere& s, const float msec);

private:
	Vector3 normal;
	float distance;
	float elasticity; // Friction Sound Heat effect

	RenderObject *ro;
};

