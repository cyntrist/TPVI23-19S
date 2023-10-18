#pragma once
#include "Game.h"
#include "texture.h"
#include "Vector2D.h"

class Alien
{
private:
	Point2D position;
	int type;
	Texture* texture = nullptr;
	Game* game = nullptr;
public:
	Alien();
	void render();
	void update();
	void hit();
};
