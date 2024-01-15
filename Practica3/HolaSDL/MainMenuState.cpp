#include "checkML.h"
#include "MainMenuState.h"
#include "GameState.h"
#include "Game.h"
#include "PauseState.h"
#include "PlayState.h"

MainMenuState::MainMenuState(Game* _game) : GameState(_game, "MENU")
{
	menuTexture = game->getTexture(menu);

	auto* newGameBtn = new Button(Vector2D((WIN_WIDTH - game->getTexture(btn_nueva)->getFrameWidth()) / 2, 130), "NUEVA PARTIDA", game->getRenderer());
	addGameObject(newGameBtn);
	addEventListener(newGameBtn);
	newGameBtn->connect([this]
		{
			auto* play = new PlayState(game, 1, false);
			game->getStateMachine()->replaceState(play);
		});
	auto* continueGameBtn = new Button(Vector2D((WIN_WIDTH - game->getTexture(btn_continuar)->getFrameWidth()) / 2, 190), "CONTINUAR", game->getRenderer());
	addGameObject(continueGameBtn);
	addEventListener(continueGameBtn);
	continueGameBtn->connect([this]
		{
			auto* play = new PlayState(game, 1, true); 
			game->getStateMachine()->replaceState(play);
		});
	auto* exitBtn = new Button(Vector2D((WIN_WIDTH - game->getTexture(btn_salir)->getFrameWidth()) / 2, 250), "SALIR", game->getRenderer());
	addGameObject(exitBtn);
	addEventListener(exitBtn);
	exitBtn->connect([this]
		{
			game->exitGame();
		});

	buttons.push_back(newGameBtn);
	buttons.push_back(continueGameBtn);
	buttons.push_back(exitBtn);
}

void MainMenuState::render() const
{
	menuTexture->render();
	GameState::render();
}


