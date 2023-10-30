#include "Bunker.h"

using namespace std;

Bunker::Bunker(const Point2D<double>& p, const uint& v, Texture*& t) {
	position = p;
	lives = v;
	texture = t; 
}

bool Bunker::update()
{
	if (lives <= 0) return false;
	return true;
}

void Bunker::render() const
{
	SDL_Rect rect;
	rect.x = position.getX();
	rect.y = position.getY();
	rect.w = texture->getFrameWidth();
	rect.h = texture->getFrameHeight();
	texture->renderFrame(rect, texture->getNumRows() - 1, texture->getNumColumns() - lives);
}

void Bunker::hit()
{
	lives--;
}
