#include "GameStateMachine.h"

void GameStateMachine::pushState(GameState* state) 
{
	stateStack.push(state);
	stateStack.top()->onEnter();
}

void GameStateMachine::popState()
{
	if(!stateStack.empty())
	{
		if(stateStack.top()->onExit())
		{
			delete stateStack.top();
			stateStack.pop();
		}
	}
}

void GameStateMachine::replaceState(GameState *state)
{
	if(!stateStack.empty())
	{
		if(stateStack.top()->getStateID() == state->getStateID())
			return; // si se va a reemplazar con si mismo, no hace nada (vuelve)
		if (stateStack.top()->onExit())
		{ // si el estado actual sale
			delete stateStack.top(); // lo borra
			stateStack.pop(); // lo borra de la pila
		}
	}
	stateStack.push(state);
	stateStack.top()->onEnter();
}

void GameStateMachine::update()
{
	if (!stateStack.empty())
		stateStack.top()->update();
}

void GameStateMachine::render() const
{
	if (!stateStack.empty())
		stateStack.top()->render();
}

void GameStateMachine::handleEvent(const SDL_Event& event)
{
	if (!stateStack.empty())
		stateStack.top()->handleEvent(event);
}
