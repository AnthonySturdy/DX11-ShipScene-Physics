#include "Collider.h"

Collider::Collider() {
}

//Calls appropriate collision check
bool Collider::CheckCollision(XMFLOAT3 pos1, Collider* c1, XMFLOAT3 pos2, Collider* c2) {
	bool isFirstSphere = c1->GetRadius() != 0;
	bool isSecondSphere = c2->GetRadius() != 0;
	
	if (isFirstSphere && isSecondSphere)			//Sphere vs Sphere
		return CheckCollision(pos1, c1->GetRadius(), pos2, c2->GetRadius());
	else if (!isFirstSphere && isSecondSphere)		//AABB vs Sphere
		return CheckCollision(pos1, c1->GetBoundingBox(), pos2, c2->GetRadius());
	else if (isFirstSphere && !isSecondSphere)		//Sphere vs AABB
		return CheckCollision(pos1, c1->GetRadius(), pos2, c2->GetBoundingBox());
	else											//AABB vs AABB
		return CheckCollision(pos1, c1->GetBoundingBox(), pos2, c2->GetBoundingBox());
}

//Sphere vs Sphere collision
bool Collider::CheckCollision(XMFLOAT3 pos1, float r1, XMFLOAT3 pos2, float r2) {
	//Distance between both objects
	float dist = sqrt((pos1.x - pos2.x) * (pos1.x - pos2.x) +
						(pos1.y - pos2.y) * (pos1.y - pos2.y) +
						(pos1.z - pos2.z) * (pos1.z - pos2.z));

	//Collision if distance is less than the sum of the radii
	return dist < (r1 + r2);
}

//Sphere vs AABB collision
bool Collider::CheckCollision(XMFLOAT3 pos1, float r, XMFLOAT3 pos2, Box3D b) {
	//Min / Max values of box
	XMFLOAT3 bMin = { pos2.x - (b.w / 2), pos2.y - (b.h / 2), pos2.z - (b.d / 2) };
	XMFLOAT3 bMax = { pos2.x + (b.w / 2), pos2.y + (b.h / 2), pos2.z + (b.d / 2) };

	//Get box's closest point to sphere centre
	float x = max(bMin.x, min(pos1.x, bMax.x));
	float y = max(bMin.y, min(pos1.y, bMax.y));
	float z = max(bMin.z, min(pos1.z, bMax.z));

	//Distance between box closest point and sphere centre
	float dist = sqrt((x - pos1.x) * (x - pos1.x) +
						(y - pos1.y) * (y - pos1.y) +
						(z - pos1.z) * (z - pos1.z));

	return dist < r;
}

//AABB vs AABB collision
bool Collider::CheckCollision(XMFLOAT3 pos1, Box3D b1, XMFLOAT3 pos2, Box3D b2) {
	//Min / Max values
	XMFLOAT3 b1Min = { pos1.x - (b1.w / 2), pos1.y - (b1.h / 2), pos1.z - (b1.d / 2) };
	XMFLOAT3 b2Min = { pos2.x - (b2.w / 2), pos2.y - (b2.h / 2), pos2.z - (b2.d / 2) };
	XMFLOAT3 b1Max = { pos1.x + (b1.w / 2), pos1.y + (b1.h / 2), pos1.z + (b1.d / 2) };
	XMFLOAT3 b2Max = { pos2.x + (b2.w / 2), pos2.y + (b2.h / 2), pos2.z + (b2.d / 2) };

	//3D overlap check
	return ((b1Min.x <= b2Max.x && b1Max.x >= b2Min.x) &&
			(b1Min.y <= b2Max.y && b1Max.y >= b2Min.y) &&
			(b1Min.z <= b2Max.z && b1Max.z >= b2Min.z));
}