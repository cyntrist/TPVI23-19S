#include "InvadersError.h"
#include "string"
InvadersError::InvadersError(const std::string& message) : logic_error(message)
{
    m = message;
}
char const* InvadersError::what() const
{
    return m.c_str();
}


