#include "Laser.h"

Laser::Laser(Point2D<double> position, Vector2D<double> speed, bool friendly) {
	this->position = position;
	this->speed = speed;
	this->friendly = friendly;
}

void Laser::render(SDL_Renderer& renderer)
{
	SDL_Rect rect;
	rect.x = position.getX();
	rect.y = position.getY();
	rect.w = 1;
	rect.y = 5;
	SDL_RenderFillRect(&renderer, &rect);
}

void Laser::update() {
	position += speed;
}
