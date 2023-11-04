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

	// todo: random shoot...

	return true;
}

void Alien::hit() {
	destroy = true;
}