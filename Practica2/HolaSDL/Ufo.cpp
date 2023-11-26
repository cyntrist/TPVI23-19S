#include "Ufo.h"
#include "Game.h"

Ufo::Ufo(Point2D<double> position, int lives, Texture* texture, Game* game, int state)
: SceneObject(position, lives, texture, game), state(state) { }

bool Ufo::update()
{ // todo: todo XD
	return true;
}