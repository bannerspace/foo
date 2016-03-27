#include "Player.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>
#include <algorithm>

Player::Player()
{	
	try
	{
		position = { { 0., 0., 0. }, 0., 0., -1, 0, 0 , false};
		scale = .1f;
		//playerState = PlayerState::ALIVE;
		camera = new Camera();
		camera->x -= 5.0f;

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
		camera->radius = boundingBox.height / 2 / 2;
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

	boundingBox.coords[0].x = boundingBox.x   * scale;
	boundingBox.coords[0].y = 0;
	boundingBox.coords[0].z = boundingBox.z   * scale;

	boundingBox.coords[1].x = boundingBox.x   * scale;
	boundingBox.coords[1].y = 0;
	boundingBox.coords[1].z = (boundingBox.depth + boundingBox.z)   * scale;

	boundingBox.coords[2].x = boundingBox.x   * scale;
	boundingBox.coords[2].y = boundingBox.height   * scale;
	boundingBox.coords[2].z = boundingBox.z   * scale;

	boundingBox.coords[3].x = boundingBox.x   * scale;
	boundingBox.coords[3].y = boundingBox.height   * scale;
	boundingBox.coords[3].z = (boundingBox.depth + boundingBox.z)   * scale;

	boundingBox.coords[4].x = (boundingBox.x + boundingBox.width)   * scale;
	boundingBox.coords[4].y = 0;
	boundingBox.coords[4].z = boundingBox.z   * scale;

	boundingBox.coords[5].x = (boundingBox.x + boundingBox.width)   * scale;
	boundingBox.coords[5].y = 0;
	boundingBox.coords[5].z = (boundingBox.depth + boundingBox.z)   * scale;

	boundingBox.coords[6].x = (boundingBox.x + boundingBox.width)   * scale;
	boundingBox.coords[6].y = boundingBox.height   * scale;
	boundingBox.coords[6].z = boundingBox.z    * scale;

	boundingBox.coords[7].x = (boundingBox.x + boundingBox.width)   * scale;
	boundingBox.coords[7].y = boundingBox.height   * scale;
	boundingBox.coords[7].z = (boundingBox.depth + boundingBox.z)    * scale;


	boundingBox.coords[8].x = boundingBox.x   * scale;
	boundingBox.coords[8].y = 0;
	boundingBox.coords[8].z = boundingBox.z   * scale;

	boundingBox.coords[9].x = boundingBox.x   * scale;
	boundingBox.coords[9].y = boundingBox.height   * scale;
	boundingBox.coords[9].z = boundingBox.z   * scale;

	boundingBox.coords[10].x = (boundingBox.x + boundingBox.width)   * scale;
	boundingBox.coords[10].y = 0;
	boundingBox.coords[10].z = boundingBox.z   * scale;

	boundingBox.coords[11].x = (boundingBox.x + boundingBox.width)   * scale;
	boundingBox.coords[11].y = boundingBox.height   * scale;
	boundingBox.coords[11].z =  boundingBox.z    * scale;

	boundingBox.coords[12].x = (boundingBox.x + boundingBox.width)   * scale;
	boundingBox.coords[12].y = 0;
	boundingBox.coords[12].z = (boundingBox.depth + boundingBox.z)    * scale;

	boundingBox.coords[13].x = (boundingBox.x + boundingBox.width)   * scale;
	boundingBox.coords[13].y = boundingBox.height   * scale;
	boundingBox.coords[13].z = (boundingBox.depth + boundingBox.z)    * scale;

	boundingBox.coords[14].x = boundingBox.x    * scale;
	boundingBox.coords[14].y = 0;
	boundingBox.coords[14].z = (boundingBox.depth + boundingBox.z)    * scale;

	boundingBox.coords[15].x = boundingBox.x    * scale;
	boundingBox.coords[15].y = boundingBox.height   * scale;
	boundingBox.coords[15].z = (boundingBox.depth + boundingBox.z)    * scale;


	boundingBox.coords[16].x = boundingBox.x    * scale;
	boundingBox.coords[16].y = 0;
	boundingBox.coords[16].z = boundingBox.z    * scale;

	boundingBox.coords[17].x = (boundingBox.x + boundingBox.width)   * scale;
	boundingBox.coords[17].y = 0;
	boundingBox.coords[17].z = boundingBox.z    * scale;

	boundingBox.coords[18].x = boundingBox.x    * scale;
	boundingBox.coords[18].y = 0;
	boundingBox.coords[18].z = (boundingBox.depth + boundingBox.z)   * scale;

	boundingBox.coords[19].x = (boundingBox.x + boundingBox.width)   * scale;
	boundingBox.coords[19].y = 0;
	boundingBox.coords[19].z = (boundingBox.depth + boundingBox.z)   * scale;

	boundingBox.coords[20].x = boundingBox.x    * scale;
	boundingBox.coords[20].y = boundingBox.height   * scale;
	boundingBox.coords[20].z = boundingBox.z    * scale;

	boundingBox.coords[21].x = (boundingBox.x + boundingBox.width)   * scale;
	boundingBox.coords[21].y = boundingBox.height   * scale;
	boundingBox.coords[21].z = boundingBox.z    * scale;

	boundingBox.coords[22].x = boundingBox.x    * scale;
	boundingBox.coords[22].y = boundingBox.height   * scale;
	boundingBox.coords[22].z = (boundingBox.depth + boundingBox.z)   * scale;

	boundingBox.coords[23].x = (boundingBox.x + boundingBox.width)   * scale;
	boundingBox.coords[23].y =  boundingBox.height   * scale;
	boundingBox.coords[23].z = (boundingBox.depth + boundingBox.z)   * scale;

}

