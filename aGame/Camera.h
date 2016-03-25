#pragma once
class Camera
{
public:
	Camera();
	~Camera();

	float lx, ly, lz;
	float x, y, z;
	float deltaAngle, deltaAngleY;
	float angle, angley;
	int xOrigin;
	int xPrev;
	float moveX, moveY, moveZ;
	bool cameraMove;
	char direction;
	float velocity;
	bool isStuck;
	bool isFreeMoving;
};

