#include "Game.h"

Alien::Alien(const Point2D<double>& p, int tipo, Texture*& t, Game*& g) {
	position = p;
	type = tipo;
	texture = t;
	game = g;
}

void Alien::render()
{
	SDL_Rect rect;
	rect.x = position.getX();
	rect.y = position.getY();
	rect.w = texture->getFrameWidth();
	rect.h = texture->getFrameHeight();
	texture->renderFrame(rect, texture->getNumRows() * type, texture->getNumColumns());
}

void Alien::update() {
	position += Vector2D<double>(game->getDirection()*alienMovSpeed, 0);

}

void Alien::hit() {

}
