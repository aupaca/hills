#ifndef GAME_H
#define GAME_H
#include <ANUT/ANUT.h>
#include <glm/glm.hpp>
#include "Renderer.h"
#include "OrbitCamera.h"

class Game
{
public:
	Game();
	~Game();
	
	bool needRedraw() const;
	void draw();
	void handleTouch(const anut::MotionEvent& motion);
	
private:
	glm::vec2 _sensivity;
	glm::vec2 _prevTouchPos;
	int _camFingerId;
	OrbitCamera _cam;
	Renderer _renderer;
	bool _updateFrame;
};


inline bool Game::needRedraw() const
{
	return _updateFrame;
}

#endif
