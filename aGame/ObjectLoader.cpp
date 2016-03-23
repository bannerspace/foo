#include "ObjectLoader.h"
#include <string>
#include <fstream>
#include <iostream>

ObjectLoader::ObjectLoader()
{
}


ObjectLoader::~ObjectLoader()
{
}

using namespace std;


//int chunk[6];
void ObjectLoader::print()
{
	std::cout << "1111" << std::endl;
}

Object ObjectLoader::ReadObjectGeometry(const char* Filename)
{
	string s;
	char buffer[100], flag[9];
	int chunk[6];

	fstream F;

	//string geometry;
	//strcpy(geometry.c_str(), Filename);
	//	+ ".obj\n";

	F.open(Filename, ios::in);

	if (!F)
	{
		std::cout << " Failed opening the geometry file" << std::endl;
		return object;
	}

	
	int counter = 0;
	bool newSection = false;

	while (getline(F, s))
	{

		strcpy(buffer, s.c_str());

		if ((buffer[0] == 'v') && (buffer[1] == ' '))
		{
			//cout << s.c_str() << endl;
			float vertices[3];
			sscanf(buffer, "%c %f %f %f", &flag[7], &vertices[0], &vertices[1], &vertices[2]);// &object.vertex[object.vertex_count], &object.vertex[object.vertex_count + 1], &object.vertex[object.vertex_count + 2]);
			/* cout << Model_Geometry[Model_Number].vertex[Model_Geometry[Model_Number].vertex_count] << " " <<  Model_Geometry[Model_Number].vertex[Model_Geometry[Model_Number].vertex_count + 1] << " " <<  Model_Geometry[Model_Number].vertex[Model_Geometry[Model_Number].vertex_count + 2] << endl;
			*/

			object.vertex.insert(object.vertex.end(), vertices[0]);
			object.vertex.insert(object.vertex.end(), vertices[1]);
			object.vertex.insert(object.vertex.end(), vertices[2]);
			//object.vertex_count += 3;

		}

		else if ((buffer[0] == 'v') && (buffer[1] == 'n') && (buffer[2] == ' '))
		{
			float normals[3];
			sscanf(buffer, "%c %c %f %f %f", &flag[0], &flag[8], &normals[0], &normals[1], &normals[2]); // &object.normals[object.normals_count], &object.normals[object.normals_count + 1], &object.normals[object.normals_count + 2]);

			/* cout << Model_Geometry[Model_Number].normals[Model_Geometry[Model_Number].normals_count] << " " << Model_Geometry[Model_Number].normals[Model_Geometry[Model_Number].normals_count + 1] << " " << Model_Geometry[Model_Number].normals[Model_Geometry[Model_Number].normals_count + 2] << endl;
			*/

			object.normals.insert(object.normals.end(), normals[0]);
			object.normals.insert(object.normals.end(), normals[1]);
			object.normals.insert(object.normals.end(), normals[2]);
			//object.normals_count += 3;

		}    
		else if ((buffer[0] == 'v') && (buffer[1] == 't') && (buffer[2] == ' '))
		{
			float u, v;
			sscanf(buffer, "vt %f %f", &u, &v);
			object.UV_vertex.push_back({ u, 1-v }); //1-v ????
		}
		else if((buffer[0] == 'u') && (buffer[1] == 's') && (buffer[2] == 'e'))
		{
			char temp[200];
			//temp[199] = '\0';
			sscanf(buffer, "usemtl %s", temp);
			
			//object.mat_name.insert(object.mat_name.end(), temp);
			object.mat_name.push_back(temp);
			newSection = true;
		}

		else if((buffer[0] == 'f') && (buffer[1] == ' '))
		{

			int vertex_faces[3], normals_faces[3], texture_faces[3];
			sscanf(buffer, "%c %d %c %d %c %d %d %c %d %c %d %d %c %d %c %d", &flag[0], &vertex_faces[0], &flag[1], &texture_faces[0], &flag[2], &normals_faces[0], &vertex_faces[1], &flag[3], &texture_faces[1], &flag[4], &normals_faces[1], &vertex_faces[2], &flag[5], &texture_faces[2], &flag[6], &normals_faces[2]);
				//&object.vertex_faces[object.faces_count], &flag[1], &chunk[0], &flag[2], &object.normals_faces[object.faces_count], &object.vertex_faces[object.faces_count + 1], &flag[3], &chunk[2], &flag[4], &object.normals_faces[object.faces_count + 1], &object.vertex_faces[object.faces_count + 2], &flag[5], &chunk[4], &flag[6], &object.normals_faces[object.faces_count + 2]);

			object.vertex_faces.insert(object.vertex_faces.end(), vertex_faces[0]);
			object.vertex_faces.insert(object.vertex_faces.end(), vertex_faces[1]);
			object.vertex_faces.insert(object.vertex_faces.end(), vertex_faces[2]);

			object.normals_faces.insert(object.normals_faces.end(), normals_faces[0]);
			object.normals_faces.insert(object.normals_faces.end(), normals_faces[1]);
			object.normals_faces.insert(object.normals_faces.end(), normals_faces[2]);

			object.texture_faces.insert(object.texture_faces.end(), texture_faces[0]);
			object.texture_faces.insert(object.texture_faces.end(), texture_faces[1]);
			object.texture_faces.insert(object.texture_faces.end(), texture_faces[2]);
			//object.faces_count += 3;

			
			if (newSection)
			{
				object.mat_start.push_back(counter);
				newSection = false;
			}
			counter += 3;
		}

		
		for (int i = 0; i < 100; i++)
			buffer[i] = NULL;
	}

	F.close();

	/*F.open(Filename, ios::in);

	if (!F)
	{
		std::cout << " Failed opening the material file" << std::endl;
		return object;
	}

	int counter = 0;
	bool newSection = false;
	bool isMat = false;
	float amb[3], dif[3], spec[3], alpha, ns, ni;
	int illum;
	unsigned int texture;
	char matName[200];


	while (getline(F, s))
	{

		strcpy(buffer, s.c_str());


		if ((buffer[0] == 'n') && (buffer[1] == 'e' && (buffer[2] == 'w')))
		{

			if (isMat)
			{
				//object.materials.push_back({amb, dif, spec, alpha, ns, ni, illum, texture });
				//object.materials.push_back({amb, dif});
				
			}
			else
			{

			}
		}
	}*/

	for (int i = 0; i < object.mat_name.size(); i++)
	{
		std::cout << object.mat_name[i] << " index: " << object.mat_start[i] << std::endl;

	}

	std::cout << object.UV_vertex.size() << endl;//" | " << object.vertex_faces.size() << std::endl;

	std::cout << "Object successfully loaded" << std::endl;

	return object;
}