#include "checkML.h"
#include "Game.h"
#include "InfoBar.h"

InfoBar::InfoBar(const Point2D<>& position, Texture* texture, int padding, GameState* gameState, SDL_Renderer* renderer)
	: GameObject(gameState), position(position), cannonTexture(texture), padding(padding), renderer(renderer) { }

/// Renderiza las vidas en la esquina inferior izquierda y el score en la esquina inferior derecha con el padding acorde
void InfoBar::render() const
{
	/// BLOQUE DE VIDAS
	SDL_Rect livesRect {
		position.getX() + padding,
		position.getY() - padding,
		cannonTexture->getFrameWidth(),
		cannonTexture->getFrameHeight()
	};
	/*for (int i = 1; i < gameState->getCannon()->getLives() + 1; i++)
	{
		cannonTexture->renderFrame(livesRect, cannonTexture->getNumRows() - 1, cannonTexture->getNumColumns() - 1);
		livesRect.x = cannonTexture->getFrameWidth() * i + padding * (i + 1);
	}*/

	/// BLOQUE DE SCORE
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, std::to_string(points).c_str(), color); // texto de score
	SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	const SDL_Rect scoreRect {
		WIN_WIDTH - textSurface->w - padding,
		WIN_HEIGHT - textSurface->h - padding,
		textSurface->w,
		textSurface->h
	};
	SDL_RenderCopy(renderer, scoreTexture, nullptr, &scoreRect);
	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(scoreTexture);
}

/// actualiza el score
void InfoBar::update()
{
	//points = gameState->getScore();
}
