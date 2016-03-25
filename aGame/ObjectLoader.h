#pragma once

#include "Object.h"
#include "TextureLoader.h"

class ObjectLoader
{
	TextureLoader textureLoader;
public:
	ObjectLoader();
	~ObjectLoader();

	Object *ReadObjectGeometry(const char* Filename);
	Object *object;

};

