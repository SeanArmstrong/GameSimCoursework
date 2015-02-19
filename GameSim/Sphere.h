#pragma once

#include "Vector3.h"
#include "RenderObject.h"
#include "Mesh.h"
#include "SFMLRenderer.h"

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
	inline RenderObject getRenderObject() const { return ro; }
	
	inline float getMass() const { return mass; }
	inline Vector3 getAcceleration() const { return acceleration; }

	// speed = distance / time 
	//inline Vector3 getVelocity(const float& time) const { return position - previousPosition / time; }

	// Setters
	inline void applyNewForce(Vector3& force){
		acceleration = force / mass;
	}

	// Sphere Sphere Collision
	bool isColliding(const Sphere& s) const;

	inline void update(const float& msec){
		// Verlet Integration
		// std::cout << "Position: " << position << std::endl;
		// std::cout << "Position - prev: " << position - previousPosition << std::endl;
		// std::cout << "Acc: " << acceleration << std::endl;
		// std::cout << "msec: " << msec << std::endl;
		// std::cout << "acceleration * t * t: " << acceleration * msec * msec << std::endl;

		position = position + (position - previousPosition) + (acceleration * msec * msec);
	}

	inline void draw(SFMLRenderer& renderer, const float& msec){
		// Need to update model matrix of render object?
		ro.SetModelMatrix(Matrix4::Translation(position));
		renderer.UpdateScene(msec);
	}

private:
	Vector3		position;
	Vector3		previousPosition;
	Vector3		acceleration;
	float		mass;
	float		radius;

	// Graphical Representation
	RenderObject ro;

};

