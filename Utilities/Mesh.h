#ifndef _MESH_H_
#define _MESH_H_

#include <vector>
#include "Point3D.h"
#include "Normal.h"
class Mesh
{
public:
	Mesh();
	Mesh(const Mesh& mes);
	~Mesh();

	Mesh& operator=(const Mesh& rhs);

	std::vector<Point3D> vertices;//存储顶点
	std::vector<int> indices;//顶点索引
	std::vector<Normal> normals; //存储顶点的法线
	std::vector<float> u; //存储各坐标点的纹理
	std::vector<float> v; //存储各坐标点的纹理
	std::vector<std::vector<int>> vertexFaces;//与每个顶点相接的所有三角形

	int numTriangles;	//三角形的数目
	int numVertices;	//顶点的数目
};



#endif