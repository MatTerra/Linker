//
// Created by mateusberardo on 09/05/2021.
//
#include "gtest/gtest.h"
#include <DefinitionTable.h>


TEST(DefinitionTable, mayInstantiateDefinitionTable){
    auto definitionTable = new DefinitionTable();
    ASSERT_NE(nullptr, definitionTable);
}

TEST(DefinitionTable, mayGetSymbolAddress){
    DefinitionTable definitionTable;
    definitionTable.addSymbol("test", 1);
    ASSERT_EQ(1, definitionTable.getSymbolAddress("test"));
}

TEST(DefinitionTable, mayApplyOffset){
    DefinitionTable definitionTable;
    definitionTable.addSymbol("test", 1);
    definitionTable.applyOffset(2);
    ASSERT_EQ(3, definitionTable.getSymbolAddress("test"));

}