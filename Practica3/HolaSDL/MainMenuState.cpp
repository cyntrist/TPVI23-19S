#include "MainMenuState.h"

MainMenuState::MainMenuState(Texture* texture) : GameState("MENU"), texture(texture)
{

}

void MainMenuState::update()
{

}

void MainMenuState::render() const
{
	//std::cout << "COJONES";
	texture->render();
}
