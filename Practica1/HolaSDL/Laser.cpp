#include "Laser.h"

Laser::Laser(Point2D<double> position, Vector2D<double> speed, bool friendly) {
	this->position = position;
	this->speed = speed;
	this->friendly = friendly;
}

void Laser::render(SDL_Renderer& renderer)
{
	if (friendly)
		SDL_SetRenderDrawColor(&renderer, 255, 0, 0, 255);
	else
		SDL_SetRenderDrawColor(&renderer, 0, 0, 255, 255);

	rect.x = position.getX();
	rect.y = position.getY();
	rect.w = LASER_WIDTH;
	rect.h = LASER_HEIGHT;
	SDL_RenderFillRect(&renderer, &rect);
}

bool Laser::update() {
	position = position + speed;
	return true;
}
