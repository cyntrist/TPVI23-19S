#include "SceneObject.h"
#include "Game.h"

/// constructora
SceneObject::SceneObject(Point2D<> position, int lives, Texture* texture, GameState* gameState)
: GameObject(gameState), position(position), lives(lives), texture(texture)
{
	width = texture->getFrameWidth();
	height = texture->getFrameHeight();
}

/// renderiza sprite entero
void SceneObject::render() const  
{
	texture->render(rect);
}

/// actualiza la posicion del rectangulo
void SceneObject::updateRect() 
{
	rect.x = position.getX();
	rect.y = position.getY();
	rect.w = texture->getFrameWidth();
	rect.h = texture->getFrameHeight();
}

/// actualiza el rectangulo en base a la posicion actual
void SceneObject::update() 
{
	updateRect();
	if (lives <= 0)
		gameState->hasDied(iterator);
}


/// devuelve bool si hay interseccion entre su rectangulo y el otro
bool SceneObject::hit(const SDL_Rect* otherRect, char friendly)
{
	if (SDL_HasIntersection(getRect(), otherRect))
	{
		lives--;
		return true;
	}
	return false;
}

/// guarda en el stream proporcionado sus datos basicos
void SceneObject::save(std::ostream& os) const
{
	os << position.getX() << " " << position.getY() << " ";
}
