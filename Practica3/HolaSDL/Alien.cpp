#include "checkML.h"
#include "Alien.h"
#include "Game.h"
#include "Mothership.h"

Alien::Alien(const Point2D<>& position, int type, Texture* texture, GameState* gameState, Mothership* mothership)
	: SceneObject(position, 1, texture, gameState), type(type), mothership(mothership)
{
	descent = position.getY();
}

void Alien::render() const
{
	texture->renderFrame(rect, type, state);
}

/// primero comprueba si ha aterrizado a traves de la madre nodriza
///	luego se mueve si la madre nodriza lo asegura
///	comprueba y avisa a la madre nodriza de que ha llegado a un extremo
///	y finalmente actualiza su posicion de descenso segun el nivel que diga la madre nodriza
void Alien::update()
{
	mothership->alienLanded(this);

	if (mothership->shouldMove()) 
	{
		position = position + Vector2D<>(mothership->getDirection() * ALIEN_MOV_SPEED * speed, 0); //movimiento de los aliens
		state = (state + 1) % 2; // animacion
		updateRect();
	}

	if (position.getX() <= 0 || position.getX() >= WIN_WIDTH - texture->getFrameWidth())
		mothership->cannotMove();
	speed = mothership->getLevel()/5 + 1;
	position = Point2D<>(position.getX(), descent + ALIEN_MOV_SPEED * mothership->getLevel()); // descenso
}

/// anyade la puntuacion al jugador acorde a su tipo y devuelve verdadero si hay interseccion con otro rectangulo
bool Alien::hit(const SDL_Rect* otherRect, char friendly){
	if (SDL_HasIntersection(getRect(), otherRect) && friendly == 'r')
	{
		const int score = 30 - type * 10;
		//gameState->addScore(score);
		mothership->alienDied();
		gameState->hasDied(anchor);
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