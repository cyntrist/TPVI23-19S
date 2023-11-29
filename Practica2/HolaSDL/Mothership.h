#pragma once
#include "GameObject.h"
#include "Vector2D.h"
#include "Alien.h"
class Game;

//enum state {}; // ...????? lo del enum ciclico... jiji

class Mothership : public GameObject
{
	int direction;
	int alienCount;
	int state;
	int level;
	int movementTimer;
	bool switchDir;

public:
	Mothership() = default;
	Mothership(int direction, int alienCount, int state, int level, Game* game, int movementTimer);
	void update() override;
	void render() const override {} 
	void save(std::ostream& os) const override;
	bool shouldMove() const;
	void cannotMove();
	void alienDied() { alienCount--; }
	bool alienLanded(const Alien*& alien);
	bool haveLanded();
	// getters
	int getDirection() const { return direction; }
	int getAlienCount() const { return alienCount; }
	//setters
	void setDirection(int value) { direction = value; }
	//void setAlienCount(int value) { alienCount = value; }
	void addAlienCount() { alienCount++; }
	};
