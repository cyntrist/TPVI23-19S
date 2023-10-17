#pragma once
#include "Game.h"
#include "texture.h"
#include "Vector2D.h"

class Alien
{
private:
	Point2D position;
	int type;
	Texture* texture;
	Game* game;
public:
	Alien();
	render();
	update();
	hit();
};
