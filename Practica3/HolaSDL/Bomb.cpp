#include "checkML.h"
#include "Bomb.h"
#include "PlayState.h"

char constexpr FRIENDLY_CHAR = 'b';

Bomb::Bomb(Point2D<> _position, Texture* _texture, PlayState* _playState)
: SceneObject(_position, 2, _texture, _playState)
{
}

void Bomb::update()
{
	updateRect();
	position = Vector2D<>(position.getX(), position.getY() + BOMB_MOV_SPEED);
	if (playState->damage(getRect(), FRIENDLY_CHAR) || lives <= 0 || position.getY()  < 0 || position.getY() > WIN_HEIGHT)
 		hasDied();
}

bool Bomb::hit(const SDL_Rect* otherRect, char friendly)
{
	if (friendly != FRIENDLY_CHAR && SDL_HasIntersection(getRect(), otherRect))
	{
		lives--;
		return true;
	}
	return false;
}

void Bomb::save(std::ostream& os) const
{
	os << "8 ";
	SceneObject::save(os);
}
