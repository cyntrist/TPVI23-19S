#include "checkML.h"
#include "PauseState.h"
#include "Game.h"
#include "MainMenuState.h"
#include "PlayState.h"

PauseState::PauseState(Game* _game) : GameState(_game, "PAUSE")
{
	// CONTINUAR
	auto* continueGameBtn = new Button(
		Vector2D<>((WIN_WIDTH - game->getTexture(btn_continuar)->getFrameWidth()) / 2, 100), "CONTINUAR",
		game->getRenderer());
	addGameObject(continueGameBtn);
	addEventListener(continueGameBtn);
	continueGameBtn->connect([this]()
	{
		game->getStateMachine()->popState();
	});

	// CARGAR
	auto* loadGameBtn = new Button(Vector2D<>((WIN_WIDTH - game->getTexture(btn_cargar)->getFrameWidth()) / 2, 200),
	                               "CARGAR PARTIDA", game->getRenderer());
	addGameObject(loadGameBtn);
	addEventListener(loadGameBtn);
	loadGameBtn->connect([this]()
	{
		auto* play = new PlayState(game, 1, 1); //sustituir todo esto por lo que sea que haga el boton
		game->getStateMachine()->replaceState(play);
	});

	// GUARDAR
	auto* saveGameBtn = new Button(Vector2D<>((WIN_WIDTH - game->getTexture(btn_guardar)->getFrameWidth()) / 2, 300),
	                               "GUARDAR PARTIDA", game->getRenderer());
	addGameObject(saveGameBtn);
	addEventListener(saveGameBtn);
	saveGameBtn->connect([this]()
	{
		game->getStateMachine()->saveGame();
		game->exitGame();
	});

	// SALIR
	auto* exitBtn = new Button(Vector2D<>((WIN_WIDTH - game->getTexture(btn_salir)->getFrameWidth()) / 2, 400), "SALIR",
	                           game->getRenderer());
	addGameObject(exitBtn);
	addEventListener(exitBtn);
	exitBtn->connect([this]()
	{
		auto* mainMenu = new MainMenuState(game);
		game->getStateMachine()->replaceState(mainMenu);
	});

	buttons.push_back(loadGameBtn);
	buttons.push_back(saveGameBtn);
	buttons.push_back(exitBtn);
}

void PauseState::render() const
{
	game->getTexture(stars)->render();
	GameState::render();
}
