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
	char *res = get_stdout_fun_result(command, ft_echo, nullptr);
	EXPECT_STREQ(res, "hello\n");
}

TEST (ft_echo, only_echo)
{
	char *command[] = {
			"echo",
			nullptr
	};
	char *res = get_stdout_fun_result(command, &ft_echo, nullptr);
	EXPECT_STREQ(res, "\n");
}

TEST (ft_echo, norm_with_n)
{
	char *command[] = {
			"echo",
			"hello",
			nullptr
	};
	char **tmp = environ;
	char *res = get_stdout_fun_result(command, &ft_echo, nullptr);
	char *orig = get_command_result(command, nullptr);
	EXPECT_STREQ(res, orig);
}

TEST (get_arr2_len, norm)
{
	char *command[] = {
			"echo",
			"hello",
			nullptr
	};
	int res = get_arr_2x_len(command);
	EXPECT_EQ(res, 2);
}

TEST (get_arr_2x_len, null_arr)
{
	char *command[] = {
			nullptr
	};
	int res = get_arr_2x_len(command);
	EXPECT_EQ(res, 0);
}

TEST (check_var_name, normal)
{
	int res = check_var_name("hel=1");
	EXPECT_EQ(res, 1);
}

TEST (check_var_name, without_value)
{
	int res = check_var_name("hel=");
	EXPECT_EQ(res, 1);
}

TEST (check_var_name, without_equal)
{
	int res = check_var_name("hel");
	EXPECT_EQ(res, 0);
}

TEST (check_var_name, first_digit)
{
	int res = check_var_name("1hel=0");
	EXPECT_EQ(res, 0);
}
TEST (check_var_name, first__)
{
	int res = check_var_name("_hel=0");
	EXPECT_EQ(res, 1);
}
TEST (check_var_name, wrong_symbol_in_name)
{
	int res = check_var_name("he<l=0");
	EXPECT_EQ(res, 0);
}

TEST (ft_export, normal)
{
	char *command[] = {
			"export",
			"aa=2",
			nullptr
	};
	char **arr = (char **)malloc(sizeof(char *) * 3);
	arr[0] = ft_strdup("a=1");
	arr[1] = ft_strdup("b=2");
	arr[2] = nullptr;
	int res = ft_export(command, &arr);
	EXPECT_STREQ(arr[0], "a=1");
	EXPECT_STREQ(arr[1], "b=2");
	EXPECT_STREQ(arr[2], "aa=2");
	EXPECT_STREQ(arr[3], nullptr);
}

TEST (ft_export, without_equal)
{
	char *command[] = {
			"export",
			"aa2",
			nullptr
	};
	char **arr = (char **)malloc(sizeof(char *) * 3);
	arr[0] = ft_strdup("a=1");
	arr[1] = ft_strdup("b=2");
	arr[2] = nullptr;
	int res = ft_export(command, &arr);
	EXPECT_STREQ(arr[0], "a=1");
	EXPECT_STREQ(arr[1], "b=2");
	EXPECT_STREQ(arr[2], nullptr);
	EXPECT_EQ(res, 0);
}

TEST (ft_export, without_val)
{
	char **command = (char **)malloc(sizeof(char *) * 3);
	command[0] = ft_strdup("export");
	command[1] = ft_strdup("aa2=");
	command[2] = nullptr;

	char **arr = (char **)malloc(sizeof(char *) * 3);
	arr[0] = ft_strdup("a=1");
	arr[1] = ft_strdup("b=2");
	arr[2] = nullptr;
	int res = ft_export(command, &arr);
	EXPECT_STREQ(arr[0], "a=1");
	EXPECT_STREQ(arr[1], "b=2");
	EXPECT_STREQ(arr[2], "aa2=\"\"");
	EXPECT_EQ(res, 1);
}

TEST (ft_export, add_two_vars)
{
	char **command = (char **)malloc(sizeof(char *) * 4);
	command[0] = ft_strdup("export");
	command[1] = ft_strdup("c=");
	command[2] = ft_strdup("d=");
	command[3] = nullptr;

	char **arr = (char **)malloc(sizeof(char *) * 3);
	arr[0] = ft_strdup("a=1");
	arr[1] = ft_strdup("b=2");
	arr[2] = nullptr;
	int res = ft_export(command, &arr);
	EXPECT_STREQ(arr[0], "a=1");
	EXPECT_STREQ(arr[1], "b=2");
	EXPECT_STREQ(arr[2], "c=\"\"");
	EXPECT_STREQ(arr[3], "d=\"\"");
	EXPECT_STREQ(arr[4], nullptr);
	EXPECT_EQ(res, 1);
}

TEST (ft_export, invalid_var_name)
{
	char *command[] = {
			"export",
			"a 2=",
			nullptr
	};
	char **arr = (char **)malloc(sizeof(char *) * 3);
	arr[0] = ft_strdup("a=1");
	arr[1] = ft_strdup("b=2");
	arr[2] = nullptr;
	int res = ft_export(command, &arr);
	EXPECT_STREQ(arr[0], "a=1");
	EXPECT_STREQ(arr[1], "b=2");
	EXPECT_STREQ(arr[2], nullptr);
	EXPECT_EQ(res, 0);
}


