//
// Created by mateusberardo on 03/05/2021.
//
#include "gtest/gtest.h"
#include <UseTable.h>


TEST(UseTable, mayInstantiateUseTable){
    auto useTable = new UseTable();
    ASSERT_NE(nullptr, useTable);
}

TEST(UseTable, mayGetSymbolUses){
    auto useTable = new UseTable();
    std::vector<uint16_t> useAddresses{1,2,3};
    useTable->addSymbol("test", useAddresses);
    ASSERT_EQ(useAddresses, useTable->getSymbolUses("test"));
}

TEST(UseTable, mayApplyOffset){
    auto useTable = new UseTable();
    std::vector<uint16_t> useAddresses{1,2,3};
    useTable->addSymbol("test", useAddresses);
    useTable->applyOffset(2);
    ASSERT_EQ((std::vector<uint16_t>{3,4,5}), useTable->getSymbolUses("test"));
}
