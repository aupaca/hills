#include "Renderer.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Renderer::Renderer(const char* vertShaderPath, const char* fragShaderPath)
	: _vertexArray(GL_ARRAY_BUFFER), _indexArray(GL_ELEMENT_ARRAY_BUFFER)
{
	if (!_glsl.compile(vertShaderPath, fragShaderPath))
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
	_layout.drawIndexed(GL_LINE_STRIP, _indexCount, GL_UNSIGNED_INT);
}

