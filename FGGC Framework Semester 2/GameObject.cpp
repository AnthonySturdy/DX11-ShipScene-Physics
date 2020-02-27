#include "GameObject.h"

GameObject::GameObject(std::string modelDirectory, Material material, ID3D11Device* _pd3dDevice) {
	_parent = nullptr;
	_textureRV = nullptr;
	pd3dDevice = _pd3dDevice;

	if(modelDirectory != "")	//Plane child class passes "" as model directory, so the plane isn't overridden.
		_appearance.LoadMesh("Resources/" + modelDirectory, pd3dDevice);
	_appearance.SetMaterial(material);
	_particleModel.SetTransform(&_transform);
}

GameObject::GameObject(Mesh mesh, Material material, ID3D11Device* _pd3dDevice) {
	_parent = nullptr;
	_textureRV = nullptr;
	pd3dDevice = _pd3dDevice;

	_appearance.SetMesh(mesh);
	_appearance.SetMaterial(material);

	_particleModel.SetTransform(&_transform);
}

GameObject::~GameObject() {
}

void GameObject::Update(float t) {
	if (!isActive)
		return;

	_transform.Update(t);
	if(!isStatic)
		_particleModel.Update(t);

	if (_parent != nullptr){	//Update World Matrix based on parent's World Matrix
		XMStoreFloat4x4(_transform.GetWorldFloat4X4(), this->_transform.GetWorldMatrix() * _parent->_transform.GetWorldMatrix());
	}
}

void GameObject::Draw(ID3D11DeviceContext* pImmediateContext) {
	if (!isActive)
		return;

	// Set vertex and index buffers
	pImmediateContext->IASetVertexBuffers(0, 1, &_appearance.GetMesh()->VertexBuffer, &_appearance.GetMesh()->VBStride, &_appearance.GetMesh()->VBOffset);
	pImmediateContext->IASetIndexBuffer(_appearance.GetMesh()->IndexBuffer, DXGI_FORMAT_R16_UINT, 0);

	pImmediateContext->DrawIndexed(_appearance.GetMesh()->IndexCount, 0, 0);
}
