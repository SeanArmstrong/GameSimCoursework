#include "Plane.h"

Plane::Plane(){
	// No
}

Plane::Plane(Vector3& plane, const float& distance){
	/*
	Plane Ax + By + Cz + D = 0
	(A, B, C) is Normal and D is distance

	*/
	Mesh* m = Mesh::GenerateQuad();
	Shader* s = new Shader("assets/shaders/basicvert.glsl", "assets/shaders/textureFrag.glsl");
	ro = new RenderObject(m, s);

	normal = plane.GetNormalised();
	this->distance = distance;

	// TODO: Test this model matrix
	ro->SetModelMatrix(Matrix4::Translation(normal * distance) * Matrix4::Rotation(90, normal.Reverse())
		* Matrix4::Rotation(90, Vector3(1, 0, 0)) * Matrix4::Scale(Vector3(distance, distance, distance)));
	ro->Update(0.0f);
}


Plane::~Plane(){
	delete ro;
}

bool Plane::isColliding(const Sphere& s) const {
	// N dot S + d < r
	// N is normal of plane
	// S is position of center of sphere
	// d is distance 
	return ((Vector3::Dot(normal, s.getPosition()) + distance) < s.getRadius());
}

// TODO: Check distance
void Plane::resolveCollisions(Sphere& s){
	// Get Data
	float penetrationDistance = s.getRadius() - (Vector3::Dot(normal, s.getPosition()) + distance);
	Vector3 normal = -normal;
	s.getRadius() - penetrationDistance;
	Vector3 point = s.getPosition() - normal * (s.getRadius() - penetrationDistance);


}
