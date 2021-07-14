#include "../includes/minishell.h"

char			**check_key(char **envs, char *key)
{
	char		**tmp;
	int			key_len;

	tmp = envs;
	if (!key)
		return NULL;
	key_len = (int)ft_strlen(key);
	while(*tmp != NULL)
	{
		if (!ft_strncmp(*tmp, key, key_len) && *(*tmp + key_len) == '=')
			return (tmp);
		if (!ft_strncmp(*tmp, key, key_len + 1))
			return (tmp);
		tmp++;
	}
	return (NULL);
}

/**
** @param envs
** @param key
** @return pointer to value
*/

char			*get_value(char **envs, char *key)
{
	char		**tmp;
	int			key_len;

	if (!key)
		return NULL;
	key_len = (int)ft_strlen(key);
	tmp = check_key(envs, key);
	if (!tmp)
		return (NULL);
	if (*((*tmp) + key_len) == '=')
		return ((*tmp) + key_len + 1);
	return ((*tmp) + key_len);
}

void		print_array_2x(char **arr)
{
	char	**tmp;

	tmp = arr;
	printf("======================\n");
	while(*tmp)
	{
		printf("'%s'\n", *tmp);
		tmp++;
	}
	printf(" '%s'\n", *tmp);
	printf("======================\n");
}

char		**copy_arrays_2x(char **src_arr)
{
	int		i;
	char	**tmp_src;
	char	**tmp_dst;
	char	**res_arr;

	i = 0;
	if (!src_arr)
		return NULL;
	tmp_src = src_arr;
	while(*(tmp_src++)) {
		i++;
	}
	res_arr = (char **) malloc(sizeof(char *) * i + 1);
	tmp_src = src_arr;
	tmp_dst = res_arr;
	while(*tmp_src)
	{
		*tmp_dst = ft_strdup(*tmp_src);
		tmp_src++;
		tmp_dst++;
	}
	*tmp_dst = NULL;
	return res_arr;
}

void		clear_arr_2x(char **arr)
{
	int		i;

	i = 0;
	while(arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

/**
 *
 * @param cmnd
 * @param paths $PATH string
 * @return char* MALLOCED path to binary
 */

char   *find_binary(char *cmnd, char *paths)
{
	char  *path;
	char  **arr;
	char  **tmp;
	struct stat buf;

	path = NULL;
	if (!cmnd || !paths || (*paths == 0) || (*cmnd) == 0)
		return NULL;
	arr = ft_split(paths, ':');
	tmp = arr;
	cmnd = ft_strjoin("/", cmnd);
	while(*tmp)
	{
		path = ft_strjoin(*tmp, cmnd);
		if (stat(path, &buf) == 0)
			break;
		free(path);
		path = NULL;
		tmp++;
	}
	free(cmnd);
	clear_arr_2x(arr);
	return path;
}

/**
** Reads data from "from" and writes to "to".
** How to usage?
**	int fd_write = open("here.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
**	int fd_read = open("foo.txt", O_RDONLY);
**	read_from_write_to(fd_read, fd_write);
** @param from	input fd
** @param to	output fd
*/

void 		read_from_write_to(int from, int to)
{
	char	*buf;
	int 	res;

	buf = (char *)malloc(2);
	buf[1] = 0;
	buf[0] = 'e';
	printf("%s\n", buf);
	while(1)
	{
		res = read(from, buf, 1);
		if (res == 0)
			break;
		write(to, buf, 1);
	}
	free(buf);
}

/**
** Redirects stdout of command to buffer variable. Needs to free buffer
** Buffer size is 1000
** @param cmd list of commands
** @return malloced pointer to result of command
*/

char 	*get_command_result(char **cmd)
{
	int fd[2];
	char *buffer;

	buffer = malloc(1000);
	pipe(fd);
	if (fork() == 0) {
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execvp(cmd[0],cmd);
	}
	else
	{
		ssize_t size = read(fd[0], buffer, 1000);
		if ( (size>0) && (size<sizeof(buffer)) )
		{
			buffer[size]='\0';
		}
		close(fd[0]);
		close(fd[1]);
	}
	return buffer;
}

char 	*get_stdout_fun_result(char **cmd, void (*fun)(char **))
{
	int fd[2];
	char *buffer;

	buffer = malloc(1000);
	pipe(fd);
	if (fork() == 0) {
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		fun(cmd);
	}
	else
	{
		ssize_t size = read(fd[0], buffer, 1000);
		if ( (size>0) && (size<sizeof(buffer)) )
		{
			buffer[size]='\0';
		}
		close(fd[0]);
		close(fd[1]);
	}
	return buffer;
}

int			get_arr_2x_len(char **arr)
{
	int 	res;

	res = 0;
	while(*arr++)
		res++;
	return res;
}

void		set_value_arr_2x(char *str, char ***arr) {
	int len;
	char **old_line;
	char *equal;
	char *new_line;
	char **res;

	if (!(new_line = ft_strdup(str)))
		exit(EXIT_FAILURE);
	equal = ft_strchr(new_line, '=');
	*equal = 0;
	if ((old_line = check_key(*arr, new_line))) {
		*equal = '=';
		free(*old_line);
		*old_line = new_line;
	} else {
		*equal = '=';
		lineaddback(arr, new_line);
		free(new_line);
	}
}
/**
 * @param src is allocated array for (char *)
 * @param addback is line, which add back to src **
 * src is reallocated with free old src
 * addback is not free
 */

void		lineaddback(char ***src,char *addback)
{
	int		i;
	char	**arr;

	i = 0;
	while(*(*src + i) != NULL)
		i++;
	arr = (char **)malloc((i += 2) * sizeof(char *));//realloc for char** + 1 line
	arr[--i] = NULL;
	arr[--i] = ft_strdup((const char*)addback);
	while (--i > -1)
		*(arr + i) = *(*src + i);
	free(*src);
	*src = arr;
}