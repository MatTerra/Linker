//
// Created by mateusberardo on 09/05/2021.
//

#ifndef LIGADOR_DEFINITIONTABLE_H
#define LIGADOR_DEFINITIONTABLE_H

#include <string>
#include <set>
#include <unordered_map>


class DefinitionTable {
public:
    void addSymbol(std::string, uint16_t);
    uint16_t getSymbolAddress(std::string);
    void applyOffset(uint16_t offset);
    void merge(DefinitionTable table);
    std::vector<std::string> getSymbols();

private:
    std::unordered_map<std::string, uint16_t> definitionTable;
    std::set<std::string> symbols;
};


#endif //LIGADOR_DEFINITIONTABLE_H
