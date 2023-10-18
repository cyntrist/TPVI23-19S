#pragma once
#include "texture.h"
#include "Vector2D.h"
//#include "Game.h"
class Game;

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
	void render();
	void update();
	void hit();
	void handleEvent();
};