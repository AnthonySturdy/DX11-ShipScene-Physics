#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "Structures.h"
#include "GameObject.h"
//#include "GameObject_Plane.h"
#include "vector3.h"
#include "json.hpp"	//https://github.com/nlohmann/json
#include "DDSTextureLoader.h"

using json = nlohmann::json;

class SceneLoader {
public:
	static std::vector<GameObject*> LoadFromFile(std::string fileDir, ID3D11Device* pd3dDevice);

private:
	static void CreateObjectInScene(GameObject* parent, json j, std::vector<GameObject*>& goArray, ID3D11Device* pd3dDevice);
	static std::wstring StringToWstring(std::string s);
};