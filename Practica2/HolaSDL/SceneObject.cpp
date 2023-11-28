#include "SceneObject.h"
#include "Game.h"

SceneObject::SceneObject() : GameObject(nullptr)
{
	position = Point2D<>(0, 0);
	lives = 0;
	texture = nullptr;
	width = 0;
	height = 0;
	rect.x = 0;
	rect.y = 0;
	rect.w = 0;
	rect.h = 0;
}

SceneObject::SceneObject(Point2D<> position, int lives, Texture* texture, Game* g)
: GameObject(g), position(position), lives(lives), texture(texture)
{
	width = texture->getFrameWidth();
	height = texture->getFrameHeight();
}

void SceneObject::render() const  // renderizar sprite
{
	texture->render(rect);
}

void SceneObject::updateRect() // actualizar la posicion del rectangulo
{
	rect.x = position.getX();
	rect.y = position.getY();
	rect.w = texture->getFrameWidth();
	rect.h = texture->getFrameHeight();
}

void SceneObject::update() 
{
	updateRect(); // actualiza el rectangulo en base a la posicion actual
}

bool SceneObject::hit(SDL_Rect* otherRect, char friendly)
{
	if (SDL_HasIntersection(getRect(), otherRect))
	{
		lives--;
		return true;
	}
	return false;
}

void SceneObject::save(std::ostream& os) const
{
	os << position.getX() << " " << position.getY() << " " << std::endl;
}
