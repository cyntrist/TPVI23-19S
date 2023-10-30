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
	SDL_Rect rect;
	rect.x = position.getX();
	rect.y = position.getY();
	rect.w = texture->getFrameWidth();
	rect.h = texture->getFrameHeight();
	texture->renderFrame(rect, texture->getNumRows() * type, texture->getNumColumns());

	//std::cout << "{" << position.getX() << " ," << position.getY() << " }" << std::endl;
}

void Alien::update() { //ni idea de si esto es mejor separarlo en varios metodos y dejar el update como solo llamadas a esos metodos

	position += Vector2D<double>(game->getDirection() * alienMovSpeed, 0); //movimiento de los aliens

	if (position.getX() <= texture->getFrameWidth() ||
		position.getX() >= WIN_WIDTH - texture->getFrameWidth()) //comprobacion por si no pueden moverse mas y hay que invertir la direcccion de movimiento
		game->cannotMove();

}

void Alien::hit() {

}