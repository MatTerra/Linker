//
// Created by mateusberardo on 09/05/2021.
//
#include "gtest/gtest.h"
#include <DefinitionTable.h>
#include <linkingerrors/UndefinedSymbolException.h>
#include <linkingerrors/RedefinedSymbolException.h>


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

TEST(DefinitionTable, mayGetSymbols){
    DefinitionTable definitionTable;
    definitionTable.addSymbol("test", 1);
    definitionTable.addSymbol("test2", 3);
    ASSERT_EQ((std::vector<std::string>{"test", "test2"}),
              definitionTable.getSymbols());
}

TEST(DefinitionTable, mayMergeTable){
    DefinitionTable definitionTable;
    definitionTable.addSymbol("test", 1);

    DefinitionTable definitionTable2;
    definitionTable2.addSymbol("test1", 2);

    definitionTable.merge(definitionTable2);
    ASSERT_EQ(1, definitionTable.getSymbolAddress("test"));
    ASSERT_EQ(2, definitionTable.getSymbolAddress("test1"));
}

TEST(DefinitionTable, getUndefinedSymbolShouldThrow){
    DefinitionTable definitionTable;
    ASSERT_THROW(definitionTable.getSymbolAddress("test"),
                 UndefinedSymbolException);
}

TEST(DefinitionTable, redefineSymbolShouldThrow){
    DefinitionTable definitionTable;
    definitionTable.addSymbol("test",2);
    ASSERT_THROW(definitionTable.addSymbol("test",1),
                 RedefinedSymbolException);
}

TEST(DefinitionTable, mergeWithRedefineShouldThrow){
    DefinitionTable definitionTable;
    definitionTable.addSymbol("test", 1);

    DefinitionTable definitionTable2;
    definitionTable2.addSymbol("test", 2);

    ASSERT_THROW(definitionTable.merge(definitionTable2),
                 RedefinedSymbolException);
}