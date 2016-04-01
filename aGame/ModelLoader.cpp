#include "ModelLoader.h"
#include <string>
#include <fstream>
#include <iostream>
#include <cstring>
#include <algorithm>
//#include <boost/iostreams/stream.hpp>

ModelLoader::ModelLoader()
{
	//.obj models loader. For now it loads model's geometry and it's textures only in .bmp image format.
	//Besides, image must be flipped horisontally, as it's still not implemented programmatically.
	//The loader only gets texture's names in .mtl file and nothing else for the moment.
	//There are also problems with texture's paths if you run compiled .exe file. So need to make PATH global variable.
}


ModelLoader::~ModelLoader()
{
}


Model * ModelLoader::ReadModel(const char *geometry, const char *materials)
{
	Model *model = new Model();

	model = ReadModelGeometry(geometry, model);
	model = ReadModelMaterials(materials, model);

	std::cout << "Model successfully loaded" << std::endl;

	return model;
}

Model * ModelLoader::ReadModel(const char *geometry)
{

	Model *model = new Model();

	model = ReadModelGeometry(geometry, model);

	std::cout << "Model successfully loaded" << std::endl;

	return model;
}

Model * ModelLoader::ReadModelMaterials( const char *materials, Model *model)
{

	cout << materials << endl;
	string s;
	char buffer[100], temp;

	fstream F;


	int counter = 0;
	bool newSection = false;

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

	while (getline(F, s, '\t'))
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
			temp = temp.substr(0, temp.length() - 1);

			string texturePath = "resources\\objects\\" + temp;
			std::cout << texturePath.c_str() << endl;
			model->textures_name.push_back(texturePath);
			model->textures.push_back(textureLoader.LoadDDSTexture(texturePath.c_str()));
			std::cout << model->textures[texNumber] << std::endl;
			texNumber++;
		}
	}

	F.close();

	for (int i = 0; i < model->mat_name.size(); i++)
	{
		std::cout << model->mat_name[i] << " index: " << model->mat_start[i] << std::endl;
	}

	std::cout << "Materials successfully loaded" << std::endl;

	return model;
}

Model * ModelLoader::ReadModelGeometry(const char *geometry, Model *model)
{
	string s;
	char buffer[100], temp;
	fstream F;
	F.open(geometry);

	if (!F)
	{
		std::cout << geometry << endl;
		std::cout << "Failed opening the geometry file" << std::endl;
		return nullptr;
	}

	float vertices[3];
	float normals[3];
	float u, v;
	int vertex_faces[3], normals_faces[3], texture_faces[3];

	int counter = 0;
	bool newSection = false;

	//clock_t start = clock();
	while (getline(F, s))
	{

		strcpy(buffer, s.c_str());

		if ((buffer[0] == 'v') && (buffer[1] == ' '))
		{
			sscanf(buffer, "%c %f %f %f", &temp, &vertices[0], &vertices[1], &vertices[2]);
			model->vertex.push_back({ vertices[0], vertices[1], vertices[2] });
		}

		else if ((buffer[0] == 'v') && (buffer[1] == 'n') && (buffer[2] == ' '))
		{
			sscanf(buffer, "%c %c %f %f %f", &temp, &temp, &normals[0], &normals[1], &normals[2]);
			model->normal.push_back({ normals[0], normals[1], normals[2] });
		}
		else if ((buffer[0] == 'v') && (buffer[1] == 't') && (buffer[2] == ' '))
		{
			sscanf(buffer, "vt %f %f", &u, &v);
			model->UV_vertex.push_back({ u, v });
		}
		else if ((buffer[0] == 'u') && (buffer[1] == 's') && (buffer[2] == 'e'))
		{
			char temp[200];
			sscanf(buffer, "usemtl %s", temp);
			model->mat_name.push_back(temp);
			newSection = true;
		}

		else if ((buffer[0] == 'f') && (buffer[1] == ' '))
		{

			sscanf(buffer, "%c %d %c %d %c %d %d %c %d %c %d %d %c %d %c %d", &temp, &vertex_faces[0], &temp, &texture_faces[0], &temp, &normals_faces[0], &vertex_faces[1], &temp, &texture_faces[1], &temp, &normals_faces[1], &vertex_faces[2], &temp, &texture_faces[2], &temp, &normals_faces[2]);

			model->vertex_faces.push_back(vertex_faces[0]);
			model->vertex_faces.push_back(vertex_faces[1]);
			model->vertex_faces.push_back(vertex_faces[2]);

			model->normals_faces.push_back(normals_faces[0]);
			model->normals_faces.push_back(normals_faces[1]);
			model->normals_faces.push_back(normals_faces[2]);

			model->texture_faces.push_back(texture_faces[0]);
			model->texture_faces.push_back(texture_faces[1]);
			model->texture_faces.push_back(texture_faces[2]);


			if (newSection)
			{
				model->mat_start.push_back(counter);
				newSection = false;
			}
			counter += 3; // for each 3 faces 
		}
	}
	//clock_t stop = clock();

	F.close();

	//std::cout << double(stop - start) / CLOCKS_PER_SEC << " seconds\n";

	for (int i = 0; i < model->vertex_faces.size(); i++)
	{
		model->vertices.push_back(model->vertex[model->vertex_faces[i] - 1].x);
		model->vertices.push_back(model->vertex[model->vertex_faces[i] - 1].y);
		model->vertices.push_back(model->vertex[model->vertex_faces[i] - 1].z);

		model->normals.push_back(model->normal[model->normals_faces[i] - 1].x);
		model->normals.push_back(model->normal[model->normals_faces[i] - 1].y);
		model->normals.push_back(model->normal[model->normals_faces[i] - 1].z);
	}

	for (int i = 0; i < model->texture_faces.size(); i++)
	{
		model->UV_vertices.push_back(model->UV_vertex[model->texture_faces[i] - 1].x);
		model->UV_vertices.push_back(model->UV_vertex[model->texture_faces[i] - 1].y);
	}

	//string materials = a + ".mtl";

	std::cout << "Geometry successfully loaded" << std::endl;

	return model;
}
