#include "Mothership.h"
#include "Alien.h"
#include "Game.h"

Mothership::Mothership(int direction, int alienCount, int state, int level, Game* game, int movementTimer)
: GameObject(game), direction(direction), alienCount(alienCount), state(state), level(level), movementTimer(movementTimer) { }

bool Mothership::shouldMove() {
	return movementTimer == ALIEN_REFRESH_RATE;
}

void Mothership::cannotMove() {
	switchDir = true;
	/* copiado tal cual de game
	bool cantMove = false;
	int i = 0;
	while (i < aliens.size() && !cantMove) {
		if (aliens[i]->getPos().getX() <= 0 || aliens[i]->getPos().getX() >= WIN_WIDTH - textures[alien]->getFrameWidth())
		{
			cantMove = true;
			for (const auto i : aliens) i->down();
		}
		else
			i++;
	}
	if (cantMove)
		direction = -direction;
	return cantMove;
	*/
}

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

bool Mothership::alienLanded(const Alien*& alien) // se me ocurre, no se
{
	if (alien->getPosition().getY() >= WIN_HEIGHT*3/4)
		return true;
	return false;
}

bool Mothership::haveLanded()
{ // idkkkk
	game->endGame();
	return true;
}

/*
/// metodo para guardar sus datos en el stream proporcionado
void Mothership::save(std::ostream& os) const 
{
	os << "3 0 0 " << state << " " << level << " " << movementTimer << std::endl;
}
*/