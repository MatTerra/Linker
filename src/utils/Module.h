//
// Created by mateusberardo on 09/05/2021.
//

#ifndef LIGADOR_MODULE_H
#define LIGADOR_MODULE_H

#include <vector>
#include <string>
#include "StringUtils.h"
#include "DefinitionTable.h"
#include "UseTable.h"

#define MODULE_NAME 0
#define MODULE_SIZE 1
#define MODULE_RELOCATION_MAP 2

class Module {
public:
    Module(std::string moduleContent);
    std::string getModuleName();
    uint16_t getModuleSize() const;
    std::string getRelocationMap();

    std::vector<int16_t> getModuleCode();

    DefinitionTable getDefinitionTable();

    UseTable getUseTable();

    void applyOffset(int offset);

private:
    std::vector<std::string> lines;
    std::string name;
    uint16_t size;
    std::string relocationMap;
    std::vector<int16_t> moduleCode;
    DefinitionTable definitionTable;
    UseTable useTable;

    void extractModuleName();
    void extractRelocationMap();
    void extractModuleSize();
    static std::string extractLineContent(std::string line);
    void extractCode(std::string code);
    static std::vector<int16_t> getNumberVector(const std::string &code);
    void addDefinitionTableEntry(const std::string &line);

    void addUseTableEntry(const std::string &line);

    void relocateCode(int offset);

    std::vector<uint16_t> getUnsignedNumberVector(const std::string &code);
};


#endif //LIGADOR_MODULE_H
