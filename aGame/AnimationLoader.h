#pragma once
#include <vector>
#include "Model.h"
#include "ModelLoader.h"

class AnimationLoader
{
public:
	AnimationLoader();
	~AnimationLoader();

	unsigned int framesCount;
	vector<Model*> frames;
	void loadAnimation(char *path, char *Filename);
	void loadModel(const char* path);
private:
	ModelLoader *loader;
	char *animListName;
};