#pragma once

#include "Object.h"

class ObjectLoader
{
public:
	ObjectLoader();
	~ObjectLoader();

	void print();
	Object ReadObjectGeometry(const char* Filename);
	Object object;

};

