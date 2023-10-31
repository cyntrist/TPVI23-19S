#include "Laser.h"

Laser::Laser(Point2D<double> position, Vector2D<double> speed, bool friendly) {
	this->position = position;
	this->speed = speed;
	this->friendly = friendly;
}

void Laser::render(SDL_Renderer& renderer)
{
	SDL_SetRenderDrawColor(&renderer, 0, 0, 255, 255);
	SDL_Rect rect;
	rect.x = position.getX();
	rect.y = position.getY();
	rect.w = 5;
	rect.y = 15;
	SDL_RenderFillRect(&renderer, &rect);
}

void Laser::update() {
	position = position + speed;
}
