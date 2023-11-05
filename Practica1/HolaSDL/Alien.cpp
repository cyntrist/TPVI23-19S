#include "Alien.h"
#include "Game.h"

Alien::Alien(Point2D<double>& p, int tipo, Texture*& t, Game*& g) { 
	position = p;
	type = tipo;
	texture = t;
	game = g;
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
	if (destroy) return false;

	position = position + Vector2D<>(game->getDirection() * alienMovSpeed, 0); //movimiento de los aliens

	if (position.getX() <= 0 ||
		position.getX() > WIN_WIDTH - texture->getFrameWidth()) //comprobacion por si no pueden moverse mas y hay que invertir la direcccion de movimiento
		game->cannotMove();
	//state = (state + 1) % 2;

	if (type == 0) {
		// todo: random shoot...
		if (timer <= 0)
			timer = game->getRandomRange(1000, 10000); //IMPORTANTE: el min y max son numero de frames, si hacemos que despues de cada update haya delay entonces tenemos que bajar estos numeros mucho
		else
			timer--;

		if (timer <= 0) { //se que esta feo de narices pero si lo ponia dentro de la comprobacion anterior todos los aliens disparaban en la primera iteracion (supongo que iniciando los aliens ya con un valor del random se solucionaria, pero no conseguia hacerlo)
			Point2D<double> pos(position.getX() + (texture->getFrameWidth() - LASER_WIDTH) / 2, position.getY() + texture->getFrameHeight());
			game->fireLaser(pos, Vector2D<>(0, laserMovSpeed), false);
		}
	}

	return true;
}

void Alien::hit() {
	destroy = true;
}