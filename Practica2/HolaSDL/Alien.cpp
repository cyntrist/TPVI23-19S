#include "checkML.h"
#include "Alien.h"
#include "Game.h"

Alien::Alien(const Point2D<double>& position, int type, Texture* texture, Game* game)
	: SceneObject(position, 1, texture, game), type(type) { }

Alien::Alien(const Point2D<double>& position, int type, Texture* texture, Game* game, Mothership* mothership)
: SceneObject(position, 1, texture, game), type(type), mothership(mothership) { }

void Alien::render() const
{
	texture->renderFrame(rect, type, state);
}

bool Alien::update()
{ //ni idea de si esto es mejor separarlo en varios metodos y dejar el update como solo llamadas a esos metodos
	if (destroy)  
	{
		const uint score = type * 10;
		Game::addScore(score);
		std::cout << "PLAYER SCORE: " << Game::getScore() << std::endl; // imagino que esto habría que devolverlo al main
		return false; // hit
	}
	/*
	if (mothership->cannotMove()) // he puesto esto por ejemplo, pero ni idea poruqe está sin hacer XD
	{
		position = position + Vector2D<>(game->getDirection() * ALIEN_MOV_SPEED, 0); //movimiento de los aliens
		state = (state + 1) % 2; // animacion
	} */
	return true;
}

void Alien::down()
{
	position = position + Vector2D<>(0, ALIEN_MOV_SPEED);
}

bool Alien::hit(SDL_Rect* otherRect, char friendly){
	if (SDL_HasIntersection(getRect(), otherRect) && friendly == 'r')
		destroy = true;
	return destroy;
}