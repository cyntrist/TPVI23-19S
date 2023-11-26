#pragma once
#include "GameObject.h"
#include "Vector2D.h"
class Alien;

enum state {}; // ...

class Mothership : public GameObject
{
	int direction;
	int alienCount;
	int state;
	int level;

public:
	Mothership() = default;
	Mothership(int direction, int alienCount, int state, int level, Game* game);
	void update() override { } // para que no se queje por ser abstracta pura
	void render() const override {} // para que no se queje por ser abstracta pura
	int getDirection() const { return direction; }
	int getAlienCount() const { return alienCount; }
	bool shouldMove();
	bool cannotMove();
	void alienDied();
	bool alienLanded(const Alien*& alien);
	bool haveLanded(); // ??????? no se si es que en el enunciado se equivoca y lo llama de dos maneras distintas pero se supone que hay dos metodos
};
