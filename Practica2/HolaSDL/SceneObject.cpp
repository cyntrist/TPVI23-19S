#include "SceneObject.h"

void SceneObject::positionRect()
{
	rect.x = position.getX();
	rect.y = position.getY();
	rect.w = texture->getFrameWidth();
	rect.h = texture->getFrameHeight();
}

SceneObject::SceneObject()
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
	game  = nullptr;
}

SceneObject::SceneObject(Point2D<double> position, int lives, Texture* texture, Game* g)
{
	this->position = position;
	this->lives = lives;
	this->texture = texture;
	width = texture->getFrameWidth();
	height = texture->getFrameHeight();
	positionRect();
	game  = g;
}

void SceneObject::render()
{
	positionRect();
	texture->render(rect);
}

void SceneObject::render(int row, int col)
{
	positionRect();
	texture->renderFrame(rect, row, col);
}

void SceneObject::hit(SDL_Rect*& otherRect, char friendly)
{
	if (SDL_HasIntersection(&rect, otherRect)) // faltaría comprobar si es friendly, pero es que depende del objeto?? nose
		lives--; 
}