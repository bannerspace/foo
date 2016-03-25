#include "Player.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>
#include <algorithm>

Player::Player()
{	
	try
	{
		position = { { 0., 0., 0. }, 0., -1, 0, 0 };
		scale = 1.0f;
		//playerState = PlayerState::ALIVE;
		camera = new Camera();
		if (!camera)
			throw "Can't create player's camera object";

		ObjectLoader loader;
		object = loader.ReadObjectGeometry("E:\\Users\\Banner\\Desktop\\aGame\\aGame\\resources\\objects\\Captain America");

		if (!object)
		{
			throw "Can't load player's geometry";
		}
		boundingBox.isShowing = false;
		CalculateSize();
	}
	catch (const char* error)
	{
		object = NULL;
		std::cout << error << std::endl;
	}

}

Player::~Player()
{
}


void Player::CalculateSize()
{
	//x.push_back(object->vertex[0].x);
	float xMax = object->vertex[0].x;
	float xMin = xMax;

	float yMax = object->vertex[0].y;
	float yMin = yMax;

	float zMax = object->vertex[0].z;
	float zMin = zMax;
	//boundingBox.width = max_element(std::begin(object->vertex))
	for (int i = 0; i < object->vertex.size(); i++)
	{
		if (xMax < object->vertex[i].x)
			xMax = object->vertex[i].x;
		if (xMin > object->vertex[i].x)
			xMin = object->vertex[i].x;

		if (yMax < object->vertex[i].y)
			yMax = object->vertex[i].y;
		if (yMin > object->vertex[i].y)
			yMin = object->vertex[i].y;

		if (zMax < object->vertex[i].z)
			zMax = object->vertex[i].z;
		if (zMin > object->vertex[i].z)
			zMin = object->vertex[i].z;
	}

	boundingBox.width = abs(xMax - xMin);
	boundingBox.height = abs(yMax - yMin);
	boundingBox.depth = abs(zMax - zMin);

	boundingBox.x = xMin;
	boundingBox.y = yMin;
	boundingBox.z = zMin;

	boundingBox.coords[0].x = 0;
	boundingBox.coords[0].y = 0;
	boundingBox.coords[0].z = 0;

	boundingBox.coords[0].x = 0;
	boundingBox.coords[0].y = 0;
	boundingBox.coords[0].z = 0;

	boundingBox.coords[0].x = 0;
	boundingBox.coords[0].y = 0;
	boundingBox.coords[0].z = 0;

	boundingBox.coords[0].x = 0;
	boundingBox.coords[0].y = 0;
	boundingBox.coords[0].z = 0;

	boundingBox.coords[0].x = 0;
	boundingBox.coords[0].y = 0;
	boundingBox.coords[0].z = 0;

	boundingBox.coords[0].x = 0;
	boundingBox.coords[0].y = 0;
	boundingBox.coords[0].z = 0;

	boundingBox.coords[0].x = 0;
	boundingBox.coords[0].y = 0;
	boundingBox.coords[0].z = 0;

	boundingBox.coords[0].x = 0;
	boundingBox.coords[0].y = 0;
	boundingBox.coords[0].z = 0;

}

