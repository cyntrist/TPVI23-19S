#include "Bunker.h"

Bunker::Bunker(const Point2D<double>& position, const int& lives, Texture*& texture) {
	this->position = position;
	this->lives = lives;
	this->texture = texture; 
}

bool Bunker::update() const
{
	if (lives >= 0)
		return true;
	return false;
}

void Bunker::render() 
{
	rect.x = position.getX();
	rect.y = position.getY();
	rect.w = texture->getFrameWidth();
	rect.h = texture->getFrameHeight();
	texture->renderFrame(rect, texture->getNumRows() - 1, texture->getNumColumns() - lives - 1);
}
