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


using namespace std;

/*void TextureLoader::BindTexture(void *data, int width, int height, int format, unsigned int number)
{
	glGenTextures(1, &texture_id[number]);
	glBindTexture(GL_TEXTURE_2D, texture_id[number]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
}*/

/*void TextureLoader::LoadBMP(const char *Filename, unsigned int tex_number)
{
	FILE *texture;

	texture = fopen(Filename, "r");

	if (!texture)
	{
		cout << "Texture file can not be opened" << endl;
		return;
	}

	char* header_Flag = new char[2];
	fread(header_Flag, 2, sizeof(char), texture);
	cout << header_Flag << endl;
	if (strcmp(header_Flag, "BM"))
	{
		delete[] header_Flag;
		cout << "Wrong texture file format" << endl;
		fclose(texture);
		return;
	}

	delete[] header_Flag;

	unsigned int Location;
	unsigned int width;
	unsigned int height;
	unsigned short numColorPlanes;
	unsigned short bitsPerPixel;
	unsigned int compressionMethod;
	unsigned int DataSize;

	fseek(texture, 0x000a, SEEK_SET);
	fread(&Location, 1, sizeof(unsigned int), texture);
	fseek(texture, 0x0012, SEEK_SET);
	fread(&width, 1, sizeof(unsigned int), texture);
	cout << width << endl;
	fread(&height, 1, sizeof(unsigned int), texture);
	fread(&numColorPlanes, 1, sizeof(unsigned short), texture);
	fread(&bitsPerPixel, 1, sizeof(unsigned short), texture);
	fread(&compressionMethod, 1, sizeof(unsigned int), texture);
	fread(&DataSize, 1, sizeof(unsigned int), texture);

	if (numColorPlanes != 1 || bitsPerPixel != 24 || compressionMethod != 0)
	{
		cout << "Texture file is not raw bmp24" << endl;
		fclose(texture);
		return;
	}

	unsigned char *bmpData = new unsigned char[DataSize];
	fseek(texture, Location, SEEK_SET);
	fread(bmpData, DataSize, sizeof(unsigned char), texture);

	return BindTexture(bmpData, width, height, GL_RGB, tex_number);
}
*/

unsigned int TextureLoader::LoadTexture(const char *Filename, bool repeat)
{

	unsigned int num;
	glGenTextures(1, &num);
	SDL_Surface *img = SDL_LoadBMP(Filename);
	if (!img)
	{
		cout << "Unable to load img" << endl;
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
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img->w, img->h, 0, GL_RGB, GL_UNSIGNED_BYTE, img->pixels);
	SDL_FreeSurface(img);
	return num;
}