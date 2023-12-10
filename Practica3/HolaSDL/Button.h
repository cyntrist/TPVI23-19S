#pragma once
#include <functional>

#include "GameObject.h"
#include "EventHandler.h"
#include "texture.h"

class Button : public GameObject, public EventHandler
{
protected:
    Texture* texture;
};

