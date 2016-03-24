#include "Player.h"
#include <GL/glew.h>
#include <GL/glut.h>
//#include <gl/GLU.h>
#include <iostream>

Player::Player()
{

	coords = { 0., 0., 0., 0., -1, 0, 0 };
	scale = 1.0f;
	playerState = PlayerState::ALIVE;
	
	ObjectLoader loader;
	//loader.print();
	object = new Object (loader.ReadObjectGeometry("E:\\Users\\Banner\\Desktop\\aGame\\aGame\\resources\\objects\\Captain America"));



	if (!object)
		std::cout << "Can't load player's geometry" << std::endl;
	//else
		//alive();
}


Player::~Player()
{
}

void Player::alive(){
	while (playerState != PlayerState::DEAD && object)
	{
		draw();
	}
}

void Player::draw() {
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//gluPerspective(45, (double)_screenWidth / _screenHeight, 1.0, 500.0);
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();

	glPushMatrix();

	glTranslatef(coords.x * scale, coords.y * scale, coords.z * scale);
	glRotatef(coords.angle, 0, 1, 0);

	int index = 0;

	for (int face = 0; face <= object->vertex_faces.size()- 1; face += 3)
	{
		glBegin(GL_TRIANGLES);
		glColor3f(1.0, 1.0, 0.5);

		for (int vertex = 0; vertex < 3; vertex++)
		{
			glNormal3f(object->normals[object->normals_faces[index] * 3 - 3] * 0.1 * scale, object->normals[object->normals_faces[index] * 3 - 2] * 0.1 * scale,
				object->normals[object->normals_faces[index] * 3 - 1] * 0.1 * scale);
			glVertex3f(object->vertex[object->vertex_faces[index] * 3 - 3] * 0.1 * scale, object->vertex[object->vertex_faces[index] * 3 - 2] * 0.1 * scale,
				object->vertex[object->vertex_faces[index] * 3 - 1] * 0.1 * scale);
			index++;
		}
		glEnd();
	}

	glPopMatrix();

}