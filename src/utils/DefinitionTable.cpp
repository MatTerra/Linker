//
// Created by mateusberardo on 09/05/2021.
//

#include "DefinitionTable.h"

void DefinitionTable::addSymbol(std::string symbol, uint16_t address) {
    // TODO symbol already defined
    definitionTable.emplace(symbol, address);
}

uint16_t DefinitionTable::getSymbolAddress(std::string symbol) {
    // TODO symbol not found
    return definitionTable[symbol];
}

void DefinitionTable::applyOffset(uint16_t offset) {
    for (auto symbol : definitionTable){
        auto useVector = &definitionTable[symbol.first];
        *useVector+=offset;
    }
}
