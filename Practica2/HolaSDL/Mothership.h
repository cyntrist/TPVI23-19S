#pragma once
#include "GameObject.h"
#include "Vector2D.h"

enum state {}; // ...

class Mothership : public GameObject
{
	Vector2D<> direction;
	int alienCount;
	int state;
	int level;

public:
	Mothership() = default;
	Mothership(Vector2D<> direction, int alienCount, int state, int level, Game* game);
	Vector2D<> getDirection() const { return direction; }
	int getAlienCount() const { return alienCount; }
	void shouldMove();
	void cannotMove();
	void alienDied();
	void alienLanded();
	void haveLanded();
};
