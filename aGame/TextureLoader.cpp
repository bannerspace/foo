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
		return 0;
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

unsigned int TextureLoader::LoadDDSTexture(const char *Filename)
{
	///// http://opengl-tutorial.blogspot.ru/p/5.html rewritten

#define ID_DXT1   0x31545844
#define ID_DXT3   0x33545844
#define ID_DXT5   0x35545844



	unsigned char header[124];
	FILE *TexturFile;
	//file exist?
	TexturFile = fopen(Filename, "rb");
	if (!TexturFile)
	{
		std::cout << "Failed loading texture: " << Filename << std::endl;
		return 0;
	}

	//and is dds?
	char filecode[4];
	fread(filecode, 1, 4, TexturFile);
	if (strncmp(filecode, "DDS ", 4) != 0) {
		fclose(TexturFile);
		std::cout << "Texture format is not DDS: " << Filename << std::endl;
		return 0;
	}
	//then what is in it?i
	//read file from 5 byte by 4 byte
	fread(&header, 124, 1, TexturFile);
	unsigned int height = *(unsigned int*)&(header[8]); //of texture (8  bit)
	unsigned int width = *(unsigned int*)&(header[12]);//of texture (12 bit)
	unsigned int linearSize = *(unsigned int*)&(header[16]);//??? its for get size mem for texture? (16 bit)
	unsigned int mipMapCount = *(unsigned int*)&(header[24]);//leve's of texture (24 bit)
	unsigned int fourCC = *(unsigned int*)&(header[80]);//

	//for corection, IDUNNO_HOW_IT_MUST_RIGHT_WORK, because calculate missig value. mb correct?
	linearSize = (fourCC == ID_DXT1) ? ((width + 3) / 4)*((height + 3) / 4) * 8 : ((width + 3) / 4)*((height + 3) / 4) * 16;//!!!!!!! 

	//detect type format
	unsigned int format;

	switch (fourCC)
	{
	case ID_DXT1:
		format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
		break;
	case ID_DXT3:
		format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
		break;
	case ID_DXT5:
		format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
		break;
	default:
		//free(buffer); //not. we not read this yet
		std::cout << "Problems aquired while detecting type of DDS -- \n\t" << Filename << std::endl;
		return 0;
	}

	//and read file to mem. close it.
	unsigned char * buffer;
	unsigned int bufsize;
	bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize; //bufsize = ((width + 3) / 4)*((height + 3) / 4);//!!!!!!!
	buffer = (unsigned char*)malloc(bufsize * sizeof(unsigned char));
	fread(buffer, 1, bufsize, TexturFile);
	fclose(TexturFile);

	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	//load mipMap
	unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
	unsigned int offset = 0;
	for (unsigned int level = 0; level < mipMapCount; ++level)
	{
		unsigned int size = ((width + 3) / 4)*((height + 3) / 4)*blockSize;
		glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height, 0, size, buffer + offset);

		offset += size;
		width /= 2;
		height /= 2;
	}


	free(buffer);
	return textureID;
}