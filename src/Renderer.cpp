#include "Renderer.h"
#include <ANUT/ANUT.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Renderer::Renderer()
	: _vertexArray(GL_ARRAY_BUFFER), _indexArray(GL_ELEMENT_ARRAY_BUFFER)
{
	if (!_glsl.compile("./src/shader/base.vert", "./src/shader/base.frag"))
	{
		// TODO: throw error
		return;
	}
	
	_shader = _glsl.shaderId();
	_shader.use();
	
	_indexCount = 0;
	_layout.indexBuffer(_indexArray);
	_layout.vertexBuffer(VERTEX_POS_INDEX, _vertexArray, VERTEX_POS_ATTR_COUNT, GL_FLOAT, false, sizeof(Vertex), VERTEX_POS_OFFSET);
	_layout.vertexBuffer(VERTEX_COLOR_INDEX, _vertexArray, VERTEX_COLOR_ATTR_COUNT, GL_FLOAT, false, sizeof(Vertex), VERTEX_COLOR_OFFSET);
	
	glm::mat4 proj = glm::perspective(glm::radians(45.f), anut::Engine::window->aspectRatio(), 0.1f, 1000.f);
	setUniform("proj", proj);
	
	float lineWidthRange[2];
	glGetFloatv(GL_ALIASED_LINE_WIDTH_RANGE, lineWidthRange);
	if (lineWidthRange[1] >= 3.f)
	{
		glLineWidth(3.f);
	}
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glEnable(GL_DEPTH_TEST);
}

Renderer::~Renderer()
{
	
}

void Renderer::loadData(const std::vector<Vertex>& vertexList, const std::vector<unsigned>& indexList)
{
	_indexCount = indexList.size();
	_vertexArray.alloc(vertexList.size() * sizeof(Vertex), GL_STATIC_DRAW, vertexList.data());
	_indexArray.alloc(_indexCount * sizeof(unsigned), GL_STATIC_DRAW, indexList.data());
}

void Renderer::setUniform(const char* name, const glm::mat4& value)
{
	glUniformMatrix4fv(_shader.uniform(name), 1, false, glm::value_ptr(value));
}

void Renderer::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_layout.drawIndexed(GL_LINE_STRIP, _indexCount, GL_UNSIGNED_INT);
}

