#include "MainGame.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include "ObjectLoader.h"
#include <thread>


#define PI 3.14159265359


void fatalError(std::string errorString) {
	std::cout << "Fatal Error: ";
	std::cout << errorString << std::endl;
	system("pause");
	SDL_Quit();
	exit(1);
}

MainGame::MainGame()
{
	_window = nullptr;
	_screenWidth = 800;
	_screenHeight = 600;
	_gameState = GameState::PLAY;
	
}


MainGame::~MainGame()
{
}

void MainGame::startGame() {
	initSystems();
	gameLoop();
}

void MainGame::initSystems() {
	SDL_Init(SDL_INIT_EVERYTHING);
	
	_window = SDL_CreateWindow("foo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight, SDL_WINDOW_OPENGL);
	if (!_window)
		fatalError("SDL window couldn't be created.");

	SDL_GLContext glContext = SDL_GL_CreateContext(_window);
	if (!glContext)
		fatalError("SDL context couldn't be created.");

	glewExperimental = true;
	GLenum error = glewInit();
	if (error)
		fatalError("Couldn't initialize glew.");

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	glClearColor(0.5f, 0.5f, 0.5f, 1.f);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, (double)_screenWidth/_screenHeight, 1.0, 1500.0);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	initSkybox();

	player = new Player();
	if (!player->object)
	{
		cout << "player can't be created" << endl;
	}
	else
	{
		//drawPlayer();
	}

	_loader = new TextureLoader();
	texture_id[0] = _loader->LoadTexture("resources\\textures\\ground.bmp", true);

	////////////////////////COLLISION IS IN CPLUSPLUSGUT TUTS!!!!!!!!!!!!!!!!!!!
}

void MainGame::gameLoop() {
	while (_gameState != GameState::EXIT)
	{
		processInput();
		render();

		if ( player->camera->cameraMove)
		{
			cameraMove( player->camera->direction);
		}
	}
	glDeleteBuffers(1, &indexvbo);
	glDeleteBuffers(1, &vbo);
}  

void MainGame::processInput() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type)
		{
			case SDL_QUIT:
			{
				_gameState = GameState::EXIT;
				break;
			}
			case SDL_MOUSEMOTION:
			{
			    mouseMove(event.motion.x , event.motion.y);
				break;
			}
			case SDL_MOUSEWHEEL:
			{
				   player->camera->radius += event.wheel.y;
				break;
			}
	 		case SDL_KEYDOWN:
			{
				if (event.key.keysym.sym == SDLK_w || event.key.keysym.sym == SDLK_s || event.key.keysym.sym == SDLK_a || event.key.keysym.sym == SDLK_d)
				{
					 player->camera->direction = event.key.keysym.sym;
					 player->camera->cameraMove = true;

				}
				else if (event.key.keysym.sym == SDLK_f)
				{

					player->camera->isFreeMoving = !player->camera->isFreeMoving; // free camera positioning

					if (player->camera->isFreeMoving)
						cout << "--Free camera positioning mode is enabled" << endl;
					else
						cout << "--Free camera positioning mode is disabled" << endl;
				}
				else if (event.key.keysym.sym == SDLK_b)
				{

					player->boundingBox.isShowing = !player->boundingBox.isShowing;

					if (player->boundingBox.isShowing)
						cout << "--Bounding box showing is enabled" << endl;
					else
						cout << "--Bounding box showing is disabled" << endl;
				}
				else if (event.key.keysym.sym == SDLK_l)
				{

					player->camera->isLocked = !player->camera->isLocked;

					if (player->camera->isLocked)
						cout << "--Camera is locked" << endl;
					else
						cout << "--Camera is unlocked" << endl;
				}
				break;
			}
			case SDL_KEYUP:
			{

				  player->camera->cameraMove = false;
				  player->camera->direction = '\0';
				break;
			}
		default:
			break;
		}
		
	}

	//SDL_Quit(); //????????????
	//killSkybox(); //???????????
}

