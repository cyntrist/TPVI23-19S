#pragma once
#include <stack>

#include "GameState.h"
class GameStateMachine
{
protected:
    std::stack<GameState*> stateStack;
public:
    void pushState(GameState*) const;
    void replaceState(GameState*);
    void popState();
    void update();
    void render(); const
    void handleEvent(const SDL_Event&);
};