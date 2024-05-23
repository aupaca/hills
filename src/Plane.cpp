#include "Plane.h"
#include <glm/glm.hpp>

std::vector<unsigned> Plane::wireframeIndexList;

Plane::Plane(float w, float h, int splitX, int splitZ)
{
	int vertexCountX = splitX + 1;
	int vertexCountZ = splitZ + 1;
	vertexList.reserve(vertexCountX * vertexCountZ);
	
	Vertex v;
	v.color = glm::vec4(1.f, 1.f, 1.f, 1.f);
	v.pos = glm::vec3(w/-2.f, 0.f, h/-2.f);
	
	float jumpX = w / splitX;
	float jumpZ = h / splitZ;
	
	for (int i = 0; i < vertexCountZ; i++)
	{
		for (int j = 0; j < vertexCountX; j++)
		{
			vertexList.push_back(v);
			v.pos.x += jumpX;
		}
		v.pos.x = w / -2.f;
		v.pos.z += jumpZ;
	}
	
	if (!wireframeIndexList.empty())
	{
		return;
	}
	
	int currentIndex = 0;
	for (int i = 0; i < vertexCountZ - 1; i++)
	{
		for (int j = 0; j < vertexCountX - 1; j++)
		{
			int nextIndex = currentIndex + 1;
			
			wireframeIndexList.push_back(currentIndex);
			wireframeIndexList.push_back(nextIndex);
			wireframeIndexList.push_back(nextIndex + vertexCountX);
			wireframeIndexList.push_back(currentIndex);
			
			wireframeIndexList.push_back(currentIndex + vertexCountX);
			wireframeIndexList.push_back(nextIndex + vertexCountX);
			wireframeIndexList.push_back(nextIndex);
			
			currentIndex = nextIndex;
		}
		for (int i = 1; i <= vertexCountX - 1; i++)
		{
			wireframeIndexList.push_back(currentIndex - i);
		}
		currentIndex++;
	}
}

