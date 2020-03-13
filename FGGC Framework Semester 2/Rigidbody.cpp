#include "Rigidbody.h"

Rigidbody::Rigidbody() {
	Debug::Print("Rigidbody default constructor called. Make sure other constructor is being used after this!");
}

Rigidbody::Rigidbody(float w, float h, float d, ParticleModel* pm) {
	particleModel = pm;
	
	inertiaTensor = CalculateInertiaTensor(w, h, d);
}

void Rigidbody::Update(float deltaTime) {
	torque = CalculateTorque(curForceDir, curPointForceApplied);
	angularAcceleration = CalculateAngularAcceleration();
	angularVelocity = CalculateAngularVelocity(deltaTime);
	angularVelocity = ApplyDamping(deltaTime);
	angularOrientation = CalculateAngularOrientation(particleModel->GetTransform()->GetPosition(), deltaTime);

	particleModel->GetTransform()->SetRotation(angularOrientation);

	if (curForceDir.z != 0) {
		XMFLOAT3 av; XMStoreFloat3(&av, angularVelocity);
		Debug::Print("force: " + std::to_string(curForceDir.x) + ", " + std::to_string(curForceDir.y) + ", " + std::to_string(curForceDir.z) + "\n");
		Debug::Print("veloc: " + std::to_string(av.x) + ", " + std::to_string(av.y) + ", " + std::to_string(av.z) + "\n");
	}

	curForceDir.x *= angularDamping;
	curForceDir.y *= angularDamping;
	curForceDir.z *= angularDamping;
	//curForceDir = XMFLOAT3();
	//curPointForceApplied = XMFLOAT3();
}

XMMATRIX* Rigidbody::GetAngularOrientation() {
	return &angularOrientation;
}

XMVECTOR Rigidbody::CalculateTorque(XMFLOAT3 forceDirection, XMFLOAT3 pointForceApplied) {
	return XMVector3Cross(XMLoadFloat3(&pointForceApplied), XMLoadFloat3(&forceDirection));
}

XMMATRIX Rigidbody::CalculateInertiaTensor(float w, float h, float d) {
	XMFLOAT3X3 matrix = XMFLOAT3X3();

	matrix._11 = 0.0833f * particleModel->GetMass() * (h * h + d * d); // 1/12 * m * (h^2 + d^2)
	matrix._22 = 0.0833f * particleModel->GetMass() * (w * w + d * d); // 1/12 * m * (w^2 + d^2)
	matrix._33 = 0.0833f * particleModel->GetMass() * (w * w + h * h); // 1/12 * m * (w^2 + h^2)

	return XMLoadFloat3x3(&matrix);
}

XMVECTOR Rigidbody::CalculateAngularAcceleration() {
	XMMATRIX inverseMatrix = XMMatrixInverse(&XMMatrixDeterminant(inertiaTensor), inertiaTensor);
	return XMVector3Transform(torque, inverseMatrix);
}

XMVECTOR Rigidbody::CalculateAngularVelocity(float deltaTime) {
	return angularVelocity + angularAcceleration * deltaTime;
}

XMVECTOR Rigidbody::ApplyDamping(float deltaTime) {
	return angularVelocity * angularDamping * deltaTime;
}

XMMATRIX Rigidbody::CalculateAngularOrientation(XMFLOAT3 position, float deltaTime) {
	XMFLOAT3 av; XMStoreFloat3(&av, angularVelocity);
	quaternion.addScaledVector(vector3(av.x, av.y, av.z), deltaTime);

	quaternion.normalise();

	XMMATRIX resultMatrix = XMMATRIX();
	CalculateTransformMatrixColumnMajor(resultMatrix, vector3(position.x, position.y, position.z), quaternion);

	return resultMatrix;
}