#include "PhysicsEngine.h"


PhysicsEngine::PhysicsEngine(){
}


PhysicsEngine::~PhysicsEngine(){
}

Sphere* PhysicsEngine::addSphere(const Vector3& pos, const float& radius, float mass, Vector3 force){
	Sphere* s = new Sphere(pos, radius, mass, force);
	spheres.push_back(s);
	//sortSpheres();
	return s;
}

Plane* PhysicsEngine::addPlane(Vector3& plane, Vector3 a, Vector3 b, Vector3 c, Vector3 d, const float& distance){
	Plane* p = new Plane(plane, a, b, c, d, distance);
	planes.push_back(p);

	return p;
}

/*
* Sorts spheres in the x axis by their smallest point
* caculated by center.x - radius
* Uses insertion sort due to its efficency over almost
* sorted data
*/
void PhysicsEngine::sortSpheres(){
	int j;
	Sphere* val;

	//iterate through entire list
	for (int i = 1; i < spheres.size(); i++){
		val = spheres[i];
		j = i - 1;

		while (j >= 0 && spheres[j]->getSmallestXPoint() > val->getSmallestXPoint()){
			spheres[j + 1] = spheres[j];
			j = j - 1;
		}//end while
		spheres[j + 1] = val;
	}//end for

	//Prints the sorted list
	//for (int i = 0; i < spheres.size(); i++)
		//cout << spheres[i]->getSmallestXPoint() << std::endl << std::endl;


}


/*void PhysicsEngine::rotatePlanes(){
	std::vector<Plane*>::const_iterator ip;
	for (ip = planes.begin(); ip < planes.end(); ++ip) {
		// Unit vector = normal / magintude
		Vector3 normal = (**ip).getNormal();
		float distance = (**ip).getDistance();
		Vector3 unitVectorNormal = normal.unitVector();

		// Unit Vector * distance = point on plane
		Vector3 point = unitVectorNormal * distance;
		Matrix4 mat;
		mat.SetPositionVector(point);

		// New point
		// Rotation matrix * (point - translation to origin) + translation again
		Matrix4 rotation = Matrix4::Rotation(1, Vector3(0, 0, 1));
		Matrix4 translation = Matrix4::Translation(normal * distance);
		Matrix4 translation2 = Matrix4::Translation(normal * -distance);
		//normal.Inverse();

		Matrix4 point2 = ((mat * translation) * rotation) * translation2;
		Matrix4 point3 = translation2 * (rotation * (mat * translation));


	}
}*/

void PhysicsEngine::rotatePlanes(){
	/*std::vector<Plane*>::const_iterator ip;
	for (ip = planes.begin(); ip < planes.end(); ++ip) {
		Vector3 norm = (**ip).getNormal();
		Vector3 unitVector = norm.unitVector();
		Quaternion quat = Quaternion::AxisAngleToQuaterion(Vector3(1, 0, 0), 0.5f);

		Matrix4 mat = quat.ToMatrix();

		Vector3 resultnorm = mat * unitVector;

		float distance = (**ip).getDistance();
		(**ip).setNormal(resultnorm);

		//(**ip).getRenderObject()->SetModelMatrix((**ip).getRenderObject()->GetModelMatrix() * Matrix4::Translation(Vector3(norm * distance)));
		//(**ip).getRenderObject()->SetModelMatrix((**ip).getRenderObject()->GetModelMatrix() * mat);

		//(**ip).getRenderObject()->SetModelMatrix((**ip).getRenderObject()->GetModelMatrix() * Matrix4::Translation(Vector3(norm * -distance)));

		(**ip).getRenderObject()->SetModelMatrix(Matrix4::Translation(resultnorm * distance) * Matrix4::Rotation(90, resultnorm.Reverse())
			* Matrix4::Rotation(90, Vector3(1, 0, 0)) * Matrix4::Scale(Vector3(distance, distance, distance)));

		(**ip).getRenderObject()->Update(0.0f);
		
	}*/
}

/*void PhysicsEngine::rotatePlanes(){
	std::vector<Plane*>::const_iterator ip;
	for (ip = planes.begin(); ip < planes.end(); ++ip) {
		// Get point
		Vector3 point = (**ip).getNormal() * (**ip).getDistance();
		Matrix4 mat;
		mat.SetPositionVector(point);
		mat = mat * Matrix4::Rotation(1, Vector3(0, 0, 1));
		point = mat.GetPositionVector();
		(**ip).setNormal(point.GetNormalised());
	}
}*/
/*Vector3 RotatePointAroundPivot(Vector3 point, Vector3 pivot, Vector3 angle){
	Vector3 direction = point - pivot; // get point direction relative to pivot
	direction = Quaternion::Euler(angle) * direction; // rotate it
	point = direction + pivot; // calculate rotated point
	return point; // return it
}*/

void PhysicsEngine::applyGravity(){
	std::vector<Sphere*>::iterator it;
	for (it = spheres.begin(); it < spheres.end(); ++it) {
		(**it).applyNewForce(Vector3(0, -9.81f, 0));
	}
}

void  PhysicsEngine::applyUpwardsForce(){
	std::vector<Sphere*>::iterator it;
	for (it = spheres.begin(); it < spheres.end(); ++it) {
		(**it).applyNewForce(Vector3(0, 5000.0f, 0));
	}
}

void PhysicsEngine::removeAcclerationFromAllSpheres(){
	std::vector<Sphere*>::iterator it;
	for (it = spheres.begin(); it < spheres.end(); ++it) {
		(**it).applyNewForce(Vector3(0, 0, 0));
	}
}

void PhysicsEngine::setDragSphereFactor(const float& drag){
	std::vector<Sphere*>::iterator it;
	for (it = spheres.begin(); it < spheres.end(); ++it) {
		(**it).setDragFactor(drag);
	}
}