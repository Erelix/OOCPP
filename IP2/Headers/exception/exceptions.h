#ifndef EXCEPTIONS_H_75886
#define EXCEPTIONS_H_75886

#include <stdexcept>
#include <string>

namespace pqueue {

class EmptyQueueException : public std::logic_error {
public:
    EmptyQueueException(const std::string &message = "Priority Queue is empty") 
        : std::logic_error(message) {}
};

class InvalidPriorityException : public std::invalid_argument {
public:
    InvalidPriorityException(const std::string &message = "Invalid priority value") 
        : std::invalid_argument(message) {}
};

class DuplicateElementException : public std::logic_error {
public:
    DuplicateElementException(const std::string &message = "Element already exists") 
        : std::logic_error(message) {}
};

}

#endif
