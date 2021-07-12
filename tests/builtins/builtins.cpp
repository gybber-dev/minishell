#include <gtest/gtest.h>
//#include <gmock/gmock.h>


extern "C" {
#include "../../src/includes/minishell.h"
#include "builtins.h"
}
//
//TEST(is_my_command, is_cd){
//	int res = is_my_command("cd");
//	EXPECT_EQ(res,1);
//}
//
//TEST(is_my_command, empty_command){
//	int res = is_my_command("");
//	EXPECT_EQ(res,0);
//}
//
//TEST(is_my_command, greater_by_one){
//	int res = is_my_command("cdd");
//	EXPECT_EQ(res,0);
//}
//
//TEST(is_my_command, null_command){
//	int res = is_my_command(NULL);
//	EXPECT_EQ(res,0);
//}
//TEST(is_my_command, another_right_command){
//	int res = is_my_command("env");
//	EXPECT_EQ(res,1);
//}

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
TEST(get_value, no_equal_symbol){
	char *arr[2] = {"cc", nullptr};
	char *res = get_value(arr, "cc");
	EXPECT_STREQ(res, "");
}

TEST(find_binary, normal){
	char path[] = "/Users/yeschall/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki";
	char *res = find_binary("ls", path);
	EXPECT_STREQ(res, "/bin/ls");
}

TEST(find_binary, null_cmd){
	char path[] = "/Users/yeschall/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki";
	char *res = find_binary(nullptr, path);
	EXPECT_STREQ(res, nullptr);
}

TEST(find_binary, null_path){
	char path[] = "/Users/yeschall/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki";
	char *res = find_binary("ls", nullptr);
	EXPECT_STREQ(res, nullptr);
}

TEST(find_binary, empty_path){
	char path[] = "";
	char *res = find_binary("ls", path);
	EXPECT_STREQ(res, nullptr);
}

TEST(find_binary, empty_cmd){
	char path[] = "/Users/yeschall/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki";
	char *res = find_binary("", path);
	EXPECT_STREQ(res, nullptr);
}

TEST(find_binary, incorrect_cmd){
	char path[] = "/Users/yeschall/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki";
	char *res = find_binary("lssss", path);
	EXPECT_STREQ(res, nullptr);
}

TEST(builtins, single_fd_leak){
	t_all all;
	int i = 0;
//	char *envp[] = {
//			"PATH=/Users/yeschall/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki",
//			nullptr
//	}
	init_all(&all);
	while (1) {
		generate_cmd(1, &all, i);
		if (!all.cmd)
			break;
		builtins(&all);
		i++;
	}
	std_fd(TAKE_FROM, &(all.proc.backup_fd));
	close(all.proc.backup_fd.in);
	close(all.proc.backup_fd.out);
	int fd_check = check_fd();
	EXPECT_EQ(fd_check, 0);
}