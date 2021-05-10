//
// Created by mateusberardo on 09/05/2021.
//
#include "gtest/gtest.h"
#include <Module.h>
#include <string>

std::string baseHeaders = "H: test\nH: 4\nH: 0100\n";
std::string definitionTable = "H: D my 3\n";
std::string useTable = "H: U use 1 3\n";
std::string textSection = "T: 13 3 14 5 -1\n";


TEST(Module, mayInstantiateModule){
    auto module = new Module(baseHeaders);
    ASSERT_NE(nullptr, module);
}

TEST(Module, mayGetName){
    Module module(baseHeaders);
    ASSERT_EQ("test", module.getModuleName());
}

TEST(Module, mayGetModuleSize){
    Module module(baseHeaders);
    ASSERT_EQ(4, module.getModuleSize());
}

TEST(Module, mayGetRelocationMap){
    Module module(baseHeaders);
    ASSERT_EQ("0100", module.getRelocationMap());
}

TEST(Module, mayGetTextSection){
    Module module(baseHeaders+textSection);
    std::vector<int16_t> text{13,3,14,5,-1};
    ASSERT_EQ(text, module.getModuleCode());
}

TEST(Module, generatesDefinitionTable){
    Module module(baseHeaders+definitionTable+textSection);
    ASSERT_EQ(3, module.getDefinitionTable().getSymbolAddress("my"));
}

TEST(Module, generatesUseTable){
    Module module(baseHeaders+definitionTable+useTable+textSection);
    ASSERT_EQ((std::vector<uint16_t>{1,3}),
              module.getUseTable().getSymbolUses("use"));
}

TEST(Module, offsetShouldApplyToAllTables){
    Module module(baseHeaders+definitionTable+useTable+textSection);
    module.applyOffset(2);
    ASSERT_EQ((std::vector<uint16_t>{3,5}),
              module.getUseTable().getSymbolUses("use"));
    ASSERT_EQ(5, module.getDefinitionTable().getSymbolAddress("my"));
    ASSERT_EQ(5, module.getModuleCode()[1]);
}

