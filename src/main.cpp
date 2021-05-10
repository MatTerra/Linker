//
// Created by mateusberardo on 03/05/2021.
//

#include <iostream>
#include <vector>
#include <Module.h>
#include <iomanip>

void updateProgramCode(std::vector<int16_t> &fullCode,
                       std::vector<int16_t> moduleCode);

void updateGlobalUseTable(UseTable &fullUseTable, UseTable moduleUseTable);

void updateGlobalDefinitionTable(DefinitionTable &fullDefinitionTable,
                                 DefinitionTable moduleDefinitionTable);

void resolveSymbolUses(std::vector<int16_t> &fullCode,
                       DefinitionTable &fullDefinitionTable,
                       UseTable &fullUseTable);

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
    
    std::vector<int16_t> fullCode;
    DefinitionTable fullDefinitionTable;
    UseTable fullUseTable;
    uint16_t nowOffset = 0;

    for (auto module : modules) {
        module.applyOffset(nowOffset);

        updateProgramCode(fullCode, module.getModuleCode());

        updateGlobalUseTable(fullUseTable,
                             module.getUseTable());

        updateGlobalDefinitionTable(fullDefinitionTable,
                                    module.getDefinitionTable());

        nowOffset += module.getModuleSize();
    }

    resolveSymbolUses(fullCode, fullDefinitionTable, fullUseTable);

    std::ofstream output;
    std::cout << "Generating output in: " << programName.substr(0, programName.find_last_of('.'))+".obj" << std::endl;
    output.open(programName.substr(0, programName.find_last_of('.'))+".obj") ;
    for (auto memContent : fullCode){
        output << std::setfill('0') << std::setw(2) << memContent << " ";
    }
    output.flush();
    output.close();

    return 0;
}

void resolveSymbolUses(std::vector<int16_t> &fullCode,
                       DefinitionTable &fullDefinitionTable,
                       UseTable &fullUseTable) {
    for (const auto& symbol : fullUseTable.getSymbols()){
        auto uses = fullUseTable.getSymbolUses(symbol);
        try {
            auto addr = fullDefinitionTable.getSymbolAddress(symbol);
            for (auto use : uses){
                fullCode[use] = addr;
            }
        } catch (UndefinedSymbolException &exception) {
            std::cerr << exception.what();
        }
    }
}

void updateGlobalDefinitionTable(DefinitionTable &fullDefinitionTable,
                                 DefinitionTable moduleDefinitionTable) {
    try {
        fullDefinitionTable.merge(moduleDefinitionTable);
    } catch (RedefinedSymbolException &exception) {
        std::cerr << exception.what();
    }
}

void updateGlobalUseTable(UseTable &fullUseTable,
                          UseTable moduleUseTable) {
    fullUseTable.merge(moduleUseTable);
}

void updateProgramCode(std::vector<int16_t> &fullCode,
                       std::vector<int16_t> moduleCode) {
    fullCode.insert(fullCode.end(),
                moduleCode.begin(), moduleCode.end());
}
