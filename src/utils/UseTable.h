//
// Created by mateusberardo on 03/05/2021.
//

#ifndef LIGADOR_USETABLE_H
#define LIGADOR_USETABLE_H

#include <string>
#include <vector>
#include <set>
#include <unordered_map>


class UseTable {

public:
    void addSymbol(std::string symbol, std::vector<uint16_t> useAddresses);
    std::vector<uint16_t> getSymbolUses(std::string symbol);
    void applyOffset(uint16_t offset);

    std::vector<std::string> getSymbols();

    void merge(UseTable table);

private:
    std::unordered_map<std::string, std::vector<uint16_t>> useTable;
    std::set<std::string> symbols;
};


#endif //LIGADOR_USETABLE_H
