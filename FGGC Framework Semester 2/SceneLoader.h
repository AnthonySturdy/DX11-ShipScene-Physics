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

using json = nlohmann::json;

class SceneLoader {
public:
	static void LoadFromFile(std::string fileDir);
	static void CreateObjectInScene(GameObject* parent, json j, ID3D11Device* pd3dDevice);

private:
	static std::wstring StringToWstring(std::string s);
};