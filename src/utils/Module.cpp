//
// Created by mateusberardo on 09/05/2021.
//

#include <iostream>
#include "Module.h"

Module::Module(std::string moduleContent) {
    lines = getLines(moduleContent);
    // TODO check that it has the headers
    extractModuleName();
    extractModuleSize();
    extractRelocationMap();
}

void Module::extractModuleSize() {
    size = std::stoi(extractHeaderContent(MODULE_SIZE));
}

void Module::extractModuleName() {
    name = extractHeaderContent(MODULE_NAME);
}

void Module::extractRelocationMap() {
    relocationMap = extractHeaderContent(MODULE_RELOCATION_MAP);
}

std::string Module::extractHeaderContent(uint8_t header) {
    auto headerContent = lines[header].substr(2);
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
