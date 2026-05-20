#include "../Headers/exceptions.h"

NotImplementedException::NotImplementedException(const std::string& message)
    : std::runtime_error(message) {}

StrategyNotSetException::StrategyNotSetException(const std::string& message)
    : std::runtime_error(message) {}