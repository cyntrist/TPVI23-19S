#include "checkML.h"
#include "Mothership.h"
#include "PlayState.h"

Mothership::Mothership(int direction, int alienCount, int state, int level, GameState* gameState, int movementTimer)
: GameObject(gameState), direction(direction), alienCount(alienCount), level(level), movementTimer(movementTimer) { }

/// metodo para comprobar si es momento de moverse
bool Mothership::shouldMove() const {
	return movementTimer == ALIEN_REFRESH_RATE;
}

/// metodo para avisar a la madre nodriza de que se ha llegado al limite y ha de cambiar la direccion de movimiento
void Mothership::cannotMove() {
	if (!switchDir)
	{
		std::cout << "CANNOT MOVE" << std::endl;
		switchDir = true;
		level++;
	}
}

/// actualiza el temporizador y cambia la direccion si hace falta
void Mothership::update()
{
	if (movementTimer < ALIEN_REFRESH_RATE)
		movementTimer++;
	else
		movementTimer = 0;

	if (shouldMove() && switchDir)
	{
		direction = -direction;
		switchDir = false;
	}
}

/// metodo para comprobar si el alien en concreto ha aterrizado
void Mothership::alienLanded(Alien* alien) const
{
	if (alien->getPosition().getY() >= WIN_HEIGHT*3/4)
		haveLanded();
}

/// metodo para avisar al juego de que los aliens han ganado
void Mothership::haveLanded() const 
{ 
	//gameState->endGame();
}

/// metodo para guardar sus datos en el stream proporcionado
void Mothership::save(std::ostream& os) const 
{
	os << "3 0 0 " << level << " " << movementTimer << std::endl;
}
