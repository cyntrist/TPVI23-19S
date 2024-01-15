#pragma once
#include <iostream>
#include "GameList.h"
#include "EventHandler.h"
#include <list>
#include <SDL_events.h>
#include "Button.h"
class Game;
#include "GameObject.h"
class GameState
{
protected:
    Game* game;
    GameList<GameObject, true> gameObjects;
    std::list<EventHandler*> eventHandlers;
    std::list<Button*> buttons;
    std::string stateID;

public:
    GameState() = default;
    GameState(Game* game, const std::string& stateID) : game(game), stateID(stateID) {}
    virtual ~GameState() = default;
    virtual void update();
    virtual void render() const;
    virtual void handleEvent(const SDL_Event& event);
    virtual void addEventListener(EventHandler* eventHandler);
    virtual void save(const std::string& fileName) const {}
    virtual void hasDied(const GameList<GameObject, true>::anchor& anchor);
	virtual void addGameObject(GameObject* object);
    virtual bool onEnter();
	virtual bool onExit();
    std::string getStateID() const { return stateID; }
    Game* getGame() const { return game; }
};

