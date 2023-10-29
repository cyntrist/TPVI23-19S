#pragma once
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

public:
	Alien() = default;
	Alien(Point2D<double>& p, int type, Texture*& t, Game*& game);
	void render();
	void update();
	void hit();
};