float MainGame::rotate2DAboutPoint(float x, float z, float x0, float z0, float angle)
{
	return x0 + (x - x0) * cos(angle) - (z - z0) * sin(angle);
}
float MainGame::rotate2D(float x, float z, float angle)
{
	return x * cos(angle) - z * sin(angle);
}


void MainGame::drawPlayer()
{
	//int num;
	//num = glGenLists(1);
	//glNewList(num, GL_COMPILE);

	/*
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof( player->object->vertex), & player->object->vertex, GL_STATIC_DRAW);
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo);*/
	//glLoadIdentity();
	//glEnableClientState(GL_VERTEX_ARRAY);
	//glEnableClientState(GL_COLOR_ARRAY);

	//glVertexPointer(3, GL_FLOAT, 0, & player->object->vertex);
	//glDrawArrays(GL_TRIANGLES, 0,  player->object->vertex.size()/3);
	


	glEnable(GL_TEXTURE);
	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);

	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glEnable(GL_NORMALIZE);

	GLfloat position[] = { player->position.coords.x, fabs(player->boundingBox.height * 2),- player->position.coords.z, 1.0 };
	GLfloat vector[] = {player->position.coords.x, 0, -player->position.coords.z };

	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, vector);
	
	//glTranslatef(0, 0, 0);
	//glRotatef(player->position.tempAngle, 0, 1, 0);
	//glTranslatef(player->position.coords.x * cos(player->position.angle) * player->scale, player->position.coords.y *  player->scale, player->position.coords.z * (player->position.angle) *  player->scale);

	int index = 0;
	int mats = 0;

	for (int face = 0; face <  player->object->vertex_faces.size(); face += 3)
	{
		if ( player->object->mat_start.size() > 1 &&  player->object->mat_start.size() > mats+1)
			if (face >  player->object->mat_start[mats+1])
			{
				mats++;
			}
		glBindTexture(GL_TEXTURE_2D,  player->object->textures[mats]);

		glBegin(GL_TRIANGLES);

			for (int vertex = 0; vertex < 3; vertex++)
			{
				float xV = player->object->vertex[player->object->vertex_faces[index] - 1].x * player->scale;
				float zV = player->object->vertex[player->object->vertex_faces[index] - 1].z * player->scale;
				float xN = player->object->normals[player->object->normals_faces[index] - 1].x * player->scale;
				float zN = player->object->normals[player->object->normals_faces[index] - 1].z * player->scale;
				
				float coordX, coordZ;
	
				float tempAngle = 

				//coordX = player->position.coords.x  + rotate2D(xV, zV, player->position.angle); //model rotation using wasd rotation 
				//coordZ = player->position.coords.z  + rotate2D(zV, -xV, player->position.angle);

				coordX = player->position.coords.x + rotate2D(xV, zV, -player->camera->deltaAngle - 1.5);  //model rotation using camera rotation 
				coordZ = player->position.coords.z + rotate2D(zV, -xV, -player->camera->deltaAngle- 1.5);

				glTexCoord2f(player->object->UV_vertex[player->object->texture_faces[index] - 1].x , player->object->UV_vertex[ player->object->texture_faces[index] - 1].y); 
				glNormal3f(player->position.coords.x + rotate2D(xN, zN, player->position.angle), player->position.coords.y + player->object->normals[player->object->normals_faces[index] - 1].y   *  player->scale, player->position.coords.z + rotate2D(zN, -xN, player->position.angle));
				glVertex3f(coordX, player->position.coords.y + player->object->vertex[player->object->vertex_faces[index] - 1].y   *  player->scale, coordZ);
				index++;
			}
		glEnd();
	}


	if (player->boundingBox.isShowing)
	{

		glLineWidth(5.0f);
		glColor3f(0, 0, 1);

		glBegin(GL_LINES);
		//bounding box
		for (int i = 0; i < 24; i++)
		{
			glVertex3f(player->position.coords.x + rotate2D(player->boundingBox.coords[i].x, player->boundingBox.coords[i].z, -player->camera->deltaAngle - 1.5), player->position.coords.y + player->boundingBox.coords[i].y, player->position.coords.z + rotate2D(player->boundingBox.coords[i].z, -player->boundingBox.coords[i].x, -player->camera->deltaAngle - 1.5));
		}

		glEnd();
	}
		glColor3f(1, 1, 1);

	
	//glDisableClientState(GL_VERTEX_ARRAY);
	glDisable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, 0);

