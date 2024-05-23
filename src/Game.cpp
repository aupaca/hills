#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Game.h"
#include "Plane.h"

Game::Game()
	: _renderer("./src/shader/base.vert", "./src/shader/base.frag")
	, _cam({0.f, 0.f, 0.f}, 240.f)
{
	_sensivity.x = -glm::radians(90.f) / 500.f;
	_sensivity.y = -glm::radians(90.f) / 500.f;
	_camFingerId = -1;
	_updateFrame = true;
	_cam.lookAt({0.f, 0.f, 0.f});
	_cam.rotate({0.f, glm::radians(45.f)});
	
	Plane hills(155.f, 155.f, 40, 40);
	for (Vertex& v : hills.vertexList)
	{
		float x = v.pos.x;
		float z = v.pos.z;
		
		v.pos.y = 0.3f * (z * sinf(0.1f * x) + x * cosf(0.1f * z));
		if (v.pos.y < -10.f)
		{
			v.color = glm::vec4(1.f, 0.92f, 0.62f, 1.f);
		}
		else if (v.pos.y < 5.f)
		{
			v.color = glm::vec4(0.48f, 0.77f, 0.46f, 1.f);
		}
		else if (v.pos.y < 12.f)
		{
			v.color = glm::vec4(0.1f, 0.48f, 0.19f, 1.f);
		}
		else if (v.pos.y < 20.f)
		{
			v.color = glm::vec4(0.45f, 0.39f, 0.34f, 1.f);
		}
		else
		{
			v.color = glm::vec4(1.f, 1.f, 1.f, 1.f);
		}
	}
	
	_renderer.loadData(hills.vertexList, hills.wireframeIndexList);
	
	glm::mat4 proj = glm::perspective(glm::radians(45.f), anut::Engine::window->aspectRatio(), 0.1f, 1000.f);
	_renderer.setUniform("proj", proj);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	
	float lineWidthRange[2];
	glGetFloatv(GL_ALIASED_LINE_WIDTH_RANGE, lineWidthRange);
	if (lineWidthRange[1] >= 3.f)
	{
		glLineWidth(3.f);
	}
}

Game::~Game()
{
	
}

void Game::draw()
{
	_updateFrame = false;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_renderer.setUniform("view", _cam.viewMatrix());
	_renderer.draw();
}

void Game::onTouchEvent(const anut::MotionEvent& motion)
{
	glm::vec2 touchPos = glm::vec2(motion.x, motion.y);
	switch (motion.action)
	{
		case anut::MotionEvent::ACTION_DOWN:
			if (_camFingerId == -1)
			{
				_camFingerId = motion.id;
				_prevTouchPos = touchPos;
			}
			break;
			
		case anut::MotionEvent::ACTION_MOVE:
			if (motion.id == _camFingerId)
			{
				_cam.rotate(_sensivity * (_prevTouchPos - touchPos));
				_prevTouchPos = touchPos;
				_updateFrame = true;
			}
			break;
			
		case anut::MotionEvent::ACTION_UP:
			if (motion.id == _camFingerId)
			{
				_camFingerId = -1;
			}
			break;
	}
}

