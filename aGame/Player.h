#pragma once

#include "Object.h"
#include "ObjectLoader.h"
#include "Camera.h"
enum class PlayerState { ALIVE, DEAD };

class Player
{

public:
	Player();
	~Player();

	struct Coords {
		float x, y, z;
		float angle;
		float normalX, normalY, normalZ;
	};

	Coords coords;
	PlayerState playerState;

	void alive();
	void draw();

	Object *object;
	Camera camera;
	float scale;
};

