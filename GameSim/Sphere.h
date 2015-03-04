/*
* Author: Sean Armstrong
* Class to contain the physical and rendering object of
* a sphere defined by its radius and mass
*/


#pragma once

#include "Vector3.h"
#include "RenderObject.h"
#include "Mesh.h"
#include "SFMLRenderer.h"
#include "Plane.h"
#include <iostream>

class Plane;

class Sphere
{
public:
	Sphere();
	Sphere(const Vector3& pos, const float& radius, float mass = 10, Vector3 force = Vector3(0, 0, 0));
	~Sphere();

	/* Updating */
	void update(const float& msec);
	void checkRestState(const float& msec);
	/* End Updating */

	/* Drawing */
	void draw(SFMLRenderer& renderer, const float& msec) const;
	/* END Drawing */

	/* Getters */
	inline Vector3			getPosition()		  const { return position; }
	inline Vector3			getPreviousPosition() const { return previousPosition; }
	inline float			getSmallestXPoint()   const { return position.x - radius; }
	inline float			getLargestXPoint()	  const { return position.x + radius; }											  
	inline RenderObject*	getRenderObject()	  const { return ro; }											  
	inline float			getMass()			  const { return mass; }
	inline float			getOneOverMass()	  const { return oneovermass; }
	inline float			getRadius()			  const { return radius; }									  
	inline float			getElasticity()		  const { return elasticity; }
	inline float			getRestState()		  const { return atRest; }
	inline Vector3			getAcceleration()	  const { return acceleration; }
	inline Vector3			getGravity()		  const { return gravity; }

	// speed = distance / time 
	inline Vector3 getVelocity(const float& time) const { 
		return (position - previousPosition) / time;
	}
	/* END Getters */


	/* Setters */
	inline void setVelocity(const Vector3& velocity, const float& time){
		this->previousPosition = position - (velocity * time);
	}

	void applyNewForce(Vector3& force);
	void applyGravity(bool status);
	void moveBy(const Vector3& d);
	void setRestState(bool state);
	void setDragFactor(const float& drag);
	/* END Setters */


	/* Collisions */
	bool isColliding(const Sphere& s) const;
	bool isColliding(const Plane& p) const;
	void resolveCollisions(Sphere& s, const float msec);
	/* Collisions */

private:
	Vector3		position;
	Vector3		previousPosition;
	Vector3		acceleration;
	Vector3		gravity;

	float		mass;
	float		oneovermass;
	float		radius;
	float		elasticity;
	float		dragFactor;

	int			framesAtRest;
	float		averageDistance;
	bool		atRest;


	// Graphical Representation
	RenderObject* ro;

};