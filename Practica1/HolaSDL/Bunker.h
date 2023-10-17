#pragma once

#include "texture.h"
using uint = unsigned int;

class Bunker
{
private:
	// Point2D
	uint vidas;
	Texture* textura;

public:
	Bunker(uint v);
	~Bunker();
	void render() const;
	bool update();
	void hit();
};