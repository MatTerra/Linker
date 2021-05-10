//
// Created by mateusberardo on 09/05/2021.
//
#include "DefinitionTable.h"

void DefinitionTable::addSymbol(std::string symbol, uint16_t address) {
    if (symbols.find(symbol) != symbols.end())
        throw RedefinedSymbolException(symbol);
    symbols.insert(symbols.end(), symbol);
    definitionTable.emplace(symbol, address);
}

uint16_t DefinitionTable::getSymbolAddress(std::string symbol) {
    if (symbols.find(symbol) == symbols.end())
        throw UndefinedSymbolException(symbol);
    return definitionTable[symbol];
}

void DefinitionTable::applyOffset(uint16_t offset) {
    for (const auto& symbol : getSymbols())
        definitionTable[symbol]+=offset;
}

std::vector<std::string> DefinitionTable::getSymbols() {
    return std::vector<std::string>(symbols.begin(), symbols.end());
}

void DefinitionTable::merge(DefinitionTable table) {
    for (const auto& symbol : table.getSymbols())
        addSymbol(symbol, table.getSymbolAddress(symbol));
}
