#include "checkML.h"
#include "Bunker.h"

Bunker::Bunker(const Point2D<double>& position, int lives, Texture* texture, Game* game)
	: SceneObject(position, lives, texture, game) { }

void Bunker::render() const
{
	texture->renderFrame(rect, texture->getNumRows() - 1, texture->getNumColumns() - lives - 1);
}
