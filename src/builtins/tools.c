#include "../includes/minishell.h"

void	print_all(t_all *all)
{
	int	i;

	printf("\n================================\ncommands:\n");
	if (!(all->cmd->command))
		printf("\t%s\n", NULL);
	else
		print_array_2x(all->cmd->command);
	printf("redirs:\n");
	if (!(all->cmd->reds))
		printf("\t%s\n", NULL);
	else
	{
		i = 0;
		while (all->cmd->reds[i])
		{
			printf("\t%d. type: %d\n", i, all->cmd->reds[i]->type);
			printf("\t%d.  val: %s\n", i, all->cmd->reds[i]->value);
			printf("\t---\n");
			i++;
		}
		printf("\t%d.  %s\n", i, NULL);
		printf("-----\nis spec  : %d\n", all->cmd->spec);
		printf("is pipe  : %d\n", all->is_pipel);
	}
	printf("\n================================\n");
}

char	**check_key(char **envs, char *key)
{
	char		**tmp;
	int			key_len;

	tmp = envs;
	if (!key)
		return (NULL);
	key_len = (int)ft_strlen(key);
	while (*tmp != NULL)
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

char	*get_value(char **envs, char *key)
{
	char		**tmp;
	int			key_len;

	if (!key)
		return (NULL);
	key_len = (int)ft_strlen(key);
	tmp = check_key(envs, key);
	if (!tmp)
		return (NULL);
	if (*((*tmp) + key_len) == '=')
		return ((*tmp) + key_len + 1);
	return ((*tmp) + key_len);
}

/**
 *
 * @param cmnd
 * @param paths $PATH string
 * @return char* MALLOCED path to binary
 */

char	*find_binary(char *cmnd, char *paths)
{
	char			*path;
	char			**arr;
	char			**tmp;
	struct stat		buf;

	path = NULL;
	if (!cmnd || !paths || (*paths == 0) || (*cmnd) == 0)
		return (NULL);
	arr = ft_split(paths, ':');
	tmp = arr;
	cmnd = ft_strjoin("/", cmnd);
	while (*tmp)
	{
		path = ft_strjoin(*tmp, cmnd);
		if (stat(path, &buf) == 0)
			break ;
		free(path);
		path = NULL;
		tmp++;
	}
	free(cmnd);
	clear_arr_2x(&arr);
	return (path);
}

int	set_value_arr_2x(char *str, char ***arr)
{
	char	**old_line;
	char	*equal;
	char	*new_line;

	new_line = ft_strdup(str);
	if (!new_line)
		return (EXIT_FAILURE);
	equal = ft_strchr(new_line, '=');
	if (!equal)
		return (ft_error("Don't work with shell variables", 1));
	*equal = 0;
	old_line = check_key(*arr, new_line);
	if (old_line)
	{
		*equal = '=';
		free(*old_line);
		*old_line = new_line;
	}
	else
	{
		*equal = '=';
		lineaddback(arr, new_line);
		free(new_line);
	}
	return (0);
}
