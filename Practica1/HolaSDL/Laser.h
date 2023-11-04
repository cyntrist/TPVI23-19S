#pragma once
#include "texture.h"
#include "Vector2D.h"

using uint = unsigned int;

class Laser
{
private:
	Point2D<double> position;
	Vector2D<> speed;
	bool friendly;
	SDL_Rect rect;

public:
	Laser() = default;
	Laser(Point2D<double> position, Vector2D<> speed, bool friendly);
	SDL_Rect getRect() { return rect; }
	void render(SDL_Renderer &renderer);
	void update();
};
