#include <gtest/gtest.h>
//#include <gmock/gmock.h>


extern "C" {
#include "../../src/includes/minishell.h"
}

TEST(is_my_command, is_cd){
	int res = is_my_command("cd");
	EXPECT_EQ(res,1);
}

TEST(is_my_command, empty_command){
	int res = is_my_command("");
	EXPECT_EQ(res,0);
}

TEST(is_my_command, greater_by_one){
	int res = is_my_command("cdd");
	EXPECT_EQ(res,0);
}

TEST(is_my_command, null_command){
	int res = is_my_command(NULL);
	EXPECT_EQ(res,0);
}
TEST(is_my_command, another_right_command){
	int res = is_my_command("env");
	EXPECT_EQ(res,1);
}
