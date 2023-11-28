#include "checkML.h"
#include "Game.h"
#include "InfoBar.h"

InfoBar::InfoBar(const Point2D<>& position, Texture* texture, int padding, Game* game, SDL_Renderer* renderer)
	: GameObject(game), position(position), cannonTexture(texture), padding(padding), renderer(renderer) { }

void InfoBar::render() const
{
	/// BLOQUE DE CANNONS
	SDL_Rect livesRect {
		position.getX() + padding,
		position.getY() - padding,
		cannonTexture->getFrameWidth(),
		cannonTexture->getFrameHeight()
	};
	for (int i = 1; i < game->getCannon()->getLives() + 1; i++)
	{
		cannonTexture->renderFrame(livesRect, cannonTexture->getNumRows() - 1, cannonTexture->getNumColumns() - 1);
		livesRect.x = cannonTexture->getFrameWidth() * i + padding * (i + 1);
	}

	/// BLOQUE DE SCORE
	if (font == NULL)
	{
		//std::cout << "FONT NOT FOUND! AT: " << FONT_ROOT << " from " << SDL_GetBasePath() << std::endl;
	}
	else
	{
		SDL_Surface* textSurface = TTF_RenderText_Solid(font, "HELLOOOO", color); // texto de score
		SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		SDL_Rect scoreRect {
			WIN_WIDTH/2,
			WIN_HEIGHT/2,
			textSurface->w,
			textSurface->h
		};
		SDL_RenderCopy(renderer, scoreTexture, nullptr, &scoreRect);
	}
}

void InfoBar::update()
{
	points = game->getScore();
}
