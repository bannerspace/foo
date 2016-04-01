#pragma once

#include "Model.h"
#include "ModelLoader.h"
#include "Camera.h"
#include "TextureLoader.h"
#include "AnimationLoader.h"
#include <vector>

enum class ObjectType { STATIC, DYNAMIC, PLAYER };

class Object
{

	virtual	void cameraCall() = 0;
public:
	Object();
	~Object();

	struct Coords {
		float x, y, z;
	};

	struct Position {
		Coords coords;
		float angle;
		float tempAngle;
		float normalX, normalY, normalZ;
		bool isRotating;
	};

	struct BoundingBox {
		float width, height, depth;
		float x, y, z;
		float coords[24 * 3];
		bool isShowing;
	};

	Position position;
	BoundingBox boundingBox;

	Model *model;
	float scale;

	vector<float> originVertices; //don't like
	vector<float> originNormals; //don't like
	vector<float> originUV; //don't like

	void drawObject();

	unsigned int vid; //vertex id
	unsigned int nid; //normals id
	unsigned int tid; //texture coords id

	unsigned int bbvid; //bounding box vertex id
	unsigned int bbcid; //bb color id

	void staticDraw();
	void dynamicDraw();

	float rotate2D(float x, float z, float angle);
private:
	void calculateSizes();
	float BBoxOriginCoords[24 * 3]; ////don't like
	//TextureLoader _loader;
};

