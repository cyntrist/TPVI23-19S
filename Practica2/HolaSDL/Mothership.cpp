#include "Mothership.h"
#include "Alien.h"
#include "Game.h"

Mothership::Mothership(int direction, int alienCount, int state, int level, Game* game)
: GameObject(game), direction(direction), alienCount(alienCount), state(state), level(level) { }

bool Mothership::cannotMove() {

	/// VERSION ANTIGUA:
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
	return false;
}

bool Mothership::alienLanded(const Alien*& alien) // se me ocurre, no se
{
	if (alien->getPosition().getY() >= WIN_HEIGHT*3/4)
		return true;
	return false;
}

bool Mothership::haveLanded()
{
	return false;
}