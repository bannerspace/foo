#pragma once

#include "Object.h"
#include "TextureLoader.h"

class ObjectLoader
{
public:
	ObjectLoader();
	~ObjectLoader();

	Object ReadObjectGeometry(const char* Filename);
	Object object;


private:
	string replaceSpaces(string temp);
};

