#include "SceneLoader.h"

std::vector<GameObject*> SceneLoader::LoadFromFile(std::string fileDir, ID3D11Device* pd3dDevice) {
	std::ifstream inFile;
	inFile.open(fileDir);
	if (!inFile.is_open())
		return std::vector<GameObject*>();

	std::vector<GameObject*> out;

	std::stringstream ss;
	ss << inFile.rdbuf();		//https://stackoverflow.com/questions/2602013/read-whole-ascii-file-into-c-stdstring
	
	json j = json::parse(ss.str());
	CreateObjectInScene(nullptr, j["0"], out, pd3dDevice);

	return out;
}

void SceneLoader::CreateObjectInScene(GameObject* parent, json j, std::vector<GameObject*>& goArray, ID3D11Device* pd3dDevice) {
	GameObject* go;
	json obj = j;	//Create a copy to use for GameObject creation. Checking if elements exist creates the element which we don't want in the original

	if (obj["Type"] == "GameObject") {
		go = new GameObject(obj["ModelDirectory"],
							obj["Material"] == nullptr ? Material() : Material(XMFLOAT4(obj["Material"]["Diffuse"]["x"], obj["Material"]["Diffuse"]["y"], obj["Material"]["Diffuse"]["z"], obj["Material"]["Diffuse"]["w"]),
																				XMFLOAT4(obj["Material"]["Ambient"]["x"], obj["Material"]["Ambient"]["y"], obj["Material"]["Ambient"]["z"], obj["Material"]["Ambient"]["w"]),
																				XMFLOAT4(obj["Material"]["Specular"]["x"], obj["Material"]["Specular"]["y"], obj["Material"]["Specular"]["z"], obj["Material"]["Specular"]["w"]),
																				obj["Material"]["SpecularPower"]), 
							pd3dDevice);	//GameObject constructor

		go->GetTransform()->SetPosition(obj["Position"] == nullptr ? XMFLOAT3() : XMFLOAT3(obj["Position"]["x"], obj["Position"]["y"], obj["Position"]["z"]));	//Set position from file
		go->GetTransform()->SetRotation(obj["Rotation"] == nullptr ? XMFLOAT3() : XMFLOAT3(obj["Rotation"]["x"], obj["Rotation"]["y"], obj["Rotation"]["z"]));	//Set rotation from file
		go->GetTransform()->SetScale(obj["Scale"] == nullptr ? XMFLOAT3(1, 1, 1) : XMFLOAT3(obj["Scale"]["x"], obj["Scale"]["y"], obj["Scale"]["z"]));			//Set scale from file

		ID3D11ShaderResourceView* rv;	//Load texture from address
		std::string texDir = obj["TextureDirectory"];
		texDir = "Resources/" + texDir;
		CreateDDSTextureFromFile(pd3dDevice, StringToWstring(texDir).c_str(), nullptr, &rv);
		go->SetTextureRV(rv);

		go->SetParent(parent);			//Set parent object
	} else if (obj["Type"] == "GameObject_Plane") {
		return;
	}

	goArray.push_back(go);

	for (auto& x : j.items()) {
		std::string key = x.key();
		//TODO: IMPROVE THE UGLY LINE BELOW 
		if (key != "Type" && key != "TextureDirectory" && key != "ModelDirectory" && key != "PlaneWidth" && key != "PlaneHeight" && key != "Position" && key != "Rotation" && key != "Scale" && key != "ShaderType" && key != "Material") {	//If is not GameObject property
			CreateObjectInScene(go, j[key], goArray, pd3dDevice);
		}
	}
}

std::wstring SceneLoader::StringToWstring(std::string s) {
	return std::wstring(s.begin(), s.end());
}
