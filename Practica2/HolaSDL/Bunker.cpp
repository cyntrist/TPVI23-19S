#include "checkML.h"
#include "Bunker.h"
#include "Game.h"

Bunker::Bunker(const Point2D<>& position, int lives, Texture* texture, Game* game)
	: SceneObject(position, lives, texture, game) { }

void Bunker::render() const
{
	texture->renderFrame(rect, texture->getNumRows() - 1, std::clamp(texture->getNumColumns() - lives, 0, texture->getNumColumns() - 1));
}

void Bunker::update() {
	if (lives <= 0)
		game->hasDied(iterator);
	updateRect();
}
