//
// Created by mateusberardo on 10/05/2021.
//

#ifndef LIGADOR_REDEFINEDSYMBOLEXCEPTION_H
#define LIGADOR_REDEFINEDSYMBOLEXCEPTION_H


#include <stdexcept>

class RedefinedSymbolException : public std::runtime_error {
public:
    explicit RedefinedSymbolException(std::string what_arg)
        : std::runtime_error("Symbol "+what_arg+" is already defined!"){}

};


#endif //LIGADOR_RedefinedSYMBOLEXCEPTION_H
