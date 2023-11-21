#include "checkML.h"
#include "Bunker.h"

Bunker::Bunker(const Point2D<double>& position, int lives, Texture* texture) {
	this->position = position;
	this->lives = lives;
	this->texture = texture; 
}

void Bunker::render() const
{
	SceneObject::render(texture->getNumRows() - 1, texture->getNumColumns() - lives - 1);
}
