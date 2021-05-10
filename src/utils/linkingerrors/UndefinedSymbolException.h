//
// Created by mateusberardo on 10/05/2021.
//

#ifndef LIGADOR_UNDEFINEDSYMBOLEXCEPTION_H
#define LIGADOR_UNDEFINEDSYMBOLEXCEPTION_H


#include <stdexcept>

class UndefinedSymbolException : public std::runtime_error {
public:
    explicit UndefinedSymbolException(std::string what_arg)
        : std::runtime_error("Symbol "+what_arg+" is not defined!"){}

};


#endif //LIGADOR_UNDEFINEDSYMBOLEXCEPTION_H
