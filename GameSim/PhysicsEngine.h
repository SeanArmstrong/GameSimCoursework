#pragma once

#include <vector>
#include "Sphere.h"

class PhysicsEngine
{
public:
	PhysicsEngine();
	~PhysicsEngine();

	inline void update(const float& msec){
		std::vector<Sphere>::iterator it;
		for (it = spheres.begin(); it < spheres.end(); ++it) {
			it->update(msec);
		}
	}

	inline void draw(SFMLRenderer& renderer, const float& msec){
		std::vector<Sphere>::iterator it;
		for (it = spheres.begin(); it < spheres.end(); ++it) {
			it->draw(renderer, msec);
		}
	}

	void addSphere(const Sphere& s);

private:

	std::vector<Sphere> spheres;
};

