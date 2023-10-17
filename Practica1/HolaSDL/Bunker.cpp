#include "Bunker.h"
#include <SDL.h>

using namespace std;

Bunker::Bunker(const uint v) {
	vidas = v;
}

bool Bunker::update()
{
	if (vidas <= 0) return false;
	return true;
}

void Bunker::render() const
{
	// ...
}

void Bunker::hit()
{
	vidas--;
}
