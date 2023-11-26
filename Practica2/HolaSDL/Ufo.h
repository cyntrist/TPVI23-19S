#pragma once
#include "SceneObject.h"

enum states { visible, hidden, destroyed };

class Ufo final: public SceneObject 
{
	int state; 
public:
	Ufo() = default;
	Ufo(Point2D<double> position, int lives, Texture* texture, Game* game, int state);
	bool update() override;
};