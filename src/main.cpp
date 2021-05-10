//
// Created by mateusberardo on 03/05/2021.
//

#include <iostream>
#include <vector>
#include <Module.h>

int main(int argc, char **argv){
    if (argc < 2) {
        std::cerr << "Expected at least 1 filename as argument to executable!";
        return 1;
    }
    std::vector<std::string> files;
    for (int i = 1; i < argc; i++) {
        auto filename = std::string(argv[i]);
        auto extension = filename.substr(filename.find_last_of('.'));
        if (extension != ".o"){
            std::cerr << "Expected a .o file!";
            return 1;
        }
        files.insert(files.end(), filename);
    }
    
    std::cout << "Program is composed of " << files.size() << " file(s)."
              << std::endl;

    std::vector<Module> modules;
    for (auto filename : files)
        modules.insert(modules.end(),
                       Module(readFile(filename)));
    
    auto programName = modules[0].getModuleName();
    
    std::vector<uint16_t> fullCode;
    uint16_t nowOffset = 0;
    for (auto module : modules){
        module.applyOffset(nowOffset);
        auto moduleCode = module.getModuleCode();
        fullCode.insert(fullCode.end(),
                        moduleCode.begin(), moduleCode.end());
        nowOffset += module.getModuleSize();
    }

    return 0;
}