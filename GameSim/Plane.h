/* 
* Author: Sean Armstrong
* Class to contain the physical and rendering object of
* a plane. A plane is defined by its normal and distance
*/

#pragma once
#include "Vector3.h"
#include "RenderObject.h"
#include "SFMLRenderer.h"
#include "Sphere.h"
#include <sfml\Window.hpp>

class Sphere;

class Plane
{
public:
	Plane(const Vector3& plane, const Vector3& a, const Vector3& b, const Vector3& c, const Vector3& d, const float& distance);
	~Plane();

	/* Updating */
	void update(const float& msec);
	void rotatePlanes(Matrix4 mat, const float& msec);
	/* End Updating */

	/* Drawing */

	inline void draw(SFMLRenderer& renderer) const { renderer.Render(*ro); }

	/* End Drawing */

	/* Getters */

	inline float			getElasticity()		const { return elasticity; }
	inline float			getDistance()		const { return distance; }
	inline RenderObject*	getRenderObject()	const { return ro; }
	inline Vector3			getNormal()			const { return normal; }
	inline bool				isRotating()		const { return rotating; }
	inline Vector3			getRotatingAxis()	const { return rotatingAxis; }
	/* End Getters */

	/* Setters */

	inline void setNormal(const Vector3& v){ normal = v; }
	/* End Setters */

	/* Collision */

	bool isColliding(const Sphere& s) const;
	void resolveCollisions(Sphere& s, const float msec);

	/* End Collision */

private:
	Plane(){}

	Vector3 normal;
	float distance;
	float elasticity; // Friction Sound Heat effect

	bool rotating;
	Vector3 rotatingAxis;

	RenderObject *ro;
};

