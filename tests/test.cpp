//#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>


extern "C" {
<<<<<<< HEAD:tests/test.cpp
#include "../GoogleTest/project/project.h"
=======
#include "../../includes/minishell.h"
>>>>>>> b69bc247808f96299bcaf0249f527ac120621c4d:GoogleTest/Tests/test.cpp
}



TEST(test_fun, nameOfTheTest1){
    int res = test_fun(1);
    ASSERT_EQ(res,1);
}

TEST(test_fun, nameOfTheTest2){
    int res = test_fun(2);
    ASSERT_EQ(res,0);
}