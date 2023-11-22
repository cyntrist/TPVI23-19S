#include "Mothership.h"

Mothership::Mothership(Vector2D<> direction, int alienCount, int state, int level, Game* game)
: GameObject(game), direction(direction), alienCount(alienCount), state(state), level(level) { }
