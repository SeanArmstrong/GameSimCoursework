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
	Plane(Vector3& plane, const float& distance);
	~Plane();

	inline void draw(SFMLRenderer& renderer) const {
		renderer.Render(*ro);
	}

	bool isColliding(const Sphere& s) const;
	void resolveCollisions(Sphere& s);

private:
	Vector3 normal;
	float distance;

	RenderObject *ro;
};

