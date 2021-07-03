#include "../includes/minishell.h"


/**
** @param envs
** @param key
** @return pointer to value
*/
char			*get_value(char **envs, char *key)
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
			return (*tmp + key_len + 1);
		if (!ft_strncmp(*tmp, key, key_len + 1))
			return (*tmp + key_len);
		tmp++;
	}
	return (NULL);
}


void		print_array_2x(char **arr)
{
	char	*tmp;

	tmp = *arr;
	printf("======================\n");
	while(tmp)
	{
		printf("'%s'\n", tmp);
		tmp++;
	}
	printf(" '%s'\n", tmp);
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