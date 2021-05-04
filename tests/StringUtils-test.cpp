//
// Created by mateusberardo on 03/05/2021.
//
#include "gtest/gtest.h"
#include <string>
#include <StringUtils.h>

TEST(StringUtils, shouldGetFirstLine){
    std::string testString = "first line\nsecond line\n";
    ASSERT_EQ("first line", getLine(testString, 0));
}

TEST(StringUtils, shouldGetSecondLine){
    std::string testString = "first line\nsecond line\n";
    ASSERT_EQ("second line", getLine(testString, getLineEnd(testString, 0)+1));
}

TEST(StringUtils, shouldTrimString){
    std::string testString = "   \t\nfirst line\nsecond line\n    \t";
    trim(testString);
    ASSERT_EQ("first line\nsecond line", testString);
}
