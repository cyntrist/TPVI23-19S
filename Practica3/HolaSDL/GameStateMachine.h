#pragma once
#include <stack>

#include "GameState.h"
class GameStateMachine
{
protected:
    std::stack<GameState*> stateStack;
public:
    void pushState(GameState*); // en el enunciado pone que deberia ser const, pero como modificas la pila si no...?
    void popState();
	void replaceState(GameState*);
    void update();
    void render() const;
    void handleEvent(const SDL_Event&);
};