#include "checkML.h"
#include "Laser.h"
#include "Game.h"

Laser::Laser(Point2D<double>& position, Vector2D<>& speed, char color, Game* game)
: SceneObject(position, 1, nullptr, game), speed(speed), color(color) { }

void Laser::updateRect()
{
	rect.x = position.getX();
	rect.y = position.getY();
	rect.w = LASER_WIDTH;
	rect.h = LASER_HEIGHT;
}

void Laser::render(SDL_Renderer& renderer) const 
{
	SDL_SetRenderDrawColor(&renderer, 0, 0, 255, 255);
	if (color == FRIENDLY_CHAR)
		SDL_SetRenderDrawColor(&renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(&renderer, &rect);
}

bool Laser::update() {
	position = position + speed;
	updateRect();
	if (position.getY() < 0) return false;  // si se sale por arriba
	return !destroy && !game->collisions(this);
	// llama a las colisiones totales, y si ha colisionado, sera destruido en el propio game
}