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

TEST(get_value, normal){
	char *arr[3] = {"ar=2", "b=3", nullptr};
	EXPECT_STREQ(get_value(arr, "ar"), "2");
	EXPECT_STREQ(get_value(arr, "b"), "3");
}
TEST(get_value, no_key_in_array){
	char *arr[3] = {"ar=2", "b=3", nullptr};
	char *res = get_value(arr, "bc");
	EXPECT_STREQ(res, nullptr);
}
TEST(get_value, null_array){
	char *arr[1] = {nullptr};
	char *res = get_value(arr, "bc");
	EXPECT_STREQ(res, nullptr);
}
TEST(get_value, empty_value){
	char *arr[2] = {"ar=", nullptr};
	char *res = get_value(arr, "ar");
	EXPECT_STREQ(res, "");
}