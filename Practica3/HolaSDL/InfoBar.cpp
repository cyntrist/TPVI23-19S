#include "checkML.h"
#include "Game.h"
#include "InfoBar.h"
#include "PlayState.h"

InfoBar::InfoBar(const Point2D<>& position, Texture* texture, int padding, GameState* gameState, SDL_Renderer* renderer)
	: GameObject(gameState), position(position), cannonTexture(texture), padding(padding), renderer(renderer)
{
}

//InfoBar::~InfoBar()
//{
//	~font();
//	GameObject::~GameObject();
//}

/// Renderiza las vidas en la esquina inferior izquierda y el score en la esquina inferior derecha con el padding acorde
void InfoBar::render() const
{
	/// BLOQUE DE VIDAS
	SDL_Rect livesRect{
		position.getX() + padding,
		position.getY() - padding,
		cannonTexture->getFrameWidth(),
		cannonTexture->getFrameHeight()
	};
	for (int i = 1; i < lives + 1; i++)
	{
		cannonTexture->renderFrame(livesRect, cannonTexture->getNumRows() - 1, cannonTexture->getNumColumns() - 1);
		livesRect.x = cannonTexture->getFrameWidth() * i + padding * (i + 1);
	}

	/// BLOQUE DE SCORE
	const Texture* scoreTexture = font->generateTexture(renderer, std::to_string(points), color);
	const SDL_Rect scoreRect{
		WIN_WIDTH - scoreTexture->getFrameWidth() - padding,
		WIN_HEIGHT - scoreTexture->getFrameHeight() - padding,
		scoreTexture->getFrameWidth(),
		scoreTexture->getFrameHeight()
	};
	scoreTexture->render(scoreRect);
}
