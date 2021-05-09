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

            if (line[0] == 'D') {
                line = line.substr(1);
                trim(line);
                unsigned long space = line.find(' ');
                std::string symbol = line.substr(0, space);
                trim(symbol);
                std::string sAddr = line.substr(space);
                trim(sAddr);
                uint16_t addr = std::stoi(sAddr);
                definitionTable.addSymbol(symbol, addr);
            }
        }
    }
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
