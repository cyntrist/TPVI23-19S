#include "MainMenuState.h"

MainMenuState::MainMenuState(Texture* menuTexture, Texture* buttonTexture) : GameState("MENU"), texture(menuTexture)
{
	
}
void MainMenuState::update()
{

}

void MainMenuState::render() const
{
	//std::cout << "COJONES";
	texture->render();
	button1->render();
}
