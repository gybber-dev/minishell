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
//	printf("======================\n");
	while(*tmp)
	{
		printf("\t%s\n", *tmp);
		tmp++;
	}
	printf(" \t%s\n", *tmp);
//	printf("======================\n");
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

void		clear_arr_2x(char ***arr)
{
	int		i;
	int size;

	i = 0;
	size = get_arr_2x_len(*arr);
	while (i < size)
		free((*arr)[i++]);
	free(*arr);
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
	clear_arr_2x(&arr);
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

char 	*get_command_result(char **cmd, char **env)
{
	int fd[2];
	char *buffer;
	char *path;

	buffer = malloc(1000);
	pipe(fd);
	if (fork() == 0) {
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		if (env){
			path = find_binary(cmd[0], get_value(env, "PATH"));
			execve(path, cmd, env);
		}else{
			execvp(cmd[0], cmd);
		}
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

char 	*get_stdout_fun_result(char **cmd, int (*fun)(char **, char **), char
**env)
{
	int fd[2];
	char *buffer;

	buffer = malloc(1000);
	pipe(fd);
	if (fork() == 0) {
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		if (env)
			fun(cmd, env);
		else
			fun(cmd, NULL);
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

int			set_value_arr_2x(char *str, char ***arr)
{
	char **old_line;
	char *equal;
	char *new_line;

	if (!(new_line = ft_strdup(str)))
		return EXIT_FAILURE;
	if (!(equal = ft_strchr(new_line, '=')))
		return (ft_error("Don't work with shell variables", 1));
	*equal = 0;
	if ((old_line = check_key(*arr, new_line)))
	{
		*equal = '=';
		free(*old_line);
		*old_line = new_line;
	} else
	{
		*equal = '=';
		lineaddback(arr, new_line);
		free(new_line);
	}
	return 0;
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
	if (!addback)
		return;
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

int 		del_line_arr_2x(char *line, char ***src)
{
	int		size;
	char	**arr;
	char	**found_line;
	char	**tmp;
	char 	**tmp_src;
	char	**tmp_arr;

	found_line = check_key(*src, line);
	if (!found_line)
		return EXIT_SUCCESS;
	size = get_arr_2x_len(*src);
	if (!(arr = (char **)malloc(size * sizeof(char *))))
		return (EXIT_FAILURE);
//	arr[size] = NULL;
//	free(**src);
//	tmp = *src;
//	while (*tmp)
//	{
//		if (*tmp != *found_line)
//			if (!(*arr = ft_strdup(*tmp)))
//				return (EXIT_FAILURE);
//		tmp++;
//	}
	tmp_src = *src;
	tmp_arr = arr;
	while(*tmp_src)
	{
		if (*tmp_src != *found_line)
			*tmp_arr = ft_strdup(*tmp_src);
		else
			tmp_arr--;
		tmp_src++;
		tmp_arr++;
	}
	*tmp_arr = NULL;
//	free(**src);
	clear_arr_2x(src);
	*src = arr;
	return (EXIT_SUCCESS);
}

int			free_and_return(char **mem, int res)
{
	if (*mem)
		free(*mem);
	*mem = NULL;
	return res;
}

int				ft_error(char *err_msg, int res)
{
	printf("%s\n", err_msg);
	return res;
}

int				ft_perror(char *msg, int res)
{
	perror(msg);
	return res;
}