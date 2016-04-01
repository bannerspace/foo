#pragma once

#include "Object.h"
#include "Camera.h"
#include "AnimationLoader.h"
#include <vector>
#include <time.h>

class timer {
private:
	unsigned long begTime;
public:
	void start() {
		begTime = clock();
	}

	double elapsedTime() {
		return ((double)clock() - begTime) / CLOCKS_PER_SEC;
	}

	bool isTimeout(unsigned long seconds) {
		return seconds >= elapsedTime();
	}
};

class Player : public Object
{

public:
	Player();
	~Player();

	Camera *camera;
	virtual void cameraCall();

	struct Animation
	{
		unsigned int vid;
		unsigned int nid;
		unsigned int tid;
	};

	AnimationLoader *animLoader;
	Animation *animation;
	unsigned int currentFrame;
	unsigned int futureFrame;
	void drawAnimation();
	bool animIsReady();
	bool animIsCalled;
	//void updateVBO();

	timer t;
};

