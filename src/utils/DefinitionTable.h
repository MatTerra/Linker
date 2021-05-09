//
// Created by mateusberardo on 09/05/2021.
//

#ifndef LIGADOR_DEFINITIONTABLE_H
#define LIGADOR_DEFINITIONTABLE_H

#include <string>
#include <unordered_map>


class DefinitionTable {
public:
    void addSymbol(std::string, uint16_t);
    uint16_t getSymbolAddress(std::string);
    void applyOffset(uint16_t offset);

private:
    std::unordered_map<std::string, uint16_t> definitionTable;
};


#endif //LIGADOR_DEFINITIONTABLE_H
