#include "checkML.h"
#include "Laser.h"
#include "Game.h"

Laser::Laser(Point2D<double>& position, Vector2D<>& speed, bool friendly, Game* game) {
	this->position = position;
	this->speed = speed;
	this->friendly = friendly;
	this->game = game;
}

void Laser::render(SDL_Renderer& renderer)
{
	SDL_SetRenderDrawColor(&renderer, 0, 0, 255, 255);
	if (friendly)
		SDL_SetRenderDrawColor(&renderer, 255, 0, 0, 255);

	rect.x = position.getX();
	rect.y = position.getY();
	rect.w = LASER_WIDTH;
	rect.h = LASER_HEIGHT;
	SDL_RenderFillRect(&renderer, &rect);
}

bool Laser::update() {
	position = position + speed;
	if (position.getY() < 0) return false;  // si se sale por arriba
	return !destroy && !game->collisions(this);
	// llama a las colisiones totales, y si ha colisionado, sera destruido en el propio game
}