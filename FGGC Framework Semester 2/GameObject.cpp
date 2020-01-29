#include "GameObject.h"

GameObject::GameObject(string type, Mesh mesh, Material material) {
	_parent = nullptr;
	_textureRV = nullptr;
	_type = type;

	_appearance.SetMesh(mesh);
	_appearance.SetMaterial(material);

	_particleModel.SetVelocity(1.0f, 0.0f, 0.0f);
	_particleModel.SetAcceleration(2.0f, 0.0f, 0.0f);
}

GameObject::~GameObject() {
}

void GameObject::Update(float t) {
	_transform.Update(t);

	if (_type == "Cube 0")
		_particleModel.MoveConstAcceleration(t, &_transform);

	if (_parent != nullptr){
		XMStoreFloat4x4(_transform.GetWorldFloat4X4(), this->_transform.GetWorldMatrix() * _parent->_transform.GetWorldMatrix());
	}

	if(_type.find("Cube") != std::string::npos)
		Debug::Print(std::to_string(t) + "\n");
}

void GameObject::Draw(ID3D11DeviceContext * pImmediateContext) {
	// NOTE: We are assuming that the constant buffers and all other draw setup has already taken place

	// Set vertex and index buffers
	pImmediateContext->IASetVertexBuffers(0, 1, &_appearance.GetMesh()->vertexBuffer, &_appearance.GetMesh()->vertexBufferStride, &_appearance.GetMesh()->vertexBufferOffset);
	pImmediateContext->IASetIndexBuffer(_appearance.GetMesh()->indexBuffer, DXGI_FORMAT_R16_UINT, 0);

	pImmediateContext->DrawIndexed(_appearance.GetMesh()->numberOfIndices, 0, 0);
}
