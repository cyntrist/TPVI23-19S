#pragma once
#include "texture.h"
#include "Vector2D.h"
//#include "Game.h"
class Game; // para evitar dependencia circular (la línea de arriba)

using uint = unsigned int;

class Cannon
{
private:
	Point2D<double> position;
	Texture* texture = nullptr;
	Game* game = nullptr;

	int movement; // int?	
	uint lives;
	uint timer;

public:
	Cannon() = default;
	Cannon(const Point2D<double>& p, const uint& l, Texture*& t, Game*& g);
	void render();
	void update();
	void hit();
	void handleEvent();
};