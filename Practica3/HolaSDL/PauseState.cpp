#include "PauseState.h"
#include "Game.h"
#include "MainMenuState.h"
#include "PlayState.h"

PauseState::PauseState(Game* _game) : GameState(_game, "PAUSE")
{
	Button* continueGameBtn = new Button(Vector2D<>((WIN_WIDTH - game->getTexture(btn_continuar)->getFrameWidth()) / 2, 100), game->getTexture(btn_continuar));
	addGameObject(continueGameBtn);
	addEventListener(continueGameBtn);
	continueGameBtn->Connect([this](const SDL_Event& arg)
		{
			PauseState* pause = new PauseState(game); //sustituir todo esto por lo que sea que haga el boton
			game->getStateMachine()->pushState(pause);
		});
	Button* loadGameBtn = new Button(Vector2D<>((WIN_WIDTH - game->getTexture(btn_cargar)->getFrameWidth()) / 2, 200), game->getTexture(btn_cargar));
	addGameObject(loadGameBtn);
	addEventListener(loadGameBtn);
	loadGameBtn->Connect([this](const SDL_Event& arg)
		{
			PauseState* pause = new PauseState(game); //sustituir todo esto por lo que sea que haga el boton
			game->getStateMachine()->pushState(pause);
		});
	Button* saveGameBtn = new Button(Vector2D<>((WIN_WIDTH - game->getTexture(btn_guardar)->getFrameWidth()) / 2, 300), game->getTexture(btn_guardar));
	addGameObject(saveGameBtn);
	addEventListener(saveGameBtn);
	saveGameBtn->Connect([this](const SDL_Event& arg)
		{
			PauseState* pause = new PauseState(game); //sustituir todo esto por lo que sea que haga el boton
			game->getStateMachine()->pushState(pause);
		});
	Button* exitBtn = new Button(Vector2D<>((WIN_WIDTH - game->getTexture(btn_salir)->getFrameWidth()) / 2, 400), game->getTexture(btn_salir));
	addGameObject(exitBtn);
	addEventListener(exitBtn);
	exitBtn->Connect([this](const SDL_Event& arg)
		{
			MainMenuState* mainMenu = new MainMenuState(game);
			game->getStateMachine()->pushState(mainMenu);
		});
}

void PauseState::render() const
{
	for (GameObject& i : gameObjects) //no se si el tipo de esto esta bien, pero funciona
		i.render();
}

void PauseState::update()
{
	for (GameObject& i : gameObjects) //no se si el tipo de esto esta bien, pero funciona
		i.update();
}

void PauseState::handleEvent(const SDL_Event& event)
{
	for (EventHandler* i : eventHandlers)
		i->handleEvent(event);
}
