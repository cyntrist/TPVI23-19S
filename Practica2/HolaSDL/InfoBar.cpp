#include "checkML.h"
#include "InfoBar.h"

InfoBar::InfoBar(const Point2D<double>& position, Texture* texture, int padding, Game* game)
	: GameObject(game), position(position), texture(texture), padding(padding) { }

void InfoBar::render() const
{
	SDL_Rect r {
		static_cast<int>(position.getX()) + padding,
		static_cast<int>(position.getY()) - padding,
		texture->getFrameWidth(),
		texture->getFrameHeight()
	};
	for (int i = 1; i < Cannon::getLives() + 1; i++)
	{
		texture->renderFrame(r, texture->getNumRows() - 1, texture->getNumColumns() - 1);
		r.x = texture->getFrameWidth() * i + padding * (i + 1);
	}
}