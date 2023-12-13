#pragma once
#include "gameList.h"
#include "GameObject.h"
#include "EventHandler.h"
#include <list>
#include <SDL_events.h>

class GameState
{
protected:
    Game* game = nullptr;
    GameList<GameObject, true> gameObjects;
    std::list<EventHandler*> eventHandlers;
public:
    virtual void update() = 0;
    virtual void render() const = 0;
    virtual void handleEvent(const SDL_Event&) = 0;
    virtual void addEventListener();
    virtual void addObject();
    virtual void save(std::ostream&) const = 0;
    virtual void hasDied(GameList<GameObject, true>::anchor) = 0;
    virtual bool onEnter() = 0;
	virtual bool onExit() = 0;
	virtual std::string getStateID() const = 0;
    Game* getGame() const { return game; }
};
