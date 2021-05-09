//
// Created by mateusberardo on 09/05/2021.
//

#ifndef LIGADOR_MODULE_H
#define LIGADOR_MODULE_H

#include <vector>
#include <string>
#include "StringUtils.h"

#define MODULE_NAME 0
#define MODULE_SIZE 1
#define MODULE_RELOCATION_MAP 2

class Module {
public:
    Module(std::string moduleContent);
    std::string getModuleName();
    uint16_t getModuleSize();
    std::string getRelocationMap();

private:
    std::vector<std::string> lines;
    std::string name;
    uint16_t size;
    std::string relocationMap;

    void extractModuleName();
    void extractRelocationMap();
    void extractModuleSize();
    std::string extractHeaderContent(uint8_t);
};


#endif //LIGADOR_MODULE_H
