#include "../includes/minishell.h"

void		bubble_sort_arr_2x(char **arr)
{
	int		i;
	int		j;
	char	*temp;
	int		count;

	count = get_arr_2x_len(arr);
	i = 0;
	while (arr[i] != NULL)
	{
		j = count - 1;
		while (j > i)
		{
			if (ft_strncmp(arr[j - 1], arr[j], (ft_strlen(arr[0]) + 1)) > 0)
			{
				temp = arr[j - 1];
				arr[j - 1] = arr[j];
				arr[j] = temp;
			}
			j--;
		}
		i++;
	}
}


void		sort_env(char **env)
{
	char	**tmp;
	char	**tmp_backup;
	int		i;

	tmp = copy_arrays_2x(env);
	tmp_backup = tmp;
	bubble_sort_arr_2x(tmp);
	while (*tmp)
	{
		write(1, "declare -x ", 11);
		i = 0;
		while(1)
		{
			write(1, &(*tmp)[i], 1);
			i++;
			if ((*tmp)[i] == 0 || (*tmp)[i] == '=')
				break ;
		}
		write(1, &(*tmp)[i++], 1);
		write(1, "\"", 1);
		while((*tmp)[i]) {
			write(1, &(*tmp)[i++], 1);
		}
		write(1, "\"\n", 2);
		tmp++;
	}
	clear_arr_2x(tmp_backup);
}

/**
**
** @param command 'PWD=<path>'
** @return 	0:	if there is no '=' symbol
** 				if first is not alpha
*/

int			check_var_name(char *command)
{
	if (!command)
		return 0;
	if (!ft_strchr(command, '='))
		return 0;
	if (!(ft_isalpha(*command) || *command == '_'))
		return 0;
	command++;
	while(*command != '=')
	{
		if (!(ft_isalnum(*command) || *command == '_'))
			return 0;
		command++;
	}
	return 1;
}

int			check_string(char **command)
{
	char	*new_line;
	char	*equal;
	char	*tmp;

	new_line = *command;
	if (!(equal = ft_strchr(new_line, '=')))
		return 0;
	if (*(equal + 1) == '\0')
	{
		if (!(tmp = ft_strjoin(new_line, "\"\"")))
			return 0;
		free(*command);
		*command = tmp;
	}
	return 1;
}

int 		ft_export(char **command, char ***env)
{
	int		i;

	if (*(command + 1) == NULL)
		sort_env(*env);
	else
	{
		command++;
		i = 0;
		while (command[i])
		{
			if (!check_var_name(*command))
				return 0;
//				exit(EXIT_FAILURE);
			if (!check_string(&command[i]))
				return 0;
//				exit(EXIT_FAILURE);
			else
				set_value_arr_2x(command[i], env);
			i++;
		}
	}
	return 1;
}