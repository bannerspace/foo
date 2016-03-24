#pragma once

#include <vector>

using namespace std;

class Object
{
public:
	Object();
	~Object();

	struct UVcoords {
		float x, y;
	};

	/*struct Faces {
		int face;
		bool hasTexture;
	};*/


	

	//Material material;
	vector<int> textures;
	vector<bool> facesHasTex;
	vector<float> vertex;
	vector<float> normals;
	vector<int> vertex_faces;
	vector<UVcoords> UV_vertex;
	vector<int> texture_faces;
	vector<int> normals_faces;
	vector<int> mat_start;
	vector<string> mat_name;
	vector<string> textures_name;
};

