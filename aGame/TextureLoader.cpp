#include "TextureLoader.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include <gl/GLU.h>
#include <iostream>
#include <stdlib.h>
#include <SDL/SDL.h>

TextureLoader::TextureLoader()
{
}


TextureLoader::~TextureLoader()
{
}


unsigned int TextureLoader::LoadTexture(const char *Filename, bool repeat)
{

	unsigned int num;
	glGenTextures(1, &num);
	SDL_Surface *img = SDL_LoadBMP(Filename);
	if (!img)
	{
		std::cout << "Unable to load image" << std::endl;
	}

	glBindTexture(GL_TEXTURE_2D, num);
	if (repeat)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}
	else
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}
	//NEEDS TO INVERT PIXELS VERTICALLY
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, img->w, img->h, 0, GL_BGR, GL_UNSIGNED_BYTE, img->pixels);
	SDL_FreeSurface(img);
	return num;
}