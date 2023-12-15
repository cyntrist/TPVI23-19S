#include "PauseState.h"
#include "Game.h"

PauseState::PauseState(Game* _game) : GameState(_game, "PAUSE")
{
	Button* continueGameBtn = new Button(Vector2D<>((WIN_WIDTH - game->getTexture(btn_continuar)->getFrameWidth()) / 2, 100), game->getTexture(btn_continuar));
	Button* loadGameBtn = new Button(Vector2D<>((WIN_WIDTH - game->getTexture(btn_cargar)->getFrameWidth()) / 2, 200), game->getTexture(btn_cargar));
	Button* saveGameBtn = new Button(Vector2D<>((WIN_WIDTH - game->getTexture(btn_guardar)->getFrameWidth()) / 2, 300), game->getTexture(btn_guardar));
	Button* exitBtn = new Button(Vector2D<>((WIN_WIDTH - game->getTexture(btn_salir)->getFrameWidth()) / 2, 400), game->getTexture(btn_salir));
	addGameObject(continueGameBtn);
	addGameObject(loadGameBtn);
	addGameObject(saveGameBtn);
	addGameObject(exitBtn);
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

