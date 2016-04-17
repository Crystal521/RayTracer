#include "Mesh.h"

Mesh::Mesh()
	:numTriangles(0),
	numVertices(0)
{
}

Mesh::~Mesh()
{
}

Mesh::Mesh(const Mesh& mes)
	:numTriangles(mes.numTriangles),
	numVertices(mes.numVertices),
	vertices(mes.vertices),
	indices(mes.indices),
	normals(mes.normals),
	u(mes.u), v(mes.v)
{}


Mesh& Mesh::operator=(const Mesh& rhs)
{
	if (this == &rhs)
		return *this;

	vertices = rhs.vertices;
	indices = rhs.indices;
	normals = rhs.normals;
	u = rhs.u;
	v = rhs.v;
	numVertices = rhs.numVertices;
	numTriangles = rhs.numTriangles;

	return *this;
}
