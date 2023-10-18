#pragma once
#include "texture.h"
#include "Vector2D.h"

using uint = unsigned int;

class Laser
{
private:
	Point2D<uint> position;
	Vector2D<uint> speed;
	bool friendly;
public:
	Laser();
	void render();
	void update();
};
