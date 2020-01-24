#include "GameObject.h"

GameObject::GameObject(string type, Mesh geometry, Material material) : _geometry(geometry), _type(type), _material(material)
{
	_parent = nullptr;

	_textureRV = nullptr;
}

GameObject::~GameObject()
{
}

void GameObject::Update(float t)
{
	_transform.Update(t);

	if (_parent != nullptr){
		XMStoreFloat4x4(_transform.GetWorldFloat4X4(), this->_transform.GetWorldMatrix() * _parent->_transform.GetWorldMatrix());
	} else {

	}

	if(_type.find("Cube") != std::string::npos)
		Debug::Print(std::to_string(t) + "\n");
}

void GameObject::Draw(ID3D11DeviceContext * pImmediateContext)
{
	// NOTE: We are assuming that the constant buffers and all other draw setup has already taken place

	// Set vertex and index buffers
	pImmediateContext->IASetVertexBuffers(0, 1, &_geometry.vertexBuffer, &_geometry.vertexBufferStride, &_geometry.vertexBufferOffset);
	pImmediateContext->IASetIndexBuffer(_geometry.indexBuffer, DXGI_FORMAT_R16_UINT, 0);

	pImmediateContext->DrawIndexed(_geometry.numberOfIndices, 0, 0);
}
