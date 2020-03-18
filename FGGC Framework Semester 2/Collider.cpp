#include "Collider.h"

Collider::Collider() {
}

bool Collider::CheckCollision(float r1, float r2) {
	return false;
}

bool Collider::CheckCollision(float r, Box3D b) {
	return false;
}

bool Collider::CheckCollision(Box3D b1, Box3D b2) {
	return false;
}
