#pragma once

#include "Object.h"
#include "ObjectLoader.h"
#include "Camera.h"
#include "TextureLoader.h"

enum class PlayerState { ALIVE, DEAD };

class Player
{

public:
	Player();
	~Player();

	struct Coords {
		float x, y, z;
	};

	struct Position {
		Coords coords;
		float angle;
		float normalX, normalY, normalZ;
	};

	struct BoundingBox {
		float width, height, depth;
		float x, y, z;
		Coords coords[8];
		bool isShowing;
	};

	Position position;
	BoundingBox boundingBox;
	PlayerState playerState;

	Object *object;
	Camera *camera;
	float scale;

private:
	void CalculateSize();
	//TextureLoader _loader;
};

