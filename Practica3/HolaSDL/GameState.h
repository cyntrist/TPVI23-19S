#pragma once
#include <iostream>
#include "gameList.h"
#include "GameObject.h"
#include "EventHandler.h"
#include <list>
#include <SDL_events.h>
class Game;
class GameObject;
class GameState
{
protected:
    Game* game = nullptr;
    GameList<GameObject, true> gameObjects;
    std::list<EventHandler*> eventHandlers;
    std::string stateID;
	bool exit = false;

public:
    GameState() = default;
    GameState(std::string);
    virtual ~GameState() = default;
    virtual void update() = 0;
    virtual void render() const = 0;
    virtual void handleEvent(const SDL_Event&) {}
    virtual void addEventListener() {}
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

