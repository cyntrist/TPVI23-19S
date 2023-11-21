#pragma once
#include "GameObject.h"

class Mothership : public GameObject
{
	Vector2D<> direction;
	int alienCount;
	enum state {}; 
	int level;

public:
	Vector2D<> getDirection() const { return direction; }
	int getAlienCount() const { return alienCount; }
	void shouldMove();
	void cannotMove();
	void alienDied();
	void alienLanded();
	void haveLanded();
};