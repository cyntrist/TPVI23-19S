#pragma once
#include "GameObject.h"
#include "Vector2D.h"
class Alien;
class Game;

//enum state {}; // ...????? lo del enum c�clico... jiji

class Mothership final : public GameObject
{
	int direction;
	int alienCount;
	int state;
	int level;
	int movementTimer;

public:
	Mothership() = default;
	Mothership(int direction, int alienCount, int state, int level, Game* game, int movementTimer);
	void update() override; // para que no se queje por ser abstracta pura
	void render() const override {} // para que no se queje por ser abstracta pura
	void save(std::ostream& os) const override {}
	bool shouldMove();
	bool cannotMove();
	void alienDied();
	bool alienLanded(const Alien*& alien);
	bool haveLanded(); // ??????? no se si es que en el enunciado se equivoca y lo llama de dos maneras distintas pero se supone que hay dos metodos
	// getters
	int getDirection() const { return direction; }
	int getAlienCount() const { return alienCount; }
	//setters
	void setDirection(int value) { direction = value; }
	void setAlienCount(int value) { alienCount = value; }
	void addAlienCount() { alienCount++; }
	};
