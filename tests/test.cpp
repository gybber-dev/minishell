#include <gtest/gtest.h>
//#include <gmock/gmock.h>


extern "C" {
#include "../src/includes/minishell.h"
}

int test_fun(int res)
{
    return res;
}

TEST(test_fun, nameOfTheTest1){
    int res = test_fun(1);
    ASSERT_EQ(res,1);
}

TEST(test_fun, nameOfTheTest2){
    int res = test_fun(2);
    ASSERT_EQ(res,0);
}