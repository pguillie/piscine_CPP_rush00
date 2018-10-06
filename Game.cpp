#include "Game.hpp"
#include <curses.h>
#include <ctime>
#include <iostream>
#include <sstream>

Game::Game(void) :
	_deltaTime(0),
	_last_clock(std::clock() / CLOCKS_PER_SEC),
	_fixed_clock(0)
{
	initscr();
	cbreak();
	noecho();
	nonl();
	intrflush(stdscr, FALSE);
	keypad(stdscr, TRUE);
}

Game::~Game(void)
{
	endwin();
}

bool Game::Continue()
{
	return _is_running;
}

void Game::Run()
{
	float fps = 1 / 60;

	while (42)
	{
		std::clock_t current = std::clock();
		std::clock_t deltaTime = current - _last_clock;

		_fixed_clock += deltaTime;
		PreRender();
			if (_fixed_clock > fps)
			{
				_fixed_clock = 0;
				FixedUpdate();
			}
			Update(float(deltaTime));
		Render();
		PostRender();

		_last_clock = current;
		_deltaTime = deltaTime;
	}
	Render();
}

void Game::PreRender(void)
{
	clear();
}

void Game::Render(void)
{
}

void Game::PostRender(void)
{
	refresh();
}

void Game::Update(float deltaTime)
{
	std::stringstream ss;

	ss << "Update " << deltaTime << std::endl;
	addstr(ss.str().c_str());
}

void Game::FixedUpdate(void)
{
	addstr("FixedUpdate\n");
}
