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

	struct Material {
		float amb[3];
		float dif[3];
		float spec[3];
		float alpha;
		float ns;
		float ni;
		int illum;
		unsigned int texture;
	};

	Material material;
	vector<float> vertex;//[100000];
	vector<float> normals;//[100000];
	vector<int> vertex_faces;//[15000];
	vector<UVcoords> UV_vertex;//[15000];
	vector<int> texture_faces;
	vector<int> normals_faces;//[15000];
	vector<Material> materials;
	vector<int> mat_start;
	vector<std::string> mat_name;
	//int vertex_count;
	//int normals_count;
	//int faces_count;
};

