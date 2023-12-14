#pragma once
#include "PlayState.h"
#include "SDL.h"
#include "texture.h"
#include "GameStateMachine.h"
class Mothership;

class Game {
private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	std::array<Texture*, NUM_TEXTURES> textures;
	GameStateMachine* stateMachine;

public:
	Game();
	~Game();
	SDL_Renderer* getRenderer() const { return renderer; }
	Texture* getTexture(TextureName name) const
	{
		return textures[name];
	}
	SDL_Renderer* getRenderer() { return renderer; }
};

