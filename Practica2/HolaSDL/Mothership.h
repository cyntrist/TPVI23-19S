#pragma once
#include "GameObject.h"
#include "Vector2D.h"
#include "Alien.h"
class Game;

//enum states {}; // ...????? lo del enum ciclico... jiji

class Mothership : public GameObject
{
	int direction; // direccion de movimiento de los aliens
	int alienCount; // numero de aliens
	int state; 
	int level; // nivel de bajada de los aliens
	int movementTimer; // temporizador de movimento de los aliens
	bool switchDir; // si ha de cambiar la direccion

public:
	Mothership() = default;
	Mothership(int direction, int alienCount, int state, int level, Game* game, int movementTimer);
	void update() override;
	void render() const override {} 
	void save(std::ostream& os) const override;
	bool shouldMove() const;
	void cannotMove();
	void alienDied() { alienCount--; }
	void alienLanded(const Alien* alien) const;
	bool haveLanded() const;
	// getters
	int getDirection() const { return direction; }
	int getAlienCount() const { return alienCount; }
	int getLevel() const { return level; }
	//setters
	void setDirection(int value) { direction = value; }
	void addAlienCount() { alienCount++; }
	};
