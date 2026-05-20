#ifndef EXCEPTIONS_H_012913
#define EXCEPTIONS_H_012913

#include <stdexcept>
#include <string>

class NotImplementedException : public std::runtime_error {
public:
    explicit NotImplementedException(const std::string& message = "Feature not implemented")
        : std::runtime_error(message) {}
};

class StrategyNotSetException : public std::runtime_error {
public:
    explicit StrategyNotSetException(const std::string& message = "Strategy not set")
        : std::runtime_error(message) {}
};

#endif
