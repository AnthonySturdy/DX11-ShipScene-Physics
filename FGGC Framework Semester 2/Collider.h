#pragma once
#include "Structures.h"

class Collider {
private:
	Box3D box;
	float r;

public:
	Collider();

	inline Box3D GetBoundingBox() const { return box; }
	inline float GetRadius() const { return r; }

	inline void SetBoundingBox(Box3D b) { box = b; }
	inline void SetRadius(float radius) { r = radius; }

	static bool CheckCollision(float r1, float r2); //Sphere vs Sphere 
	static bool CheckCollision(float r, Box3D b);	//Sphere vs Box 
	static bool CheckCollision(Box3D b, float r) { CheckCollision(r, b); }	//Calls above function
	static bool CheckCollision(Box3D b1, Box3D b2); //Box vs Box 
};