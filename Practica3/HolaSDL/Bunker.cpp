#include "checkML.h"
#include "Bunker.h"
#include <algorithm>
#include "Game.h"

Bunker::Bunker(const Point2D<>& position, int lives, Texture* texture, PlayState* playState)
	: SceneObject(position, lives, texture, playState) { }

/// muestra su frame de textura segun las vidas que le queden, sin salirse 
void Bunker::render() const
{
	texture->renderFrame(rect, texture->getNumRows() - 1, std::clamp(texture->getNumColumns() - lives, 0, texture->getNumColumns() - 1));
}

/// avisa a game si ha de ser destruido cuando no le quedan vidas
void Bunker::update() {
	if (lives <= 0)
		//game->hasDied(iterator);
	updateRect();
}

/// metodo para guardar sus datos en el stream proporcionado
void Bunker::save(std::ostream& os) const 
{
	os << "4 ";
	SceneObject::save(os);
	os << lives << std::endl;
}