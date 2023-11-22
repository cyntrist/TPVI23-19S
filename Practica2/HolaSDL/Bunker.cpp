#include "checkML.h"
#include "Bunker.h"

Bunker::Bunker(const Point2D<double>& p, int l, Texture* t)
{
	position = p;
	lives = l;
	texture = t; 
}

void Bunker::render() const
{
	SceneObject::render(texture->getNumRows() - 1, texture->getNumColumns() - lives - 1);
}
