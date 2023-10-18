#pragma once
#include "texture.h"
#include "Vector2D.h"

using uint = unsigned int;

class Bunker
{
private:
	Point2D<uint> position;
	uint lives;
	Texture* texture = nullptr;

public:
	Bunker(Point2D p, uint v, Texture* t);
	void render() const;
	bool update();
	void hit();
};