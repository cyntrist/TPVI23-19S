#pragma once
#include "texture.h"
#include "Vector2D.h"

class Bunker
{
private:
	Point2D<double> position = Point2D<double>(0, 0);
	int lives;
	Texture* texture = nullptr;
	SDL_Rect rect;

public:
	Bunker() = default;
	Bunker(const Point2D<double>& position, const int& lives, Texture*& texture);
	SDL_Rect* getRect() { return &rect; }
	void render();
	bool update() const;
	void hit() { lives--; }
	Point2D<double> getPos() { return position; }
	int getLives() { return lives; }
};