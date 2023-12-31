#include "checkML.h"
#include "GameState.h"
#include "GameObject.h"

void GameState::update()
    {
    	for (auto& i : gameObjects) // los objetos
			i.update();
    }

void GameState::render() const
    {
    	for (const auto& i : gameObjects) // los objetos
			i.render();
    }

void GameState::handleEvent(const SDL_Event& event)
    {
	    for (EventHandler* i : eventHandlers)
			i->handleEvent(event);
    }

void GameState::addEventListener(EventHandler* eventHandler)
    {
        eventHandlers.push_back(eventHandler);
    }

void GameState::hasDied(const GameList<GameObject, true>::anchor& anchor)
    {
	    gameObjects.erase(anchor);
    }

void GameState::addGameObject(GameObject* object)
	{
		gameObjects.push_back(object);
	}

bool GameState::onEnter()
    {
    	std::cout << "Entering " << stateID << std::endl; return true;
    }

bool GameState::onExit()
    {
	    std::cout << "Exiting " << stateID << std::endl; return true;
    }
