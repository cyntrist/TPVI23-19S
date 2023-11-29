#include "checkML.h"
#include "Mothership.h"
#include "Alien.h"
#include "Game.h"

Mothership::Mothership(int direction, int alienCount, int state, int level, Game* game, int movementTimer)
: GameObject(game), direction(direction), alienCount(alienCount), state(state), level(level), movementTimer(movementTimer) { }

/// metodo para comprobar si es momento de moverse
bool Mothership::shouldMove() const {
	return movementTimer == ALIEN_REFRESH_RATE;
}


/// metodo para avisar a la madre nodriza de que se ha llegado al límite y ha de cambiar la direccion de movimiento
void Mothership::cannotMove() {
	switchDir = true;
}

///
void Mothership::update()
{
	if (movementTimer < ALIEN_REFRESH_RATE)
		movementTimer++;
	else
		movementTimer = 0;

	if (switchDir)
	{
		direction = -direction;
		switchDir = false;
	}
}

/// metodo para comprobar si el alien en concreto ha aterrizado
bool Mothership::alienLanded(const Alien*& alien) 
{
	if (alien->getPosition().getY() >= WIN_HEIGHT*3/4)
	{
		haveLanded();
		return true;
	}
	return false;
}

/// metodo para avisar al juego de que los aliens han ganado
bool Mothership::haveLanded()
{ 
	game->endGame();
	return true;
}


/// metodo para guardar sus datos en el stream proporcionado
void Mothership::save(std::ostream& os) const 
{
	os << "3 0 0 " << state << " " << level << " " << movementTimer << std::endl;
}
