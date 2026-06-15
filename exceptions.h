#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <string>

using namespace std;

// Manejo de excepciones
class InvalidActionException : public runtime_error {
public:
    InvalidActionException(const string &msg) : runtime_error(msg) {}
};

#endif
