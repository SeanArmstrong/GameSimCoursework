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

	// Getters
	inline Vector3	getPosition() const { return position; }
	inline Vector3	getPreviousPosition() const { return previousPosition; }
	inline float	getX() const { return position.x; }
	inline float	getY() const { return position.y; }
	inline float	getZ() const { return position.z; }
	inline float	getSmallestXPoint() const { return position.x - radius; }
	inline float	getLargestXPoint() const { return position.x + radius; }
	inline RenderObject* getRenderObject() const { return ro; }
	
	inline float getMass() const { return mass; }
	inline float getOneOverMass() const { return oneovermass; }
	inline Vector3 getAcceleration() const { return acceleration; }

	inline float getRadius() const { return radius; }
	inline float getElasticity() const { return elasticity; }
	inline float getRestState() const { return atRest; }

	// speed = distance / time 
	inline Vector3 getVelocity(const float& time) const { 
		return (position - previousPosition) / time;
	}

	// Setters
	inline void applyNewForce(Vector3& force){
		acceleration = force / mass;
	}
	inline void setVelocity(const Vector3& velocity, const float& time){
		this->previousPosition = position - (velocity * time);
	}
	inline void moveBy(const Vector3& d){
		position = position + d;
		previousPosition = previousPosition + d;
	}
	
	void setDragFactor(const float& drag);

	// Sphere Sphere Collision
	bool isColliding(const Sphere& s) const;
	// Sphere Plane Collision
	bool isColliding(const Plane& p) const;

	inline void update(const float& msec){
		if (!atRest){
			Vector3 temp = position;
			position += (position - previousPosition) + (acceleration * msec * msec);// *dragFactor;
			previousPosition = temp;
			checkRestState(msec);
		}
	}

	inline void checkRestState(const float& msec){
		if (getVelocity(msec).SquaredLength() < 0.00001f && acceleration.SquaredLength() == 0.0f){
			atRest = true;
		}
	}

	inline void draw(SFMLRenderer& renderer, const float& msec) const {
		// Need to update model matrix of render object?
		ro->SetModelMatrix(Matrix4::Translation(position) * Matrix4::Scale(Vector3(radius, radius, radius)));
		ro->Update(msec);
		renderer.Render(*ro);
	}

	void resolveCollisions(Sphere& s, const float msec);

private:
	Vector3		position;
	Vector3		previousPosition;
	Vector3		acceleration;
	float		mass;
	float		oneovermass;
	float		radius;
	float		elasticity;
	float		dragFactor;
	bool		atRest;


	// Graphical Representation
	RenderObject* ro;

};