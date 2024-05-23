#ifndef PLANE_H
#define PLANE_H
#include <vector>
#include "Vertex.h"

struct Plane
{
	static std::vector<unsigned> wireframeIndexList;
	
	Plane(float w, float h, int splitX, int splitZ);
	std::vector<Vertex> vertexList;
};

#endif

