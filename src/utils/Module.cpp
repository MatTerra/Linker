//
// Created by mateusberardo on 09/05/2021.
//

#include <iostream>
#include <utility>
#include "Module.h"

Module::Module(std::string moduleContent) {
    lines = getLines(std::move(moduleContent));
    // TODO check that it has the headers
    extractModuleName();
    extractModuleSize();
    extractRelocationMap();
    for (int c=3; c<lines.size(); c++){
        std::string line = lines[c];

        if (line[0] == 'T')
            extractCode(line);
        else if (line[0] == 'H') {

            line = extractLineContent(line);

            char type = line[0];

            line = line.substr(2);
            trim(line);

            if (type == 'D')
                addDefinitionTableEntry(line);
            else if (type == 'U'){
                addUseTableEntry(line);

            }
        }
    }
}

void Module::addUseTableEntry(const std::string &line) {
    std::string symbol = line.substr(0, line.find(' '));
    std::string uses = line.substr(symbol.size() + 1);

    trim(symbol);
    trim(uses);

    useTable.addSymbol(symbol, getNumberVector(uses));
}

void Module::addDefinitionTableEntry(const std::string &line) {
    std::string symbol = line.substr(0, line.find(' '));
    std::string addr = line.substr(symbol.size() + 1);

    trim(symbol);
    trim(addr);
    definitionTable.addSymbol(symbol, std::stoi(addr));
}

void Module::extractModuleSize() {
    size = std::stoi(
            extractLineContent(lines[MODULE_SIZE]));
}

void Module::extractModuleName() {
    name = extractLineContent(lines[MODULE_NAME]);
}

void Module::extractRelocationMap() {
    relocationMap = extractLineContent(lines[MODULE_RELOCATION_MAP]);
}

void Module::extractCode(std::string code) {
    code = extractLineContent(code);
    moduleCode = getNumberVector(code);

}

std::vector<uint16_t> Module::getNumberVector(const std::string &code) {
    std::vector<uint16_t> numbers;
    size_t nextSpace = 0;
    size_t lastSpace = 0;

    while (nextSpace != std::string::npos) {
        nextSpace = code.find(' ', lastSpace+1);

        numbers.insert(numbers.end(),
                          std::stoi(code.substr(lastSpace,
                                                nextSpace-lastSpace)));

        lastSpace=nextSpace;
    }
    return numbers;
}

std::string Module::extractLineContent(std::string line) {
    auto headerContent = line.substr(2);
    trim(headerContent);
    return headerContent;
}

std::string Module::getModuleName() {
    return name;
}

uint16_t Module::getModuleSize() {
    return size;
}

std::string Module::getRelocationMap() {
    return relocationMap;
}

std::vector<uint16_t> Module::getModuleCode() {
    return moduleCode;
}

DefinitionTable Module::getDefinitionTable() {
    return definitionTable;
}

UseTable Module::getUseTable() {
    return useTable;
}

void Module::applyOffset(int offset) {
    useTable.applyOffset(offset);
    definitionTable.applyOffset(offset);
    relocateCode(offset);
}

void Module::relocateCode(int offset) {
    uint64_t codePosition;
    for (codePosition=0; codePosition < moduleCode.size(); codePosition++)
        if(relocationMap[codePosition] == '1')
            moduleCode[codePosition]+=offset;
}
