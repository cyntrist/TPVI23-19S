#pragma once
#include "Game.h"
#include "texture.h"
#include "Vector2D.h"

using uint = unsigned int;

class Cannon
{
private:
	Point2D position;
	Texture* texture;
	Game* game;

	int movement; // int?	
	uint lives;
	uint timer;

public:
	Cannon();
	render();
	update();
	hit();
	handleEvent();
};