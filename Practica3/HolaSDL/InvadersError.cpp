#include "InvadersError.h"
#include "string"
InvadersError::InvadersError(const std::string& message) : logic_error(message)
{ }


