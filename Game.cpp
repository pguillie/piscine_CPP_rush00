#include "Game.hpp"
#include "Entity.hpp"
#include "Character.hpp"
#include "Enemy.hpp"
#include "Missile.hpp"
#include "Player.hpp"
#include "Weapon.hpp"
#include <iostream>
#include <sstream>
#include <curses.h>
#include <unistd.h>

extern int g_sig;

Game::Game(void) :
	_deltaTime(0),
	_last_clock(std::clock()),
	_score(0),
	_height(LINES),
	_width(COLS)
{
	initscr();
	cbreak();
	noecho();
	nonl();
	intrflush(stdscr, FALSE);
	nodelay(stdscr, TRUE);
	keypad(stdscr, TRUE);
	curs_set(FALSE);
	start_color();
	init_pair(RED, COLOR_RED, COLOR_BLACK);
	init_pair(GREEN, COLOR_GREEN, COLOR_BLACK);
	getmaxyx(stdscr, _height, _width);
	_height -= 1;
	_width -= 1;
	_missiles = NULL;
	_enemies = NULL;
	initBackground();
	coord position;
	position.y = _height - 10;
	position.x = (_width - 1) / 2 - 2;
	_player = new Player(position, "/==A==\\");
}

Game::~Game(void)
{
	endwin();
	t_entity * e(_missiles);
	t_entity * tmp;
	while (e) {
		delete e->entity;
		tmp = e;
		e = e->next;
		delete tmp;
	}
	e = _enemies;
	while (e) {
		delete e->entity;
		tmp = e;
		e = e->next;
		delete tmp;
	}
	delete _player;
}

void Game::Run(void)
{
	srand(time(0));
	_player->setWeapon(new Weapon(300));
	_player->getWeapon()->setColor(GREEN);
	_is_running = true;
	while (_is_running && g_sig == 0)
	{
		std::clock_t current = std::clock();
		float deltaTime = (current - _last_clock) / 100000.00f;

		Update(deltaTime);
		Render();
		PostRender();

		_last_clock = current;
		_deltaTime = deltaTime;
		usleep(10000);
	}
	move(_height / 2 - 1, (_width - 9) / 2);
	addstr("GAME OVER");
	move(_height / 2 + 1, (_width - 21) / 2);
	addstr("press HomeKey to exit");
	while ((getch() != KEY_HOME))
		;
}

void Game::newStar(coord position) {
	Missile * star;
	int type(rand() % 100);
	if (type < 15)
		star = new Missile(position, DOWN, 3, "*");
	else if (type < 42)
		star = new Missile(position, DOWN, 2, "+");
	else
		star = new Missile(position, DOWN, 1, ".");
	_background = registerEntity(star, _background);
}

void Game::initBackground()
{
	_background = NULL;
	coord pos;
	for (int y(1); y < _height - 1; y++) {
		for (int i(0); i < 42; i++) {
			if (rand() % 1000 < 42) {
				pos.y = y;
				pos.x = rand() % (_width - 2) + 1;
				newStar(pos);
			}
		}
	}
}

void Game::renderEntity(Entity &e)
{
	move(e.getPosition().y, e.getPosition().x);
	int color(e.getColor());
	attron(COLOR_PAIR(color) | A_BOLD);
	addstr(e.getDesign().c_str());
	attroff(COLOR_PAIR(color) | A_BOLD);
}

void Game::Render(void)
{
	erase();
	renderEntity(*_player);
	t_entity * e;
	e = _background;
	while (e) {
		renderEntity(*(e->entity));
		e = e->next;
	}
	e = _missiles;
	while (e) {
		renderEntity(*(e->entity));
		e = e->next;
	}
	e =_enemies;
	while (e) {
		renderEntity(*(e->entity));
		e = e->next;
	}
}

void Game::PostRender(void)
{
	box(stdscr, 0, 0);
	renderHud();
	refresh();
}

void Game::updatePlayer(float deltaTime) {
	int ch = getch();
	switch (ch) {
	case KEY_UP:
		_player->setDirection(UP);
		break;
	case KEY_DOWN:
		_player->setDirection(DOWN);
		break;
	case KEY_RIGHT:
		_player->setDirection(RIGHT);
		break;
	case KEY_LEFT:
		_player->setDirection(LEFT);
		break;
	case 27:
		_is_running = false;
		break;
	case 113:
		_is_running = false;
		break;
	case 32:
		Missile * missile = _player->shoot(deltaTime);
		if (missile)
			_missiles = registerEntity(missile, _missiles);
		break;
	}
	_player->move(deltaTime, _height, _width);
}

