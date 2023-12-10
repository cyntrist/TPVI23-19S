#pragma once
#include "gameList.h"
#include "GameObject.h"
#include "EventHandler.h"
#include <list>
#include <SDL_events.h>

class GameState
{
protected:
    Game* game;
    GameList<GameObject, true> gameObjects;
    std::list<EventHandler*> eventHandlers;
public:
    void update();
    void render(); const
    void handleEvent(const SDL_Event&);
    void addEventListener();
    void addObject();
    void save(std::ostream&) const;
    void hasDied(GameList<GameObject, true>::anchor);
    Game* getGame() const { return game; }
};

