#include "Object.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>
#include <algorithm>

#define PI 3.14159265359

Object::Object()
{
	try
	{
		position = { { 0., 0., 0. }, 0., 0., -1, 0, 0, false };
		scale = .1f;

		ModelLoader modelLoader;
		model = modelLoader.ReadModel("resources\\objects\\Captain America.obj", "resources\\objects\\Captain America.mtl");

		if (!model)
		{
			throw "Can't load player's geometry";
		}
		else
		{
			boundingBox.isShowing = false;
			calculateSizes();

		 	glGenBuffers(1, &tid);
			glBindBuffer(GL_ARRAY_BUFFER, tid);
			glBufferData(GL_ARRAY_BUFFER, model->UV_vertices.size()*sizeof(float), NULL, GL_STATIC_DRAW);
			glBufferSubData(GL_ARRAY_BUFFER, 0, model->UV_vertices.size()*sizeof(float), &model->UV_vertices[0]);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			glGenBuffers(1, &nid);
			glBindBuffer(GL_ARRAY_BUFFER, nid);
			glBufferData(GL_ARRAY_BUFFER, model->normals.size()*sizeof(float), NULL, GL_STATIC_DRAW);
			glBufferSubData(GL_ARRAY_BUFFER, 0, model->normals.size()*sizeof(float), &model->normals[0]);
			glBindBuffer(GL_ARRAY_BUFFER, 0);


			glGenBuffers(1, &vid);
			glBindBuffer(GL_ARRAY_BUFFER, vid);
			glBufferData(GL_ARRAY_BUFFER, model->vertices.size()*sizeof(float), NULL, GL_STATIC_DRAW);
			glBufferSubData(GL_ARRAY_BUFFER, 0, model->vertices.size()*sizeof(float), &model->vertices[0]);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			glGenBuffers(1, &bbvid);
			glBindBuffer(GL_ARRAY_BUFFER, bbvid);
			glBufferData(GL_ARRAY_BUFFER, 72 * sizeof(float), NULL, GL_STATIC_DRAW);
			glBufferSubData(GL_ARRAY_BUFFER, 0, 72 * sizeof(float), &boundingBox.coords[0]);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
	}
	catch (const char* error)
	{
		model = NULL;
		std::cout << error << std::endl;
	}

}

Object::~Object()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &vid);
	glDeleteBuffers(1, &nid);
	glDeleteBuffers(1, &tid);
	glDeleteBuffers(1, &bbvid);
	glDeleteBuffers(1, &bbcid);
}

