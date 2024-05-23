#ifndef VERTEX_H
#define VERTEX_H
#include <glm/glm.hpp>

struct Vertex
{
	glm::vec3 pos;
	glm::vec4 color;
};

#define VERTEX_POS_INDEX 0
#define VERTEX_POS_ATTR_COUNT 3
#define VERTEX_POS_OFFSET 0

#define VERTEX_COLOR_INDEX 1
#define VERTEX_COLOR_ATTR_COUNT 4
#define VERTEX_COLOR_OFFSET sizeof(glm::vec3)

#endif
