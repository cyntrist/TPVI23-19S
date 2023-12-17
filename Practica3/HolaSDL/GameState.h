#pragma once
#include <iostream>
#include "gameList.h"
#include "EventHandler.h"
#include <list>
#include <SDL_events.h>
class Game;
#include "GameObject.h"
class GameState
{
protected:
    Game* game;
    GameList<GameObject, true> gameObjects;
    std::list<EventHandler*> eventHandlers;
    std::string stateID;
	//bool exit = false;

public:
    GameState() = default;
    GameState(Game* game, const std::string& stateID) : game(game), stateID(stateID) {}
    virtual ~GameState() = default;
    virtual void update()
    {
    	for (auto& i : gameObjects) // los objetos
			i.update();
    }
    virtual void render() const
    {
    	for (const auto& i : gameObjects) // los objetos
			i.render();
    }
    virtual void handleEvent(const SDL_Event& event)
    {
	    for (EventHandler* i : eventHandlers)
			i->handleEvent(event);
    }
    virtual void addEventListener(EventHandler* eventHandler)
    {
        eventHandlers.push_back(eventHandler);
    }
    virtual void save(std::ostream&) const {}
    virtual void hasDied(const GameList<GameObject, true>::anchor& anchor)
    {
	    gameObjects.erase(anchor);
    }
	virtual void addGameObject(GameObject* object)
	{
		gameObjects.push_back(object);
	}
    virtual bool onEnter()
    {
    	std::cout << "Entering " << stateID << std::endl; return true;
    } 
	virtual bool onExit()
    {
	    std::cout << "Exiting " << stateID << std::endl; return true;
    }
    virtual std::string getStateID() const { return stateID; }
    Game* getGame() const { return game; }
};

