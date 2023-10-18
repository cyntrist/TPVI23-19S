#pragma once
#include "Game.h"
#include "texture.h"
#include "Vector2D.h"

using uint = unsigned int;

class Alien
{
private:
	Point2D<double> position;
	int type;
	Texture* texture = nullptr;
	//Game* game = nullptr;
public:
	Alien();
	void render();
	void update();
	void hit();
};
