#ifndef GAME_H
#define GAME_H

#include <ctime>

class Game
{
	public:
		Game(void);
		~Game(void);

		void Run();
		void FixedUpdate(void);
		void Update(float deltaTime);

		void Render(void);

		bool Continue();
	private:
		bool _is_running;
		float _deltaTime;

		void PreRender(void);
		void PostRender(void);

	private:
		Game(Game const &src);
		Game &operator=(Game const &rhs);
		std::clock_t _last_clock;
		std::clock_t _fixed_clock;
};

#endif /* GAME_H */
