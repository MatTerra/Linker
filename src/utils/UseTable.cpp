//
// Created by mateusberardo on 03/05/2021.
//
#include <algorithm>
#include "UseTable.h"

void UseTable::addSymbol(std::string symbol,
                         std::vector <uint16_t> useAddresses) {
    useTable.emplace(symbol, useAddresses);
}

std::vector<uint16_t> UseTable::getSymbolUses(std::string symbol) {
    return useTable[symbol];
}

void UseTable::applyOffset(uint16_t offset) {
    for (auto symbol : useTable){
        auto useVector = &useTable[symbol.first];
        std::transform(useVector->begin(), useVector->end(), useVector->begin(),
                       [offset](uint16_t addr){ return addr+offset; });
    }
}
