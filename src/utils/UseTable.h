//
// Created by mateusberardo on 03/05/2021.
//

#ifndef LIGADOR_USETABLE_H
#define LIGADOR_USETABLE_H

#include <string>
#include <vector>
#include <unordered_map>


class UseTable {

public:
    void addSymbol(std::string symbol, std::vector<uint16_t> useAddresses);

    std::vector<uint16_t> getSymbolUses(std::string symbol);

    void applyOffset(uint16_t offset);

private:
    std::unordered_map<std::string, std::vector<uint16_t>> useTable;
};


#endif //LIGADOR_USETABLE_H
