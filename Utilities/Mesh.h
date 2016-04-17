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

	std::vector<Point3D> vertices;//�洢����
	std::vector<int> indices;//��������
	std::vector<Normal> normals; //�洢����ķ���
	std::vector<float> u; //�洢������������
	std::vector<float> v; //�洢������������
	std::vector<std::vector<int>> vertexFaces;//��ÿ��������ӵ�����������

	int numTriangles;	//�����ε���Ŀ
	int numVertices;	//�������Ŀ
};



#endif