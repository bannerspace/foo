#include "ObjectLoader.h"
#include <string>
#include <fstream>
#include <iostream>


ObjectLoader::ObjectLoader()
{
	//.obj models loader. For now it loads model's geometry and it's textures only in .bmp image format.
	//Besides, image must be flipped horisontally, as it's still not implemented programmatically.
	//The loader only gets texture's names in .mtl file and nothing else for the moment.
	//There are also problems with texture's paths if you run compiled .exe file. So need to make PATH global variable.
	object = new Object();
}


ObjectLoader::~ObjectLoader()
{
}


Object * ObjectLoader::ReadObjectGeometry(const char *geometry, const char *materials) //const char* Filename)
{
	string s;
	char buffer[100], temp;

	fstream F;

	//string a = Filename;
	//string geometry = a + ".obj";

	//F.open(geometry, ios::in);
	F.open(geometry, ios::in);

	if (!F)
	{
		std::cout << geometry << endl;
		std::cout << "Failed opening the geometry file" << std::endl;
		return nullptr;
	}

	
	int counter = 0;
	bool newSection = false;

	while (getline(F, s))
	{

		strcpy(buffer, s.c_str());

		if ((buffer[0] == 'v') && (buffer[1] == ' '))
		{
			float vertices[3];
			sscanf(buffer, "%c %f %f %f", &temp, &vertices[0], &vertices[1], &vertices[2]);

			object->vertex.push_back({vertices[0], vertices[1], vertices[2]});
		}

		else if ((buffer[0] == 'v') && (buffer[1] == 'n') && (buffer[2] == ' '))
		{
			float normals[3];
			sscanf(buffer, "%c %c %f %f %f", &temp, &temp, &normals[0], &normals[1], &normals[2]);

			object->normal.push_back({ normals[0], normals[1], normals[2] });

		}    
		else if ((buffer[0] == 'v') && (buffer[1] == 't') && (buffer[2] == ' '))
		{
			float u, v;
			sscanf(buffer, "vt %f %f", &u, &v);
			object->UV_vertex.push_back({ u, 1-v });
		}
		else if((buffer[0] == 'u') && (buffer[1] == 's') && (buffer[2] == 'e'))
		{
			char temp[200];
			sscanf(buffer, "usemtl %s", temp);
			object->mat_name.push_back(temp);
			newSection = true;
		}

		else if((buffer[0] == 'f') && (buffer[1] == ' '))
		{

			int vertex_faces[3], normals_faces[3], texture_faces[3];
			sscanf(buffer, "%c %d %c %d %c %d %d %c %d %c %d %d %c %d %c %d", &temp, &vertex_faces[0], &temp, &texture_faces[0], &temp, &normals_faces[0], &vertex_faces[1], &temp, &texture_faces[1], &temp, &normals_faces[1], &vertex_faces[2], &temp, &texture_faces[2], &temp, &normals_faces[2]);

			object->vertex_faces.insert(object->vertex_faces.end(), vertex_faces[0]);
			object->vertex_faces.insert(object->vertex_faces.end(), vertex_faces[1]);
			object->vertex_faces.insert(object->vertex_faces.end(), vertex_faces[2]);

			object->normals_faces.insert(object->normals_faces.end(), normals_faces[0]);
			object->normals_faces.insert(object->normals_faces.end(), normals_faces[1]);
			object->normals_faces.insert(object->normals_faces.end(), normals_faces[2]);

			object->texture_faces.insert(object->texture_faces.end(), texture_faces[0]);
			object->texture_faces.insert(object->texture_faces.end(), texture_faces[1]);
			object->texture_faces.insert(object->texture_faces.end(), texture_faces[2]);

			
			if (newSection)
			{
				object->mat_start.push_back(counter);
				newSection = false;
			}
			counter += 3;
		}
	}

	F.close();


	for (int i = 0; i < object->vertex_faces.size(); i++)
	{
		object->vertices.push_back(object->vertex[object->vertex_faces[i] - 1].x);
		object->vertices.push_back(object->vertex[object->vertex_faces[i] - 1].y);
		object->vertices.push_back(object->vertex[object->vertex_faces[i] - 1].z);

		object->normals.push_back(object->normal[object->normals_faces[i] - 1].x);
		object->normals.push_back(object->normal[object->normals_faces[i] - 1].y);
		object->normals.push_back(object->normal[object->normals_faces[i] - 1].z);
	}

	for (int i = 0; i < object->texture_faces.size(); i++)
	{
		object->UV_vertices.push_back(object->UV_vertex[object->texture_faces[i] - 1].x);
		object->UV_vertices.push_back(object->UV_vertex[object->texture_faces[i] - 1].y);
	}

	//string materials = a + ".mtl";

	F.open(materials, ios::in);

	if (!F)
	{
		std::cout << " Failed opening the material file" << std::endl;
		return nullptr;
	}

    newSection = false;
	//float amb[3], dif[3], spec[3], alpha, ns, ni; // not implemented yet
	//int illum;
	char matName[200];
	unsigned int texNumber = 0;

	while (getline(F, s,'\t'))
	{
	
		strcpy(buffer, s.c_str());

		if ((buffer[0] == 'n') && (buffer[1] == 'e' && (buffer[2] == 'w')))
		{
			newSection = true;
		}
		else if (strstr(buffer, "map_Ka"))
		{
			//NEEDS TO REMOVE DOUBLE AND MULTIPLE SPACES + CONVERTING TO BMP
			sscanf(buffer, "map_Ka %s", matName);
			string temp = buffer;
			temp.erase(0, 7); //"map_Ka" + ' ' = 7 chars

			temp = temp.substr(0, temp.length() - 4);
			temp += "bmp";

			string texturePath = "resources\\objects\\" + temp;
			std::cout << texturePath.c_str() << endl;
			object->textures_name.push_back(texturePath);
			object->textures.push_back(textureLoader.LoadTexture(texturePath.c_str(), false));
			std::cout << object->textures[texNumber] << std::endl;
			texNumber++;
		}
	}

	F.close();
	

	for (int i = 0; i < object->mat_name.size(); i++)
	{
		std::cout << object->mat_name[i] << " index: " << object->mat_start[i] << std::endl;
	}

	std::cout << "Object successfully loaded" << std::endl;

	return object;
}