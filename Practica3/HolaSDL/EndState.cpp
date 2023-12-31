#include "checkML.h"
#include "EndState.h"
#include "Game.h"
#include "MainMenuState.h"

EndState::EndState(Game* _game) : GameState(_game, "END")
{
	// VOLVER AL MENU
	auto* saveGameBtn = new Button(Vector2D<>((WIN_WIDTH - game->getTexture(btn_volver)->getFrameWidth()) / 2, WIN_HEIGHT / 2), game->getTexture(btn_volver));
	addGameObject(saveGameBtn);
	addEventListener(saveGameBtn);
	saveGameBtn->Connect([this]()
		{
			game->getStateMachine()->pushState(new MainMenuState(game));
		});

	// SALIR
	auto* exitBtn = new Button(Vector2D<>((WIN_WIDTH - game->getTexture(btn_salir)->getFrameWidth()) / 2, WIN_HEIGHT * 3 / 4), game->getTexture(btn_salir));
	addGameObject(exitBtn);
	addEventListener(exitBtn);
	exitBtn->Connect([this]()
		{
			game->exitGame();
		});
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
