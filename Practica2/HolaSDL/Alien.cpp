#include "checkML.h"
#include "Alien.h"
#include "Game.h"

Alien::Alien(const Point2D<>& position, int type, Texture* texture, Game* game)
	: SceneObject(position, 1, texture, game), type(type) { }

Alien::Alien(const Point2D<>& position, int type, Texture* texture, Game* game, Mothership* mothership)
	: SceneObject(position, 1, texture, game), type(type), mothership(mothership) { }

void Alien::render() const
{
	texture->renderFrame(rect, type, state);
}

void Alien::update()
{ //ni idea de si esto es mejor separarlo en varios metodos y dejar el update como solo llamadas a esos metodos
	/*
	if (mothership->cannotMove()) // he puesto esto por ejemplo, pero ni idea poruqe esta sin hacer XD
	{
		position = position + Vector2D<>(game->getDirection() * ALIEN_MOV_SPEED, 0); //movimiento de los aliens
		state = (state + 1) % 2; // animacion
	}
	*/
}

void Alien::down()
{
	position = position + Vector2D<int>(0, ALIEN_MOV_SPEED);
}

/// añade la puntuacion al jugador acorde a su tipo y devuelve verdadero si hay interseccion con otro rectangulo
bool Alien::hit(SDL_Rect* otherRect, char friendly){
	if (SDL_HasIntersection(getRect(), otherRect) && friendly == 'r')
	{
		const int score = 30 - type * 10;
		Game::addScore(score);
		game->hasDied(iterator);
		return true;
	}
	return false;
}

/// metodo para guardar sus datos en el stream proporcionado
void Alien::save(std::ostream& os) const 
{
	os << "1 " << position.getX() << " " << position.getY() << " " << type << std::endl;
}