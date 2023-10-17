#include "Bunker.h"
#include <SDL.h>

using namespace std;

Bunker::Bunker(const uint v, Texture* t) {
	lives = v;
	texture = t; 
}

bool Bunker::update()
{
	if (lives <= 0) return false;
	return true;
}

void Bunker::render() const
{
	// ...
}

void Bunker::hit()
{
	lives--;
}
