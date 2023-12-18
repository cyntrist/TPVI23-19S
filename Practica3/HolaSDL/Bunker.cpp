#include "checkML.h"
#include "Bunker.h"
#include <algorithm>
#include "Game.h"
#include "PlayState.h"

Bunker::Bunker(const Point2D<>& position, int lives, Texture* texture, PlayState* playState)
	: SceneObject(position, lives, texture, playState) { }

/// muestra su frame de textura segun las vidas que le queden, sin salirse 
void Bunker::render() const
{
	texture->renderFrame(rect, texture->getNumRows() - 1, std::clamp(texture->getNumColumns() - lives, 0, texture->getNumColumns() - 1));
}

/// avisa a game si ha de ser destruido cuando no le quedan vidas
void Bunker::update() {
	SceneObject::update(); // no hace falta que tenga su propio metodo pero lo dejo por si lo necesitamos 
}

/// metodo para guardar sus datos en el stream proporcionado
void Bunker::save(std::ostream& os) const 
{
	os << "4 ";
	SceneObject::save(os);
	os << lives << std::endl;
}