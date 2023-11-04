#pragma once
#include "Laser.h"
#include "texture.h"
#include "Vector2D.h"
//#include "Game.h"
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

public:
	Alien() = default;
	Alien(Point2D<double>& p, int type, Texture*& t, Game*& game);
	SDL_Rect getRect() { return rect; }
	void render();
	bool update();
	bool hit();
};
