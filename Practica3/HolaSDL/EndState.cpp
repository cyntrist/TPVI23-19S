#include "checkML.h"
#include "EndState.h"
#include "Game.h"
#include "MainMenuState.h"

EndState::EndState(Game* _game) : GameState(_game, "END")
{
	Texture* gameOver = game->getTexture(game_over);
	SDL_Rect rect = {
		WIN_WIDTH / 2,
		WIN_HEIGHT / 2,
		gameOver->getFrameWidth(),
		gameOver->getFrameHeight()
	};
	gameOver->render(rect);

	// GUARDAR
	auto* saveGameBtn = new Button(Vector2D<>((WIN_WIDTH - game->getTexture(btn_volver)->getFrameWidth()) / 2, WIN_HEIGHT / 2), game->getTexture(btn_volver));
	addGameObject(saveGameBtn);
	addEventListener(saveGameBtn);
	saveGameBtn->Connect([this](const SDL_Event& arg)
		{
			game->getStateMachine()->pushState(new MainMenuState(game));
		});

	// SALIR
	auto* exitBtn = new Button(Vector2D<>((WIN_WIDTH - game->getTexture(btn_salir)->getFrameWidth()) / 2, WIN_HEIGHT * 3 / 4), game->getTexture(btn_salir));
	addGameObject(exitBtn);
	addEventListener(exitBtn);
	exitBtn->Connect([this](const SDL_Event& arg)
		{
			game->exitGame();
		});
}

void EndState::render() const
{
	game->getTexture(stars)->render();
	GameState::render();
}
