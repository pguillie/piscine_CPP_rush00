#ifndef ENEMY_H
#define ENEMY_H

#include "Character.hpp"

class Enemy : public Character
{
	public:
		Enemy(coord pos, movement dir, int speed, std::string design);
		~Enemy(void);

		Enemy &operator=(Enemy const &rhs);

		Missile * shoot(float timeLapse);

	private:
		Enemy(void);
		Enemy(Enemy const &src);
		int _attackSpeed;
		int _timeUntilAttack;
};

#endif /* ENEMY_H */
