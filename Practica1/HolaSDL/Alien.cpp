#include "Alien.h"
#include "Game.h"

Alien::Alien(const Point2D<double>& position, const int& type, Texture*& texture, Game*& game) { 
	this->position = position;
	this->type = type;
	this->texture = texture;
	this->game = game;
}

void Alien::render()
{
	rect.x = position.getX();
	rect.y = position.getY();
	rect.w = texture->getFrameWidth();
	rect.h = texture->getFrameHeight();
	texture->renderFrame(rect, type, state);
}

bool Alien::update() { //ni idea de si esto es mejor separarlo en varios metodos y dejar el update como solo llamadas a esos metodos
	if (destroy) return false; // hit

	if (game->getAlienUpdateTimer() <= 0)
	{
		position = position + Vector2D<>(game->getDirection() * ALIEN_MOV_SPEED, 0); //movimiento de los aliens
		state = (state + 1) % 2; // animacion

		if (type == 0) { // random shoot:
			if (shootingTimer <= 0)
				shootingTimer = game->getRandomRange(0.1 * TIME_BETWEEN_FRAMES, 2 * TIME_BETWEEN_FRAMES); //IMPORTANTE: el min y max son numero de frames de update del alien, es decir, el alien disparara una vez cada x updates entre ese rango
			else
				shootingTimer--;

			if (shootingTimer <= 0) { //se que esta feo de narices pero si lo ponia dentro de la comprobacion anterior todos los aliens disparaban en la primera iteracion (supongo que iniciando los aliens ya con un valor del random se solucionaria, pero no conseguia hacerlo)
				Point2D<double> pos(position.getX() + (texture->getFrameWidth() - LASER_WIDTH) / 2, position.getY() + texture->getFrameHeight());
				game->fireLaser(pos, Vector2D<>(0, LASER_MOV_SPEED), false);
			}
		}
	}
	return true;
}