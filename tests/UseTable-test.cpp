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
    UseTable useTable;
    std::vector<uint16_t> useAddresses{1,2,3};
    useTable.addSymbol("test", useAddresses);
    ASSERT_EQ(useAddresses, useTable.getSymbolUses("test"));
}

TEST(UseTable, mayApplyOffset){
    UseTable useTable;
    std::vector<uint16_t> useAddresses{1,2,3};
    useTable.addSymbol("test", useAddresses);
    useTable.applyOffset(2);
    ASSERT_EQ((std::vector<uint16_t>{3,4,5}), useTable.getSymbolUses("test"));
}

TEST(UseTable, shouldListSymbols){
    UseTable useTable;
    useTable.addSymbol("test", (std::vector<uint16_t>) {1});
    useTable.addSymbol("test2", (std::vector<uint16_t>) {2});
    ASSERT_EQ((std::vector<std::string>{"test", "test2"}),
              useTable.getSymbols());
}

TEST(UseTable, duplicateEntryShouldExpandUses){
    UseTable useTable;
    useTable.addSymbol("test", (std::vector<uint16_t>) {1});
    useTable.addSymbol("test", (std::vector<uint16_t>) {2});
    ASSERT_EQ((std::vector<uint16_t>{1, 2}),
              useTable.getSymbolUses("test"));
}

TEST(UseTable, mayMergeUseTables){
    UseTable useTable;
    useTable.addSymbol("test", (std::vector<uint16_t>) {1});
    useTable.addSymbol("test2", (std::vector<uint16_t>) {2});

    UseTable useTable2;
    useTable2.addSymbol("test", (std::vector<uint16_t>) {5});
    useTable2.addSymbol("test2", (std::vector<uint16_t>) {7});

    useTable.merge(useTable2);
    ASSERT_EQ((std::vector<uint16_t>{1, 5}),
              useTable.getSymbolUses("test"));
    ASSERT_EQ((std::vector<uint16_t>{2, 7}),
              useTable.getSymbolUses("test2"));
}
