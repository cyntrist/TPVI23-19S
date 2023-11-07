#pragma once
#include "Laser.h"
#include "texture.h"
#include "Vector2D.h"
class Game;

using uint = unsigned int;

class Alien
{
private:
	Point2D<double> position;
	int type;
	Texture* texture = nullptr;
	Game* game = nullptr;
	int state = 0; // estado de animacion
	SDL_Rect rect; // rectangulo de hitbox
	bool destroy = false; // si ha de ser destruido
	double shootingTimer;

public:
	Alien() = default;
	Alien(const Point2D<double>& position, const int& type, Texture*& texture, Game*& game);
	void render();
	bool update();
	void hit() { destroy = true; }
	SDL_Rect* getRect() { return &rect; }
	Point2D<double> getPos() const { return position; }
	int getType() const { return type; }
};
