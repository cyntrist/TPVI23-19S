#pragma once
#include "texture.h"
#include "Vector2D.h"

using uint = unsigned int;

class Laser
{
private:
	Point2D<double> position;
	Vector2D<double> speed;
	bool friendly;
public:
	Laser() = default;
	Laser(Point2D<double> position, Vector2D<double> speed, bool friendly);
	void render();
	void update();
};
