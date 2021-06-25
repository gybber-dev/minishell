#include <gtest/gtest.h>
//#include <gmock/gmock.h>


extern "C" {
#include "../src/includes/minishell.h"
}

TEST(test_fun, nameOfTheTest1){
    int res = test_fun(1);
    EXPECT_EQ(res,1);
}

TEST(test_fun, nameOfTheTest2){
    int res = test_fun(2);
    EXPECT_EQ(res,0);
}