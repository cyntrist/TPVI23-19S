#include "SceneObject.h"

SceneObject::SceneObject() : GameObject(nullptr)
{
	this->position = Point2D<double>(0, 0);
	this->lives = 0;
	this->texture = nullptr;
	width = 0;
	height = 0;
	rect.x = 0;
	rect.y = 0;
	rect.w = 0;
	rect.h = 0;
}

void SceneObject::updateRect() // actualizar la posicion del rectángulo
{
	rect.x = position.getX();
	rect.y = position.getY();
	rect.w = texture->getFrameWidth();
	rect.h = texture->getFrameHeight();
}

SceneObject::SceneObject(Point2D<double> position, int lives, Texture* texture, Game* g)
: GameObject(g), position(position), lives(lives), texture(texture)
{
	width = texture->getFrameWidth();
	height = texture->getFrameHeight();
}

void SceneObject::render() const  // renderizar sprite
{
	texture->render(rect);
}

void SceneObject::render(int row, int col) const // renderizar frame
{
	texture->renderFrame(rect, row, col);
}

bool SceneObject::update() 
{
	updateRect(); // actualiza el rectángulo en base a la posición actual
	return !hasDied();
}

void SceneObject::hit(SDL_Rect*& otherRect, char friendly)
{
	if (SDL_HasIntersection(&rect, otherRect)) // faltaría comprobar si es friendly, pero es que depende del objeto?? nose
		lives--; 
}

bool SceneObject::hasDied()
{
	if (lives < 0)
		return true;
	return false;
}
