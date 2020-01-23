#include "Debug.h"

void Debug::Print(std::string str) {
	OutputDebugStringA(str.c_str());
}
