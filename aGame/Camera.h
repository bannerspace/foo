#pragma once
class Camera
{
public:
	Camera();
	~Camera();

	float lx, ly, lz;
	float x, y, z;
	float deltaAngle, deltaAngleY, lastAngle;
	float angle, angley;
	int xOrigin;
	int xOld, yOld;
	float moveX, moveY, moveZ;
	bool cameraMove;
	char direction;
	float velocity;
	bool isStuck;
	bool isFreeMoving;
	bool isLocked;
	float radius;
};

