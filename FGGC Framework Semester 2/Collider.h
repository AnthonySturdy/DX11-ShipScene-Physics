#pragma once
#include <directxmath.h>
#include "Structures.h"

//JavaScript collision solutions referenced: https://developer.mozilla.org/en-US/docs/Games/Techniques/3D_collision_detection

class Collider {
private:
	Box3D box;
	float r = 0.0f;

	static bool CheckCollision(XMFLOAT3 pos1, float r1, XMFLOAT3 pos2, float r2); //Sphere vs Sphere 
	static bool CheckCollision(XMFLOAT3 pos1, float r, XMFLOAT3 pos2, Box3D b);	//Sphere vs Box 
	static bool CheckCollision(XMFLOAT3 pos1, Box3D b, XMFLOAT3 pos2, float r) { return CheckCollision(pos2, r, pos1, b); }	//Calls above function
	static bool CheckCollision(XMFLOAT3 pos1, Box3D b1, XMFLOAT3 pos2, Box3D b2); //Box vs Box 

public:
	Collider();

	inline Box3D GetBoundingBox() const { return box; }
	inline float GetRadius() const { return r; }

	inline void SetBoundingBox(Box3D b) { box = b; }
	inline void SetRadius(float radius) { r = radius; }

	static bool CheckCollision(XMFLOAT3 pos1, Collider* c1, XMFLOAT3 pos2, Collider* c2);
};