TEST (set_value_arr_2x, rewrite)
{
	char **arr = (char **)malloc(sizeof(char *) * 3);
	arr[0] = ft_strdup("a=1");
	arr[1] = ft_strdup("aa=2");
	arr[2] = nullptr;
	char *new_val = "a=3";
	set_value_arr_2x(new_val, &arr);
	char *res = arr[0];
	EXPECT_STREQ(res, new_val);
}

TEST (set_value_arr_2x, add_last)
{
	char **arr;

	arr = (char **)malloc(sizeof(char *) * 3);
	arr[0] = ft_strdup("a=1");
	arr[1] = ft_strdup("aa=2");
	arr[2] = nullptr;
	char *new_val = "b=3";
	set_value_arr_2x(new_val, &arr);
	char *res = arr[2];
	EXPECT_STREQ(res, new_val);
}

TEST (set_value_arr_2x, add_in_empty_arr)
{
	char **arr;

	arr = (char **)malloc(sizeof(char *) * 3);
	arr[0] = ft_strdup("a=1");
	arr[1] = ft_strdup("aa=2");
	arr[2] = nullptr;
	char *new_val = "b=3";
	set_value_arr_2x(new_val, &arr);
	char *res = arr[2];
	EXPECT_STREQ(res, new_val);
}

TEST (set_value_arr_2x, add_in_empty_val)
{
	char **arr;

	arr = (char **)malloc(sizeof(char *) * 3);
	arr[0] = ft_strdup("a=1");
	arr[1] = ft_strdup("aa=2");
	arr[2] = nullptr;
	char *new_val = "";
	set_value_arr_2x(new_val, &arr);
	char *res = arr[2];
	EXPECT_STREQ(res, nullptr);
}

TEST (lineaddback, normal)
{
	char **arr;

	arr = (char **)malloc(sizeof(char *) * 3);
	arr[0] = ft_strdup("a=1");
	arr[1] = ft_strdup("aa=2");
	arr[2] = nullptr;
	char *new_val = "b=3";
	lineaddback(&arr, new_val);
	char *res = arr[2];
	EXPECT_STREQ(res, new_val);
	EXPECT_STREQ(arr[3], nullptr);
}

TEST (lineaddback, add_empty)
{
	char **arr;

	arr = (char **)malloc(sizeof(char *) * 3);
	arr[0] = ft_strdup("a=1");
	arr[1] = ft_strdup("aa=2");
	arr[2] = nullptr;
	char *new_val = "";
	lineaddback(&arr, new_val);
	char *res = arr[2];
	EXPECT_STREQ(res, new_val);
}

TEST (lineaddback, add_null)
{
	char **arr;

	arr = (char **)malloc(sizeof(char *) * 3);
	arr[0] = ft_strdup("a=1");
	arr[1] = ft_strdup("aa=2");
	arr[2] = nullptr;
	char *new_val = nullptr;
	lineaddback(&arr, new_val);
	char *res = arr[2];
	EXPECT_STREQ(res, new_val);
}

TEST (lineaddback, add_in_null)
{
	char **arr;

	arr = (char **)malloc(sizeof(char *) * 1);
	arr[0] = nullptr;
	char *new_val = "b=3";
	lineaddback(&arr, new_val);
	char *res = arr[0];
	EXPECT_STREQ(res, new_val);
	EXPECT_STREQ(arr[1], nullptr);
}

TEST (del_line_arr_2x, normal)
{
	char **arr;
	arr = (char **)malloc(sizeof(char *) * 3);
	arr[0] = ft_strdup("a=1");
	arr[1] = ft_strdup("aa=2");
	arr[2] = nullptr;
	char *del_val = "a";
	del_line_arr_2x(del_val, &arr);
	char *res = arr[0];
	EXPECT_STREQ(res, "aa=2");
}
TEST (del_line_arr_2x, normal_del_from_middle)
{
	char **arr;
	arr = (char **)malloc(sizeof(char *) * 3);
	arr[0] = ft_strdup("a=1");
	arr[1] = ft_strdup("aa=2");
	arr[2] = nullptr;
	char *del_val = "aa";
	del_line_arr_2x(del_val, &arr);
	char *res = arr[1];
	EXPECT_STREQ(res, nullptr);
}

TEST (del_line_arr_2x, no_key)
{
	char **arr;
	arr = (char **)malloc(sizeof(char *) * 3);
	arr[0] = ft_strdup("a=1");
	arr[1] = ft_strdup("aa=2");
	arr[2] = nullptr;
	int res_backup = get_arr_2x_len(arr);
	char *del_val = "bb";
	del_line_arr_2x(del_val, &arr);
	int res_changed = get_arr_2x_len(arr);
	EXPECT_EQ(res_backup, res_changed);
}


