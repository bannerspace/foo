#pragma once
class TextureLoader
{
public:
	TextureLoader();
	~TextureLoader();

	unsigned int LoadTexture(const char *Filename, bool repeat);
	unsigned int LoadDDSTexture(const char *Filename);
};

