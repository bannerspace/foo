#pragma once
#include "Model.h"
#include "TextureLoader.h"

class ModelLoader
{
	TextureLoader textureLoader;
public:
	ModelLoader();
	~ModelLoader();

	Model *ReadModelGeometry(const char *geometry, Model *model);
	Model *ReadModelMaterials(const char *materials, Model *model);
	Model *ReadModel(const char *geometry, const char *materials);
	Model *ReadModel(const char *geometry);
};
