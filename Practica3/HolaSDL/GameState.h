#pragma once
#include <iostream>
#include "gameList.h"
#include "GameObject.h"
#include "EventHandler.h"
#include <list>
#include <SDL_events.h>
class Game;
class GameObject; //??? por que esto ha arreglado 90 errores???? en la practica anterior no haciamos esto que yo recuerde
class GameState
{
protected:
    Game* game = nullptr;
    GameList<GameObject, true> gameObjects;
    std::list<EventHandler*> eventHandlers;
    std::string stateID;

public:
    GameState() = default;
    virtual ~GameState() = default;
    virtual void update() = 0;
    virtual void render() const = 0;
    virtual void handleEvent(const SDL_Event&);
    virtual void addEventListener();
    virtual void save(std::ostream&) const;
    virtual void hasDied(GameList<GameObject, true>::anchor);
	//virtual void addGameObject(GameObject*);
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

