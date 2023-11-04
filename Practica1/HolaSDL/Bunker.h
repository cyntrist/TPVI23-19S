#pragma once
#include "texture.h"
#include "Vector2D.h"

using uint = unsigned int;

class Bunker
{
private:
	Point2D<double> position = Point2D<double>(0, 0);
	uint lives;
	Texture* texture = nullptr;
	SDL_Rect rect;

public:
	Bunker() = default;
	Bunker(const Point2D<double>& p, const uint& v, Texture*& t);
	SDL_Rect* getRect() { return &rect; }
	void render();
	bool update();
	void hit();
};