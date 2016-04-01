#include "Camera.h"


Camera::Camera()
{
	lx = 1.0;
	ly = -1.0;
	lz = 0.;
	x = 0;
	y = 1.5;
	z = 0;
	deltaAngle = 0.0;
	deltaAngleY = 0.0;
	lastAngle = 0.0;
	angle = 0.0;
	angley = 0.0;
	xOrigin = -1;
	xOld = 0.0;
	yOld = 0.0;
	moveX = 0.0;
	moveY = -6.0;
	moveZ = 0.0;
	cameraMove = false;
	direction = '\0';
	velocity = .1f;
	isStuck = false;
	isFreeMoving = false;
	isLocked = false;
	radius = 1.0;
}


Camera::~Camera()
{
}
