#include "checkML.h"
#include "Alien.h"
#include "Game.h"
#include "Mothership.h"

Alien::Alien(const Point2D<>& position, int type, Texture* texture, Game* game, Mothership* mothership)
	: SceneObject(position, 1, texture, game), type(type), mothership(mothership)
{
	this->position = Point2D<>(position.getX(), position.getY() + texture->getFrameHeight() * mothership->getLevel());
}

void Alien::render() const
{
	texture->renderFrame(rect, type, state);
}

void Alien::update()
{ 
	if (mothership->shouldMove()) 
	{
		position = position + Vector2D<>(mothership->getDirection() * ALIEN_MOV_SPEED, 0); //movimiento de los aliens
		state = (state + 1) % 2; // animacion
		updateRect();
	}
	if (position.getX() <= 0 || position.getX() >= WIN_WIDTH - texture->getFrameWidth())
		mothership->cannotMove();
}

void Alien::down()
{
	position = position + Vector2D(0, ALIEN_MOV_SPEED);
}

/// añade la puntuacion al jugador acorde a su tipo y devuelve verdadero si hay interseccion con otro rectangulo
bool Alien::hit(SDL_Rect* otherRect, char friendly){
	if (SDL_HasIntersection(getRect(), otherRect) && friendly == 'r')
	{
		const int score = 30 - type * 10;
		game->addScore(score);
		mothership->alienDied();
		game->hasDied(iterator);
		return true;
	}
	return false;
}

/// metodo para guardar sus datos en el stream proporcionado
void Alien::save(std::ostream& os) const 
{
	os << "1 ";
	SceneObject::save(os);
	os << type << std::endl;
}