#pragma once
#include <SDL_events.h>

class EventHandler
{
public:
    virtual void handleEvent(const SDL_Event& event) = 0; //segun el enunciado solo es esto la clase (???
};

