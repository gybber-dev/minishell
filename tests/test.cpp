//#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>


extern "C" {
#include "../GoogleTest/project/project.h"
}



TEST(test_fun, nameOfTheTest1){
    int res = test_fun(1);
    ASSERT_EQ(res,1);
}

TEST(test_fun, nameOfTheTest2){
    int res = test_fun(2);
    ASSERT_EQ(res,0);
}