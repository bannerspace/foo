#pragma once
#include <vector>

using namespace std;

class Model
{
public:
	Model();
	~Model();

	struct UVcoords {
		float x, y;
	};

	struct Coords {
		float x, y, z;
	};

	vector<int> textures;	//uniq texture id for binding
	vector<Coords> vertex;	//geometry coords (.x, .y, .z)    //STOP USING STRUCT IN VERTS!
	vector<float> vertices; // one by one
	vector<Coords> normal;	//normals vectors coords (.x, .y, .z) 
	vector<float> normals;
	vector<int> vertex_faces; //faces to connect for vertices one by one 
	vector<UVcoords> UV_vertex; //texture coords (.x, .y)
	vector<float> UV_vertices;
	vector<int> texture_faces; //faces to connect for textures coords one by one 
	vector<int> normals_faces; //faces to connect for normals one by one 
	vector<int> mat_start;	//faces indices from where each material starts from
	vector<string> mat_name; //materials names (don't use for the time)
	vector<string> textures_name;
};

