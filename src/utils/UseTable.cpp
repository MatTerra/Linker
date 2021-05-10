//
// Created by mateusberardo on 03/05/2021.
//
#include <algorithm>
#include "UseTable.h"

void UseTable::addSymbol(std::string symbol,
                         std::vector <uint16_t> useAddresses) {
    if (symbols.find(symbol) != symbols.end()) {
        useTable[symbol].insert(useTable[symbol].end(),
                                useAddresses.begin(), useAddresses.end());
    }
    else {
        useTable.emplace(symbol, useAddresses);
        symbols.insert(symbols.end(), symbol);
    }
}

std::vector<uint16_t> UseTable::getSymbolUses(std::string symbol) {
    return useTable[symbol];
}

void UseTable::applyOffset(uint16_t offset) {
    for (auto symbol : symbols){
        std::transform(useTable[symbol].begin(), useTable[symbol].end(),
                       useTable[symbol].begin(),
                       [offset](uint16_t addr){ return addr+offset; });
    }
}

std::vector<std::string> UseTable::getSymbols() {
    return std::vector<std::string>(symbols.begin(), symbols.end());
}

void UseTable::merge(UseTable table) {
    for(auto symbol : table.getSymbols())
        addSymbol(symbol, table.getSymbolUses(symbol));
}