void Object::calculateSizes()
{
	float xMax = model->vertex[0].x;
	float xMin = xMax;

	float yMax = model->vertex[0].y;
	float yMin = yMax;

	float zMax = model->vertex[0].z;
	float zMin = zMax;

	for (int i = 0; i < model->vertex.size(); i++)
	{
		if (xMax < model->vertex[i].x)
			xMax = model->vertex[i].x;
		if (xMin > model->vertex[i].x)
			xMin = model->vertex[i].x;

		if (yMax < model->vertex[i].y)
			yMax = model->vertex[i].y;
		if (yMin > model->vertex[i].y)
			yMin = model->vertex[i].y;

		if (zMax < model->vertex[i].z)
			zMax = model->vertex[i].z;
		if (zMin > model->vertex[i].z)
			zMin = model->vertex[i].z;
	}

	boundingBox.width = abs(xMax - xMin);
	boundingBox.height = abs(yMax - yMin);
	boundingBox.depth = abs(zMax - zMin);


	boundingBox.x = xMin;
	boundingBox.y = yMin;
	boundingBox.z = zMin;

	boundingBox.coords[0] = boundingBox.x * scale;
	boundingBox.coords[1] = 0;
	boundingBox.coords[2] = boundingBox.z * scale;

	boundingBox.coords[3] = boundingBox.x * scale;
	boundingBox.coords[4] = 0;
	boundingBox.coords[5] = (boundingBox.depth + boundingBox.z)   * scale;

	boundingBox.coords[6] = boundingBox.x   * scale;
	boundingBox.coords[7] = boundingBox.height   * scale;
	boundingBox.coords[8] = boundingBox.z   * scale;

	boundingBox.coords[9] = boundingBox.x   * scale;
	boundingBox.coords[10] = boundingBox.height   * scale;
	boundingBox.coords[11] = (boundingBox.depth + boundingBox.z)   * scale;

	boundingBox.coords[12] = (boundingBox.x + boundingBox.width)   * scale;
	boundingBox.coords[13] = 0;
	boundingBox.coords[14] = boundingBox.z   * scale;

	boundingBox.coords[15] = (boundingBox.x + boundingBox.width)   * scale;
	boundingBox.coords[16] = 0;
	boundingBox.coords[17] = (boundingBox.depth + boundingBox.z)   * scale;

	boundingBox.coords[18] = (boundingBox.x + boundingBox.width)   * scale;
	boundingBox.coords[19] = boundingBox.height   * scale;
	boundingBox.coords[20] = boundingBox.z    * scale;

	boundingBox.coords[21] = (boundingBox.x + boundingBox.width)   * scale;
	boundingBox.coords[22] = boundingBox.height   * scale;
	boundingBox.coords[23] = (boundingBox.depth + boundingBox.z)    * scale;


	boundingBox.coords[24] = boundingBox.x   * scale;
	boundingBox.coords[25] = 0;
	boundingBox.coords[26] = boundingBox.z   * scale;

	boundingBox.coords[27] = boundingBox.x   * scale;
	boundingBox.coords[28] = boundingBox.height   * scale;
	boundingBox.coords[29] = boundingBox.z   * scale;

	boundingBox.coords[30] = (boundingBox.x + boundingBox.width)   * scale;
	boundingBox.coords[31] = 0;
	boundingBox.coords[32] = boundingBox.z   * scale;

	boundingBox.coords[33] = (boundingBox.x + boundingBox.width)   * scale;
	boundingBox.coords[34] = boundingBox.height   * scale;
	boundingBox.coords[35] = boundingBox.z    * scale;

	boundingBox.coords[36] = (boundingBox.x + boundingBox.width)  * scale;
	boundingBox.coords[37] = 0;
	boundingBox.coords[38] = (boundingBox.depth + boundingBox.z)   * scale;

	boundingBox.coords[39] = (boundingBox.x + boundingBox.width)  * scale;
	boundingBox.coords[40] = boundingBox.height   * scale;
	boundingBox.coords[41] = (boundingBox.depth + boundingBox.z)   * scale;

	boundingBox.coords[42] = boundingBox.x    * scale;
	boundingBox.coords[43] = 0;
	boundingBox.coords[44] = (boundingBox.depth + boundingBox.z)  * scale;

	boundingBox.coords[45] = boundingBox.x    * scale;
	boundingBox.coords[46] = boundingBox.height   * scale;
	boundingBox.coords[47] = (boundingBox.depth + boundingBox.z)  * scale;


	boundingBox.coords[48] = boundingBox.x    * scale;
	boundingBox.coords[49] = 0;
	boundingBox.coords[50] = boundingBox.z    * scale;

	boundingBox.coords[51] = (boundingBox.x + boundingBox.width) * scale;
	boundingBox.coords[52] = 0;
	boundingBox.coords[53] = boundingBox.z    * scale;

	boundingBox.coords[54] = boundingBox.x    * scale;
	boundingBox.coords[55] = 0;
	boundingBox.coords[56] = (boundingBox.depth + boundingBox.z) * scale;

	boundingBox.coords[57] = (boundingBox.x + boundingBox.width) * scale;
	boundingBox.coords[58] = 0;
	boundingBox.coords[59] = (boundingBox.depth + boundingBox.z) * scale;

	boundingBox.coords[60] = boundingBox.x    * scale;
	boundingBox.coords[61] = boundingBox.height   * scale;
	boundingBox.coords[62] = boundingBox.z    * scale;

	boundingBox.coords[63] = (boundingBox.x + boundingBox.width) * scale;
	boundingBox.coords[64] = boundingBox.height   * scale;
	boundingBox.coords[65] = boundingBox.z    * scale;

	boundingBox.coords[66] = boundingBox.x    * scale;
	boundingBox.coords[67] = boundingBox.height   * scale;
	boundingBox.coords[68] = (boundingBox.depth + boundingBox.z) * scale;

	boundingBox.coords[69] = (boundingBox.x + boundingBox.width) * scale;
	boundingBox.coords[70] = boundingBox.height   * scale;
	boundingBox.coords[71] = (boundingBox.depth + boundingBox.z) * scale;


	for (int i = 0; i < model->vertices.size(); i++)
	{
		model->vertices[i] *= scale;
		model->normals[i] *= scale;
	}

	originVertices = model->vertices;
	originNormals = model->normals;
	originUV = model->UV_vertices;

	for (int i = 0; i < 72; i++)
	{
		BBoxOriginCoords[i] = boundingBox.coords[i];
	}

}


void Object::staticDraw()
{

}


void Object::drawObject()
{

	glPushMatrix();

	cameraCall();

	glEnable(GL_TEXTURE);
	glEnable(GL_NORMALIZE);
	//if (player->model->mat_start.size() > 1 && player->model->mat_start.size() > mats + 1)
	//	if (face > player->model->mat_start[mats + 1])
	//{
	//	mats++;
	//	}

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

	GLfloat pos[] = { position.coords.x, fabs(boundingBox.height * 2), -position.coords.z, 1.0 };
	GLfloat vector[] = { position.coords.x, 0, -position.coords.z };

	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, vector);


	glBindTexture(GL_TEXTURE_2D, model->textures[0]);

	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, tid);
	glTexCoordPointer(2, GL_FLOAT, 0, NULL);
	glEnableClientState(GL_NORMAL_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, nid);
	glNormalPointer(GL_FLOAT, 0, NULL);
	glEnableClientState(GL_VERTEX_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, vid);
	glVertexPointer(3, GL_FLOAT, 0, NULL);
	glDrawArrays(GL_TRIANGLES, 0, model->vertices.size() / 3);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glBindTexture(GL_TEXTURE_2D, 0);

	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);

	if (boundingBox.isShowing)
	{
		glLineWidth(5.0f);
		glEnableClientState(GL_VERTEX_ARRAY);
		glBindBuffer(GL_ARRAY_BUFFER, bbvid);
		glVertexPointer(3, GL_FLOAT, 0, NULL);
		glDrawArrays(GL_LINES, 0, 72);
		glDisableClientState(GL_VERTEX_ARRAY);

	}

	glDisable(GL_TEXTURE);
	glDisable(GL_NORMALIZE);


	glPopMatrix();

}

float Object::rotate2D(float x, float z, float angle)
{
	return x * cos(angle) - z * sin(angle);
}
