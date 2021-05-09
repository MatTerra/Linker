//
// Created by mateusberardo on 09/05/2021.
//
#include "gtest/gtest.h"
#include <Module.h>
#include <string>

std::string baseHeaders = "H: test\nH: 4\nH: 0100";
std::string textSection = "T: 13 3 14 5"

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

