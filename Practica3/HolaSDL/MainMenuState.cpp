#include "MainMenuState.h"

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
			PlayState* play = new PlayState(game); //sustituir todo esto por lo que sea que haga el boton
			game->getStateMachine()->pushState(play);
		});
	auto* continueGameBtn = new Button(Vector2D<>((WIN_WIDTH - game->getTexture(btn_continuar)->getFrameWidth()) / 2, 190), game->getTexture(btn_continuar));
	addGameObject(continueGameBtn);
	addEventListener(continueGameBtn);
	continueGameBtn->Connect([this](const SDL_Event& arg)
		{
			PauseState* pause = new PauseState(game); //sustituir todo esto por lo que sea que haga el boton
			game->getStateMachine()->pushState(pause);
		});
	auto* exitBtn = new Button(Vector2D<>((WIN_WIDTH - game->getTexture(btn_salir)->getFrameWidth()) / 2, 250), game->getTexture(btn_salir));
	addGameObject(exitBtn);
	addEventListener(exitBtn);
	exitBtn->Connect([this](const SDL_Event& arg)
		{
			game->exitGame();
		});
}
void MainMenuState::update()
{
	for (GameObject& i : gameObjects) //no se si el tipo de esto esta bien, pero funciona
		i.update();
}

void MainMenuState::render() const
{
	//std::cout << "COJONES";
	menuTexture->render();
	for (GameObject& i : gameObjects) //no se si el tipo de esto esta bien, pero funciona
		i.render();
}

void MainMenuState::handleEvent(const SDL_Event& event)
{
	for (EventHandler* i : eventHandlers)
		i->handleEvent(event);
}