/*	glEndList();

	 player->object->normals.clear();
	 player->object->vertex.clear();
	 player->object->vertex_faces.clear();
	 player->object->normals_faces.clear();
	 player->object->UV_vertex.clear();

	lists.push_back(num);*/

	
	
/*	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, player->object->vertex.size()*sizeof(float )*3, &player->object->vertex[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
*/

	//glGenBuffers(1, &indexvbo);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexvbo);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short)* 3, pindices, GL_STATIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		//glLoadIdentity();
		//glEnableClientState(GL_VERTEX_ARRAY);
		//glEnableClientState(GL_COLOR_ARRAY);

		//glVertexPointer(3, GL_FLOAT, 0, & player->object->vertex);
		//glDrawArrays(GL_TRIANGLES, 0,  player->object->vertex.size()/3);

}

#define MAIN_SCALER 1.0
void MainGame::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	if (player->camera->isFreeMoving)
	{
		gluLookAt(player->camera->x, player->camera->y, player->camera->z, player->camera->x + player->camera->lx, player->camera->y + player->camera->ly, player->camera->z + player->camera->lz, 0.f, 1.f, 0.f);
		glTranslatef( player->camera->moveX * MAIN_SCALER,  player->camera->moveY * MAIN_SCALER,  player->camera->moveZ * MAIN_SCALER);
	}
	else
	{
		float eyeX, eyeY, eyeZ;

		if (player->camera->isLocked)
		{
			eyeX = player->camera->radius* sin(player->camera->deltaAngle);
			eyeY = player->position.coords.y + player->camera->radius* sin(player->camera->deltaAngleY);
			eyeZ = player->camera->radius* cos(player->camera->deltaAngle);
			gluLookAt(player->position.coords.x + rotate2D(eyeX, eyeZ, player->position.angle), eyeY, player->position.coords.z + rotate2D(eyeZ, -eyeX, player->position.angle), player->position.coords.x, player->position.coords.y + player->boundingBox.height / 2 * player->scale, player->position.coords.z, 0.f, 1.f, 0.f);

		}
		else
		{
			eyeX = player->position.coords.x + player->camera->radius* sin(player->camera->deltaAngle);
			eyeY = player->position.coords.y + player->camera->radius* sin(player->camera->deltaAngleY);
			eyeZ = player->position.coords.z + player->camera->radius* cos(player->camera->deltaAngle);
			gluLookAt(eyeX, eyeY, eyeZ, player->position.coords.x, player->position.coords.y + player->boundingBox.height / 2 * player->scale, player->position.coords.z, 0.f, 1.f, 0.f);
		}

	}
	drawSkybox(500.0f);

	if (player->object)
	{
		glPushMatrix();
		//glTranslatef(player->position.coords.x * player->scale, player->position.coords.y * player->scale, player->position.coords.z * player->scale);
		//glTranslatef(-(player->position.coords.x * cos(player->position.angle) - player->position.coords.z * sin(player->position.angle))* player->scale, player->position.coords.y * player->scale, (player->position.coords.z * cos(player->position.angle) + player->position.coords.x * sin(player->position.angle))* player->scale);
		//glRotatef(player->position.angle, 0, 1, 0);
		//glCallList(lists[0]);
		drawPlayer();

	/*	glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, sizeof(float)* 3, 0);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, player->object->vertex.size());
		glDisableClientState(GL_VERTEX_ARRAY);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		*/
		glPopMatrix();
	}
	drawFloor();
	SDL_GL_SwapWindow(_window);
}

 void MainGame::mouseMove(int x, int y)
{
	 player->camera->deltaAngle += (x - player->camera->xOld) * 0.02f;
	 player->camera->deltaAngleY -= (y - player->camera->yOld) * 0.02f;

	  player->camera->xOld = x;
	  player->camera->yOld = y;



	  if (player->camera->isFreeMoving)
	  {
		  player->camera->lx = sin(player->camera->angle + player->camera->deltaAngle);
		  player->camera->ly = -tan(player->camera->angley + player->camera->deltaAngleY);
		  player->camera->lz = -cos(player->camera->angle + player->camera->deltaAngle);
	  }

 }

 float MainGame::collisionPointPlane(float normalX, float normalY, float normalZ, float x1, float z1, float x2, float z2)
 {
	 GLfloat length = sqrt( player->camera->lx *  player->camera->lx +  player->camera->ly *  player->camera->ly +  player->camera->lz *  player->camera->lz);

	 if ( player->camera->moveX >= -x2 &&  player->camera->moveX <= x1 &&  player->camera->moveZ >= -z2 &&  player->camera->moveZ <= z1)
	 {
		 float nX, nY, nZ;
		 bool more;
		 if (sqrt(pow(( player->camera->moveX - normalX), 2) + pow(( player->camera->moveY - normalY), 2) + pow(( player->camera->moveZ - normalZ), 2)) < sqrt(pow(( player->camera->moveX - normalX), 2) + pow(( player->camera->moveY - (-normalY)), 2) + pow(( player->camera->moveZ - normalZ), 2)))
		 {
			// std::cout << "distance to 0;-1;0 is shorter" << std::endl;
			 nX = normalX;
			 nY = -normalY;
			 nZ = normalZ;
			 more = true;
		 }
		 else
		 {
			// std::cout << "distance to 0;1;0 is shorter" << std::endl;
			 nX = normalX;
			 nY = normalY / 100.; //0.01;
			 nZ = normalZ;
			 more = false;
		 }

		 //std::cout << "distance to plane: " << float(fabs(_camera->moveX * nX + _camera->moveY * normalY + _camera->moveZ * nZ) + nY) << std::endl;

		 if ( player->camera->isStuck)
		 {
			 float angle = acos(( player->camera->lx * nX +  player->camera->ly* nY +  player->camera->lz * nZ) / (1 * sqrt( player->camera->lx *  player->camera->lx +  player->camera->ly *  player->camera->ly +  player->camera->lz *  player->camera->lz))) * 180 / PI;
			 //std::cout << "angle is " << angle << " degrees" << std::endl;

			 //float _y = _camera->ly / length * _camera->velocity;
			 if (!more)
			 {
				 //std::cout << "angle should be grater than 90 degrees" << std::endl;
				 if (angle < 90)
				 {
					  player->camera->isStuck = false;
					// return false;
					 return   player->camera->ly / length *  player->camera->velocity;
				 }
			 }
			 else
			 {
				// std::cout << "angle should be less than 90 degrees" << std::endl;
				 if (angle < 90)
				 {
					
					  player->camera->isStuck = false;
					 return   player->camera->ly / length *  player->camera->velocity;
				 }
			 }

		 }
		 else {
			 if (float(fabs( player->camera->moveX * nX +  player->camera->moveY *normalY +  player->camera->moveZ * nZ) + nY) > 0.1)
			 {
				  player->camera->isStuck = false;
				 return   player->camera->ly / length *  player->camera->velocity;
			 }
			 else
			 {
				  player->camera->isStuck = true;
			 }
		 }
	 }
	 else
	 {
		  player->camera->isStuck = false;
		 return   player->camera->ly / length *  player->camera->velocity;
	 }

	 return 0.f;
 }

 void MainGame::cameraMove(char dir)
 {
	 GLfloat length = sqrt( player->camera->lx *  player->camera->lx +  player->camera->ly *  player->camera->ly +  player->camera->lz *  player->camera->lz);
	 switch (dir) {
	 case SDLK_w:
	 {

		 if (!player->camera->isFreeMoving)
		 {
			 player->position.coords.x -= 1.0 * sin(player->camera->deltaAngle);//moving in the camera's forward direction
			 player->position.coords.z -= 1.0 * cos(player->camera->deltaAngle);
			 
			// player->position.angle -= player->camera->deltaAngle;

			 //player->position.coords.x += 1.0 * cos(player->position.angle); //moving in the model's forward direction
			// player->position.coords.z += 1.0 * sin(player->position.angle);

			 player->camera->moveX = -player->position.coords.x;
			 player->camera->moveZ = -player->position.coords.z;
		 }
		 else
		 {
			 player->camera->moveX -= player->camera->lx / length *  player->camera->velocity;
			 player->camera->moveZ -= player->camera->lz / length *  player->camera->velocity;
		 }

		break;
	 }
	 case SDLK_s:
	 {

		 if (!player->camera->isFreeMoving)
		 {
			 player->position.coords.x -= 1.0  * cos(player->position.angle);//player->camera->lx / length *  player->camera->velocity;
			 player->position.coords.z -= 1.0  * sin(player->position.angle);//player->camera->lz / length *  player->camera->velocity;

			 player->camera->moveX = -player->position.coords.x;
			 player->camera->moveZ = -player->position.coords.z;
		 }
		 else
		 {
			 player->camera->moveX += player->camera->lx / length *  player->camera->velocity;
			 player->camera->moveZ += player->camera->lz / length *  player->camera->velocity;
		 }

		break;
	 }
	 case SDLK_d:
	 {
			if (player->camera->isFreeMoving)
			{
				player->camera->moveX += player->camera->lz / length * player->camera->velocity;
				player->camera->moveZ -= player->camera->lx / length * player->camera->velocity;
			}
			else
			{
					player->position.angle -= .5;
			}

		break;
	 }
	 case SDLK_a:
	 {
			if (player->camera->isFreeMoving)
			{
				player->camera->moveX -= player->camera->lz / length * player->camera->velocity;
				player->camera->moveZ += player->camera->lx / length * player->camera->velocity;
			}
			else
			{
					player->position.angle += .5;
			
			}
		break;
	 }
	 default:
		 break;
	 }

 }

 void MainGame::initSkybox() {
	
	 skybox[SKY_LEFT] = _loader->LoadTexture("resources\\textures\\skybox\\sky_left.bmp", false);
	 skybox[SKY_BACK] = _loader->LoadTexture("resources\\textures\\skybox\\sky_back.bmp", false);
	 skybox[SKY_RIGHT] = _loader->LoadTexture("resources\\textures\\skybox\\sky_right.bmp", false);
	 skybox[SKY_FRONT] = _loader->LoadTexture("resources\\textures\\skybox\\sky_front.bmp", false);
	 skybox[SKY_TOP] = _loader->LoadTexture("resources\\textures\\skybox\\sky_top.bmp", false);
	 skybox[SKY_BOTTOM] = _loader->LoadTexture("resources\\textures\\skybox\\sky_bottom.bmp", false);
 }

 void MainGame::killSkybox() {
	 glDeleteTextures(6, &skybox[0]);
 }

 void MainGame::drawSkybox(float size) {

	 glDisable(GL_LIGHTING);
	 glDisable(GL_DEPTH_TEST);
	 glDisable(GL_LIGHT0);

	 glBindTexture(GL_TEXTURE_2D, skybox[SKY_BACK]);
	 glBegin(GL_QUADS);
		 glTexCoord2f(0, 0);
		 glVertex3f(size, size, size);
		 glTexCoord2f(1, 0);
		 glVertex3f(-size, size, size);
		 glTexCoord2f(1, 1);
		 glVertex3f(-size, -size, size);
		 glTexCoord2f(0, 1);
		 glVertex3f(size, -size, size);
	 glEnd();

	 glBindTexture(GL_TEXTURE_2D, skybox[SKY_LEFT]);
	 glBegin(GL_QUADS);
		glTexCoord2f(0, 0);
		glVertex3f(-size, size, size);
		glTexCoord2f(1, 0);
		glVertex3f(-size, size, -size);
		glTexCoord2f(1, 1);
		glVertex3f(-size, -size, -size);
		glTexCoord2f(0, 1);
		glVertex3f(-size, -size, size);
	 glEnd();

	 glBindTexture(GL_TEXTURE_2D, skybox[SKY_RIGHT]);
	 glBegin(GL_QUADS);
		 glTexCoord2f(0, 0);
		 glVertex3f(size, size, -size);
		 glTexCoord2f(1, 0);
		 glVertex3f(size, size, size);
		 glTexCoord2f(1, 1);
		 glVertex3f(size, -size, size);
		 glTexCoord2f(0, 1);
		 glVertex3f(size, -size, -size);
	 glEnd();

	 glBindTexture(GL_TEXTURE_2D, skybox[SKY_FRONT]);
	 glBegin(GL_QUADS);
		 glTexCoord2f(1, 0);
		 glVertex3f(size, size, -size);
		 glTexCoord2f(0, 0);
		 glVertex3f(-size, size, -size);
		 glTexCoord2f(0, 1);
		 glVertex3f(-size, -size, -size);
		 glTexCoord2f(1, 1);
		 glVertex3f(size, -size, -size);
	 glEnd();

	 glBindTexture(GL_TEXTURE_2D, skybox[SKY_TOP]);
	 glBegin(GL_QUADS);
		 glTexCoord2f(1, 0);
		 glVertex3f(size, size, size);
		 glTexCoord2f(0, 0);
		 glVertex3f(-size, size, size);
		 glTexCoord2f(0, 1);
		 glVertex3f(-size, size, -size);
		 glTexCoord2f(1, 1);
		 glVertex3f(size, size, -size);
	 glEnd();

	 glBindTexture(GL_TEXTURE_2D, skybox[SKY_BOTTOM]);
	 glBegin(GL_QUADS);
		 glTexCoord2f(1, 1);
		 glVertex3f(size, -size, size);
		 glTexCoord2f(0, 1);
		 glVertex3f(-size, -size, size);
		 glTexCoord2f(0, 0);
		 glVertex3f(-size, -size, -size);
		 glTexCoord2f(1, 0);
		 glVertex3f(size, -size, -size);
	 glEnd();

	 glBindTexture(GL_TEXTURE_2D, 0);
	  glEnable(GL_DEPTH_TEST);

 }

 void MainGame::drawFloor()
 {
	// glEnable(GL_LIGHTING);
	// glEnable(GL_LIGHT0);
	 glBindTexture(GL_TEXTURE_2D, texture_id[0]);

	 glBegin(GL_QUADS);


	 glTexCoord2f(0.0f, 0.0f);
	 glNormal3f(0.0, 1.0, 0.0);
	 glVertex3f(0.0f, 0.0f, 0.0f);
	 glTexCoord2f(0.0f, 100.0f);
	 glNormal3f(0.0, 1.0, 0.0);
	 glVertex3f(0.0f, 0.0f, 100.0f);
	 glTexCoord2f(100.0f, 100.0f);
	 glNormal3f(0.0, 1.0, 0.0);
	 glVertex3f(100.0f, 0.0f, 100.0f);
	 glTexCoord2f(100.0f, 0.0f);
	 glNormal3f(0.0, 1.0, 0.0);
	 glVertex3f(100.0f, 0.0f, 0.0f);

	 glEnd();

	 glBindTexture(GL_TEXTURE_2D, 0);
 }