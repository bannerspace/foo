#include "AnimationLoader.h"
#include <string>
#include <fstream>
#include <iostream>

AnimationLoader::AnimationLoader()
{
	loader = new ModelLoader();
	framesCount = 0;
}


AnimationLoader::~AnimationLoader()
{
}

void AnimationLoader::loadAnimation(char *path, char *Filename)  //Load Animation List
{

	string s;
	char buffer[100], temp;

	string _path = path;
	string _fname = Filename;
	string listPath = _path + _fname;
	//string _materials = materials;

	cout << listPath.c_str() << endl;
	fstream F;
	F.open(listPath.c_str(), ios::in);

	if (!F)
	{
		std::cout << "Failed opening animation list" << std::endl;
		return;
	}

	while (getline(F, s))
	{
		//strcpy(buffer, s.c_str());

		if (s.length())
		{
			std::cout << (path + s).c_str() << std::endl;
			frames.push_back(loader->ReadModel((path + s + '\0').c_str())); //????????????? PATH IS CORRECT MTHFCK!!!
			framesCount++;
		}
	}
}
