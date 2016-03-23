#pragma once
class TextureLoader
{
public:
	TextureLoader();
	~TextureLoader();

	unsigned int LoadTexture(const char *Filename, bool repeat);

};

