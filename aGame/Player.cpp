#include "Player.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>
#include <algorithm>


#define PI 3.14159265359

Player::Player()
{	
	try
	{
		camera = new Camera();

		if (!camera)
			throw "Can't create player's camera model";
		else
		{
			camera->x -= 5.0f;
			camera->radius = boundingBox.height / 2 / 2;
		}
		animIsCalled = false;
		animLoader = new AnimationLoader();
		animLoader->loadAnimation("E:\\Users\\Banner\\Desktop\\aGame\\aGame\\resources\\objects\\animation\\", "animation_list.txt");
		currentFrame = 0;
		animation = new Animation[animLoader->framesCount];

		for (int i = 0; i < animLoader->framesCount; i++)
		{
			glGenBuffers(1, &animation[i].tid);
			glBindBuffer(GL_ARRAY_BUFFER, animation[i].tid);
			glBufferData(GL_ARRAY_BUFFER, animLoader->frames[i]->UV_vertices.size()*sizeof(float), NULL, GL_STATIC_DRAW);
			glBufferSubData(GL_ARRAY_BUFFER, 0, animLoader->frames[i]->UV_vertices.size()*sizeof(float), &animLoader->frames[i]->UV_vertices[0]);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			glGenBuffers(1, &animation[i].nid);
			glBindBuffer(GL_ARRAY_BUFFER, animation[i].nid);
			glBufferData(GL_ARRAY_BUFFER, animLoader->frames[i]->normals.size()*sizeof(float), NULL, GL_STREAM_DRAW);
			glBufferSubData(GL_ARRAY_BUFFER, 0, animLoader->frames[i]->normals.size()*sizeof(float), &animLoader->frames[i]->normals[0]);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			glGenBuffers(1, &animation[i].vid);
			glBindBuffer(GL_ARRAY_BUFFER, animation[i].vid);
			glBufferData(GL_ARRAY_BUFFER, animLoader->frames[i]->vertices.size()*sizeof(float), NULL, GL_STREAM_DRAW);
			glBufferSubData(GL_ARRAY_BUFFER, 0, animLoader->frames[i]->vertices.size()*sizeof(float), &animLoader->frames[i]->vertices[0]);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
	}
	catch (const char* error)
	{
		model = NULL;
		std::cout << error << std::endl;
	}

}

Player::~Player()
{
	delete[] camera;
	delete[] animLoader;
	delete[] animation;

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	for (int i = 0; i < animLoader->framesCount; i++)
	{
		glDeleteBuffers(1, &animation[i].vid);
		glDeleteBuffers(1, &animation[i].nid);
		glDeleteBuffers(1, &animation[i].tid);
	}
}

bool Player::animIsReady()
{
	return (t.elapsedTime() > (double)1/animLoader->framesCount) ? true : false;
}

void Player::cameraCall() 
{
	glTranslatef(position.coords.x, 0, position.coords.z);

	if (camera->cameraMove)
		glRotatef((camera->deltaAngle + 1.5) * 180 / PI, 0, 1, 0);
	else
		glRotatef((camera->lastAngle + 1.5) * 180 / PI, 0, 1, 0);
}

void Player::drawAnimation()
{
	if (animIsReady() && currentFrame != futureFrame)
	{
		currentFrame++;
		animIsCalled = false;
		if (currentFrame == animLoader->framesCount)
		{
			currentFrame = 0;
			futureFrame = 0;
		}
	}
	//cout << currentFrame << endl;

	glPushMatrix();

	cameraCall();
	if (boundingBox.isShowing)
	{
		glLineWidth(5.0f);
		glEnableClientState(GL_VERTEX_ARRAY);
		glBindBuffer(GL_ARRAY_BUFFER, bbvid);
		glVertexPointer(3, GL_FLOAT, 0, NULL);
		glDrawArrays(GL_LINES, 0, 72);
		glDisableClientState(GL_VERTEX_ARRAY);
	}

	glScalef(scale, scale, scale);

	glEnable(GL_TEXTURE);
	glEnable(GL_NORMALIZE);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

	GLfloat pos[] = { position.coords.x, fabs(boundingBox.height * 2), -position.coords.z, 1.0 };
	GLfloat vector[] = { position.coords.x, 0, -position.coords.z };

	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, vector);


	glBindTexture(GL_TEXTURE_2D, model->textures[0]);

	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, animation[(unsigned int)currentFrame].tid);
	glTexCoordPointer(2, GL_FLOAT, 0, NULL);
	glEnableClientState(GL_NORMAL_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, animation[(unsigned int)currentFrame].nid);
	glNormalPointer(GL_FLOAT, 0, NULL);
	glEnableClientState(GL_VERTEX_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, animation[(unsigned int)currentFrame].vid);
	glVertexPointer(3, GL_FLOAT, 0, NULL);
	glDrawArrays(GL_TRIANGLES, 0, animLoader->frames[(unsigned int)currentFrame]->vertices.size() / 3);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glBindTexture(GL_TEXTURE_2D, 0);

	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);

	glDisable(GL_TEXTURE);
	glDisable(GL_NORMALIZE);

	glPopMatrix();
}



/*void Player::updateVBO()
{
	int index = 0;
	for (int face = 0; face < model->vertex_faces.size(); face++)
	{
		float xV = originVertices[index];
		float zV = originVertices[index + 2];
		float xN = originNormals[index];
		float zN = originNormals[index + 2];

		float coordX, coordZ, normalX, normalZ;

		coordX = rotate2D(xV, zV, - camera->deltaAngle - 1.5); 
		coordZ = rotate2D(zV, -xV, - camera->deltaAngle - 1.5);

		normalX = rotate2D(xN, zN, - camera->deltaAngle - 1.5);
		normalZ = rotate2D(zN, -xN, - camera->deltaAngle - 1.5);


		 model->normals[index] =  position.coords.x + normalX;
		 model->normals[index + 2] =  position.coords.z + normalZ;

		 model->vertices[index] =  coordX;
		 model->vertices[index + 2] =  coordZ;
		index += 3;
	}
	if (boundingBox.isShowing)
	{
		for (int i = 0; i < 72; i+=3)
		{
			boundingBox.coords[i] = position.coords.x + rotate2D(BBoxOriginCoords[i], BBoxOriginCoords[i + 2], -camera->deltaAngle - 1.5);
			//glVertex3f(position.coords.x + rotate2D(boundingBox.coords[i].x, boundingBox.coords[i].z, -player->camera->deltaAngle - 1.5), player->position.coords.y + player->boundingBox.coords[i].y, player->position.coords.z + rotate2D(player->boundingBox.coords[i].z, -player->boundingBox.coords[i].x, -player->camera->deltaAngle - 1.5));
			boundingBox.coords[i + 2] = position.coords.z + rotate2D(BBoxOriginCoords[i + 2], -BBoxOriginCoords[i], -camera->deltaAngle - 1.5);
		}
		glBindBuffer(GL_ARRAY_BUFFER, bbvid);
		glBufferSubData(GL_ARRAY_BUFFER, 0, 72 * sizeof(float), &boundingBox.coords[0]);
	}

	glBindBuffer(GL_ARRAY_BUFFER, nid);
	glBufferSubData(GL_ARRAY_BUFFER, 0,  model->normals.size()*sizeof(float), & model->normals[0]);
	glBindBuffer(GL_ARRAY_BUFFER, vid);
	glBufferSubData(GL_ARRAY_BUFFER, 0,  model->vertices.size()*sizeof(float), & model->vertices[0]);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}*/