#include "MainMenuState.h"
#include "GameState.h"
#include "Game.h"
#include "PauseState.h"
#include "PlayState.h"

MainMenuState::MainMenuState(Game* _game) : GameState(_game, "MENU")
{
	menuTexture = game->getTexture(menu);

	auto* newGameBtn = new Button(Vector2D<>((WIN_WIDTH - game->getTexture(btn_nueva)->getFrameWidth()) / 2, 130), game->getTexture(btn_nueva));
	addGameObject(newGameBtn);
	addEventListener(newGameBtn);
	newGameBtn->Connect([this](const SDL_Event& arg)
		{
			auto* play = new PlayState(game); //sustituir todo esto por lo que sea que haga el boton
			game->getStateMachine()->replaceState(play);
		});
	auto* continueGameBtn = new Button(Vector2D<>((WIN_WIDTH - game->getTexture(btn_continuar)->getFrameWidth()) / 2, 190), game->getTexture(btn_continuar));
	addGameObject(continueGameBtn);
	addEventListener(continueGameBtn);
	continueGameBtn->Connect([this](const SDL_Event& arg)
		{
			//auto* pause = new PauseState(game); //sustituir todo esto por lo que sea que haga el boton
			//game->getStateMachine()->pushState(pause);
		});
	auto* exitBtn = new Button(Vector2D<>((WIN_WIDTH - game->getTexture(btn_salir)->getFrameWidth()) / 2, 250), game->getTexture(btn_salir));
	addGameObject(exitBtn);
	addEventListener(exitBtn);
	exitBtn->Connect([this](const SDL_Event& arg)
		{
			game->exitGame();
		});
}

void MainMenuState::render() const
{
	menuTexture->render();
	GameState::render();
}


