#pragma once
#include <stdexcept>

class InvadersError : public std::logic_error
{
public:
    InvadersError(const std::string& message);
};

