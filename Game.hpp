#ifndef GAME_H
#define GAME_H

#include "Entity.hpp"
#include <ctime>

typedef struct s_entity {
	Entity *entity;
	struct s_entity *next;
	struct s_entity *prev;
} t_entity;

class Player;

class Game
{
	public:
		Game(void);
		virtual ~Game(void);

		void Run(void);
		virtual void Update(float deltaTime);
		void updatePlayer(float deltaTime);
		void Stop(void);
		t_entity * registerEntity(Entity *e, t_entity *type);
		t_entity * removeEntity(t_entity *e, t_entity **type);
		void registerPlayer(Player *p);
		void checkCollisions(void);

	private:
		bool _is_running;
		float _deltaTime;

		void PreRender(void);
		void Render(void);
		void PostRender(void);
		void renderEntity(Entity &e);
		void renderHud(void) const;
		void initBackground(void);

	private:
		Game(Game const &src);
		Game &operator=(Game const &rhs);

		std::clock_t _last_clock;
		Player *_player;
		t_entity *_missiles;
		t_entity *_enemies;
		t_entity *_background;
		int _height;
		int _width;
};

#endif /* GAME_H */
