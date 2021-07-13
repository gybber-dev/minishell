#include <gtest/gtest.h>
//#include <gmock/gmock.h>


extern "C" {
#include "../../src/includes/minishell.h"
#include "builtins.h"
}

TEST(is_builtin, is_cd){
	int res = is_builtin("cd");
	EXPECT_EQ(res,1);
}

TEST(is_builtin, empty_command){
	int res = is_builtin("");
	EXPECT_EQ(res,0);
}

TEST(is_builtin, greater_by_one){
	int res = is_builtin("cdd");
	EXPECT_EQ(res,0);
}

TEST(is_builtin, null_command){
	int res = is_builtin(nullptr);
	EXPECT_EQ(res,0);
}
TEST(is_builtin, another_right_command){
	int res = is_builtin("env");
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
		exec_command(&all);
		i++;
	}
	std_fd(TAKE_FROM, &(all.proc.backup_fd));
	close(all.proc.backup_fd.in);
	close(all.proc.backup_fd.out);
	int fd_check = check_fd();
	EXPECT_EQ(fd_check, 0);
}

//TEST(processor, single_fd_leak){
//	char *envp[] = {
//		"PATH=/Users/yeschall/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki",
//		nullptr
//	};
//	EXPECT_EQ(fd_check, 0);
//}

TEST (check_flag_n, normal)
{
	char *command = "-n";
	int res = check_flag_n(command);
	EXPECT_EQ(res, 1);
}

TEST (check_flag_n, not_flag)
{
	char *command = "n";
	int res = check_flag_n(command);
	EXPECT_EQ(res, 0);
}

TEST (check_flag_n, multi_n)
{
	char *command = "-nnnnn";
	int res = check_flag_n(command);
	EXPECT_EQ(res, 1);
}

TEST (check_flag_n, only_dash)
{
	char *command = "-";
	int res = check_flag_n(command);
	EXPECT_EQ(res, 0);
}


TEST (ft_echo, normal)
{
	char *command[] = {
		"echo",
		"hello",
		nullptr
	};
	char *res = get_stdout_fun_result(command, &ft_echo);
	EXPECT_STREQ(res, "hello\n");
}

TEST (ft_echo, only_echo)
{
	char *command[] = {
			"echo",
			nullptr
	};
	char *res = get_stdout_fun_result(command, &ft_echo);
	EXPECT_STREQ(res, "\n");
}

//TEST (ft_echo, norm_with_n)
//{
//	char *command[] = {
//			"echo",
//			"-n",
//			"hello",
//			nullptr
//	};
//	char *res = get_stdout_fun_result(command, &ft_echo);
//	EXPECT_STREQ(res, "hello");
//}

