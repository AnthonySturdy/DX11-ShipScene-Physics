#pragma once

#include <windows.h>
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <directxcolors.h>
#include <vector>
#include "DDSTextureLoader.h"
#include "resource.h"
#include "Camera.h"
#include "ParticleSystem.h"
#include "SceneLoader.h"
#include "Shader.h"
/*
//#include <SpriteFont.h>
#include "CommonStates.h"
//#include "DDSTextureLoader.h"
#include "Effects.h"
#include "GeometricPrimitive.h"
#include "Model.h"
#include "PrimitiveBatch.h"
#include "ScreenGrab.h"
#include "SpriteBatch.h"
#include "SpriteFont.h"
#include "VertexTypes.h"
*/
#include "GameObject.h"
#include "Debug.h"
#include "Transform.h"
#include "Structures.h"

using namespace DirectX;

#define NUM_OF_CUBES 5
#define FPS_60 1.0f/60.0f

class Application
{
private:
	HINSTANCE               _hInst;
	HWND                    _hWnd;
	D3D_DRIVER_TYPE         _driverType;
	D3D_FEATURE_LEVEL       _featureLevel;
	ID3D11Device*           _pd3dDevice;
	ID3D11DeviceContext*    _pImmediateContext;
	IDXGISwapChain*         _pSwapChain;
	ID3D11RenderTargetView* _pRenderTargetView;
	ID3D11BlendState*		_transparency;
	ID3D11VertexShader*     _pVertexShader;
	ID3D11PixelShader*      _pPixelShader;
	ID3D11InputLayout*      _pVertexLayout;

	ID3D11Buffer*           _pConstantBuffer;

	ID3D11DepthStencilView* _depthStencilView = nullptr;
	ID3D11Texture2D* _depthStencilBuffer = nullptr;

	ID3D11ShaderResourceView* _errorTextureRV = nullptr;
	ID3D11SamplerState* _pSamplerLinear = nullptr;

	Light basicLight;
	float globalTime = 0;

	std::vector<GameObject*> _gameObjects;
	std::vector<Shader*> shaders;

	ParticleSystem* particleSystem;

	Camera * _camera;
	float _cameraOrbitRadius = 7.0f;
	float _cameraOrbitRadiusMin = 1.0f;
	float _cameraOrbitRadiusMax = 500.0f;
	float _cameraOrbitAngleXZ = -90.0f;
	float _cameraSpeed = 4.0f;

	UINT _WindowHeight;
	UINT _WindowWidth;

	// Render dimensions - Change here to alter screen resolution
	UINT _renderHeight = 1080;
	UINT _renderWidth = 1920;

	ID3D11DepthStencilState* DSLessEqual;
	ID3D11RasterizerState* RSCullNone;

	ID3D11RasterizerState* CCWcullMode;
	ID3D11RasterizerState* CWcullMode;


	bool KeyOneIsPressed = false;

private:
	HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow);
	HRESULT InitDevice();
	void Cleanup();
	HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);
	HRESULT InitShadersAndInputLayout();

public:
	Application();
	~Application();

	HRESULT Initialise(HINSTANCE hInstance, int nCmdShow);

	bool HandleKeyboard(MSG msg);

	void Update();
	void Draw();
};

