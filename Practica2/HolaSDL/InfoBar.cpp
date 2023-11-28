#include "checkML.h"
#include "InfoBar.h"
#include "Game.h"

InfoBar::InfoBar(const Point2D<>& position, Texture* texture, int padding, Game* game)
	: GameObject(game), position(position), texture(texture), padding(padding) { }

void InfoBar::render() const
{ // todo: infobar con score
	SDL_Rect r {
		position.getX() + padding,
		position.getY() - padding,
		texture->getFrameWidth(),
		texture->getFrameHeight()
	};
	/*for (int i = 1; i < Cannon::getLives() + 1; i++)
	{
		texture->renderFrame(r, texture->getNumRows() - 1, texture->getNumColumns() - 1);
		r.x = texture->getFrameWidth() * i + padding * (i + 1);
	}*/
}