#pragma once

#include "texture.h"
using uint = unsigned int;

class Bunker
{
private:
	// Point2D
	uint lives;
	Texture* texture;

public:
	Bunker(uint v, Texture* t);
	void render() const;
	bool update();
	void hit();
};