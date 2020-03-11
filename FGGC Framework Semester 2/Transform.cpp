#include "Transform.h"

Transform::Transform() {
	_position = XMFLOAT3();
	_rotation = XMMATRIX();
	_scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
}

void Transform::Update(float t) {
	XMMATRIX scale = XMMatrixScaling(_scale.x, _scale.y, _scale.z);
	XMMATRIX rotation = _rotation;
	XMMATRIX translation = XMMatrixTranslation(_position.x, _position.y, _position.z);
	
	// Calculate world matrix
	XMStoreFloat4x4(&_world, scale * rotation * translation);
}