void Game::Update(float deltaTime)
{
	updatePlayer(deltaTime);

	t_entity * e(_missiles);
	while (e)
	{
		if (e->entity->move(deltaTime, _height, _width) < 0)
			e = removeEntity(e, &_missiles);
		else
			e = e->next;
	}
	e = _enemies;
	while (e)
	{
		Enemy *en = (Enemy *)e->entity;
		if (en->move(deltaTime, _height, _width) < 0)
			e = removeEntity(e, &_enemies);

	 	else
 		{
			e = e->next;
			Missile *m = en->shoot(deltaTime);
			if (m)
				_missiles = registerEntity(m, _missiles);
 		}
	}
	e = _background;
	while (e) {
		if (e->entity->move(deltaTime, _height, _width) < 0)
			e = removeEntity(e, &_background);
		else
			e = e->next;
	}
	
	// create enemies
	if (rand() % 1000 > 950) {
		coord position;
		position.y = 0;
		Enemy * character;
		if (rand() % 2 == 0) {
			position.x = rand() % (_width - 2 - 5) + 1;
			character = new Enemy(position, DOWN, (rand() % 42 + 100) / 10, "(-0-)");
		}
		else {
			position.x = rand() % (_width - 2 - 3) + 1;
			character = new Enemy(position, DOWN, (rand() % 100 + 200) / 10, "<0>");
		}
		_enemies = registerEntity(character, _enemies);
	}

	// create background
	if (rand() % 1000 < 42) {
		coord position;
		position.y = 0;
		position.x = rand() % (_width - 2) + 1;
		newStar(position);
	}

	checkCollisions();
}

void Game::Stop(void)
{
	_is_running = false;
}

void Game::registerPlayer(Player *p)
{
	_player = p;
}

t_entity * Game::registerEntity(Entity *e, t_entity *type)
{
	if (type) {
		t_entity * list(type);
		while (list->next)
			list = list->next;
		list->next = new t_entity;
		list->next->entity = e;
		list->next->next = NULL;
		list->next->prev = list;
	} else {
		type = new t_entity;
		type->entity = e;
		type->next = NULL;
		type->prev = NULL;
	}
	return type;
}

t_entity * Game::removeEntity(t_entity *e, t_entity ** type)
{
	t_entity * next(e->next);

	if (e->prev)
		e->prev->next = e->next;
	else
		*type = e->next;
	if (e->next)
		e->next->prev = e->prev;
	delete e->entity;
	delete e;
	return next;
}

bool isACollision(Entity * a, Entity * b) {
	int yA = a->getPosition().y;
	int yB = b->getPosition().y;
	if ((yA == yB)
		|| (a->getDirection() == UP && b->getDirection() == DOWN && yA == yB - 1)
		|| (a->getDirection() == DOWN && b->getDirection() == UP && yA == yB + 1)) {
		int aLeftEnd(a->getPosition().x);
		int bLeftEnd(b->getPosition().x);
		int aRightEnd(aLeftEnd + a->getDesign().length());
		int bRightEnd(bLeftEnd + b->getDesign().length());
		if ((aLeftEnd >= bLeftEnd && aLeftEnd <= bRightEnd)
			|| (aRightEnd >= bLeftEnd && aRightEnd <= bRightEnd))
			return (true);
	}
	return (false);
}

void Game::checkCollisions(void)
{
	t_entity * missile(_missiles);
	while (missile) {
		Entity * a = missile->entity;
		bool collides(false);
		t_entity * character(_enemies);
		while (character) {
			Entity * b = character->entity;
			if (isACollision(a, b)) {
				collides = true;
				character = removeEntity(character, &_enemies);
				_score += 1;
			} else
				character = character->next;
		}
		if (isACollision(a, _player)) {
			collides = true;
			_is_running = false;
		}
		if (collides)
			missile = removeEntity(missile, &_missiles);
		else
			missile = missile->next;
	}
	t_entity * enemy(_enemies);
	while (enemy) {
		Entity * a = enemy->entity;
		bool collides(false);
		t_entity * others(_enemies);
		while (others) {
			Entity * b = others->entity;
			if (a != b && isACollision(a, b)) {
				collides = true;
				others = removeEntity(others, &_enemies);
			} else
				others = others->next;
		}
		if (isACollision(a, _player)) {
			collides = true;
			_is_running = false;
		}
		if (collides)
			enemy = removeEntity(enemy, &_enemies);
		else
			enemy = enemy->next;
	}
		
}

void Game::renderHud(void) const
{
	std::stringstream ss;

	move(_height, 1);
	std::clock_t c = std::clock() / 100000;
	ss << " TIME " << c << " | " << "SCORE " << _score << " ";

	addstr(ss.str().c_str());
}
