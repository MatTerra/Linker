//
// Created by mateusberardo on 09/05/2021.
//

#include "DefinitionTable.h"

void DefinitionTable::addSymbol(std::string symbol, uint16_t address) {
    definitionTable.emplace(symbol, address);
}

uint16_t DefinitionTable::getSymbolAddress(std::string symbol) {
    return definitionTable[symbol];
}

void DefinitionTable::applyOffset(uint16_t offset) {
    for (auto symbol : definitionTable){
        auto useVector = &definitionTable[symbol.first];
        *useVector+=offset;
    }
}
