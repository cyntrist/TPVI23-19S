#include "Laser.h"

Laser::Laser(Point2D<double> position, Vector2D<double> speed, bool friendly) {
	this->position = position;
	this->speed = speed;
	this->friendly = friendly;
}

void Laser::render()
{
	//SDL_RenderDrawLine(renderer, position.getX(), position.getY(), position.getX(), position.getY() + 5); 
	//como el laser no tiene textura y es solo una linea de pixeles pues he pensado en hacerlo asi pero yo que se lo mismo hay que hacerlo con la clase texture. Falta acceder al renderer del game supongo? ns me duele la cabeza, tmb ese 5 es por poner una longitud de laser cualquiera, aunque lo mismo se hace con la speed 
}

void Laser::update() {
	position += speed;
}
