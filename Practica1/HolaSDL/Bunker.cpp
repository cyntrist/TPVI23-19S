#include "Bunker.h"

using namespace std;

Bunker::Bunker(const uint v, Texture* t) {
	position = Point2D<uint>(0, 0);
	lives = v;
	texture = t; 
}

Bunker::Bunker(Point2D p, const uint v, Texture* t) {
	position = p;
	lives = v;
	texture = t; 
}

bool Bunker::update()
{
	if (lives <= 0) return false;
	return true;
}

void Bunker::render(const SDL_Rect& rect) const
{
	texture->renderFrame(rect, 1, 3 - lives);
}

void Bunker::hit()
{
	lives--;
}
