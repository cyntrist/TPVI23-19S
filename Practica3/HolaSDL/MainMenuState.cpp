#include "MainMenuState.h"

#include "Game.h"
#include "PlayState.h"

MainMenuState::MainMenuState(Game* _game) : GameState(_game, "MENU")
{
	menuTexture = game->getTexture(menu);
	Button* newGameBtn = new Button(Vector2D<>((WIN_WIDTH - game->getTexture(btn_nueva)->getFrameWidth()) / 2, 130), game->getTexture(btn_nueva));
	Button* continueGameBtn = new Button(Vector2D<>((WIN_WIDTH - game->getTexture(btn_continuar)->getFrameWidth()) / 2, 190), game->getTexture(btn_continuar));
	Button* exitBtn = new Button(Vector2D<>((WIN_WIDTH - game->getTexture(btn_salir)->getFrameWidth()) / 2, 250), game->getTexture(btn_salir));
	addGameObject(newGameBtn);
	addGameObject(continueGameBtn);
	addGameObject(exitBtn);
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
