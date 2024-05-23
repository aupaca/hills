#include "MainActivity.h"
#include "Game.h"

void MainActivity::onSurfaceCreated()
{
	anut::Engine::window->setFlags(AWINDOW_FLAG_FULLSCREEN, AWINDOW_FLAG_FULLSCREEN);
	_game = new Game;
}

void MainActivity::onSurfaceDestroyed()
{
	delete _game;
}

void MainActivity::onTouchEvent(const anut::MotionEvent& motion)
{
	_game->onTouchEvent(motion);
}

void MainActivity::onUpdate()
{
	if (_game->needRedraw())
	{
		_game->draw();
		anut::Engine::window->display();
	}
}

