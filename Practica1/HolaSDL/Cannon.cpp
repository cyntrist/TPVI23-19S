#include "Cannon.h"

Cannon::Cannon(const Point2D<double>& p, const uint& l, Texture*& t, Game*& g) {
	position = p;
	lives = l;
	texture = t;
	game = g;
}

void Cannon::render()
{
SDL_Rect rect;
	rect.x = position.getX();
	rect.y = position.getY();
	rect.w = texture->getFrameWidth();
	rect.h = texture->getFrameHeight();
	texture->renderFrame(rect, texture->getNumRows() - 1, texture->getNumColumns() - 1);
}

void Cannon::update()
{
	
}

void Cannon::hit()
{
	
}

void Cannon::handleEvent()
{
	
}


