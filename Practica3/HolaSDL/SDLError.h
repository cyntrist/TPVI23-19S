#pragma once
#include "InvadersError.h"

class SDLError : public InvadersError
{
public: 
    SDLError(const std::string& message);
};

