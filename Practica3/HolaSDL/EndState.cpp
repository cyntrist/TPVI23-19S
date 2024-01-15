#include "checkML.h"
#include "EndState.h"
#include "Game.h"
#include "MainMenuState.h"

EndState::EndState(Game* _game) : GameState(_game, "END")
{
	// VOLVER AL MENU
	auto* backButton = new Button(Vector2D(0,0), "VOLVER AL MENU", game->getRenderer());
	backButton->setPosition(Vector2D((WIN_WIDTH - backButton->getTexture()->getFrameWidth()) / 2, WIN_HEIGHT / 2));
	addGameObject(backButton);
	addEventListener(backButton);
	backButton->connect([this]()
		{
			game->getStateMachine()->pushState(new MainMenuState(game));
		});

	// NUEVA PARTIDA
	auto* newButton = new Button(Vector2D(0,0), "NUEVA PARTIDA", game->getRenderer());
	newButton->setPosition(Vector2D((WIN_WIDTH - newButton->getTexture()->getFrameWidth()) / 2, WIN_HEIGHT * 3 / 4));
	addGameObject(newButton);
	addEventListener(newButton);
	newButton->connect([this]()
		{
			game->exitGame();
		});

	buttons.push_back(backButton);
	buttons.push_back(newButton);
}

void EndState::render() const
{
	game->getTexture(stars)->render();
	Texture* gameOver = game->getTexture(game_over);
	SDL_Rect rect = {
		(WIN_WIDTH - gameOver->getFrameWidth()*2)/ 2,
		(WIN_HEIGHT - gameOver->getFrameHeight()*2) / 4,
		gameOver->getFrameWidth()*2,
		gameOver->getFrameHeight()*2
	};
	SDL_SetTextureColorMod(gameOver->getTexture(), 255, 0, 0);
	gameOver->render(rect);
	GameState::render();
}
