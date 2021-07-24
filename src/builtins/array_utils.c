#include "../includes/minishell.h"

void	print_array_2x(char **arr)
{
	char	**tmp;

	tmp = arr;
	while (*tmp)
	{
		printf("\t%s\n", *tmp);
		tmp++;
	}
}

char	**copy_arrays_2x(char **src_arr)
{
	int		i;
	char	**tmp_src;
	char	**tmp_dst;
	char	**res_arr;

	i = 0;
	if (!src_arr)
		return (NULL);
	tmp_src = src_arr;
	while (*(tmp_src++))
		i++;
	res_arr = (char **) malloc(sizeof(char *) * i + 1);
	if (!res_arr)
		return (NULL);
	tmp_src = src_arr;
	tmp_dst = res_arr;
	while (*tmp_src)
	{
		*tmp_dst = ft_strdup(*tmp_src);
		tmp_src++;
		tmp_dst++;
	}
	*tmp_dst = NULL;
	return (res_arr);
}

void	clear_arr_2x(char ***arr)
{
	int		i;
	int		size;

	i = 0;
	size = get_arr_2x_len(*arr);
	while (i < size)
		free((*arr)[i++]);
	free(*arr);
}

int	get_arr_2x_len(char **arr)
{
	int		res;

	res = 0;
	while (*arr++)
		res++;
	return (res);
}

/**
** @param src is allocated array for (char *)
** @param addback is line, which add back to src **
** src is reallocated with free old src
** addback is not free
*/

void	lineaddback(char ***src, char *addback)
{
	int		i;
	char	**arr;

	i = 0;
	if (!addback)
		return ;
	while (*(*src + i) != NULL)
		i++;
	arr = (char **)malloc((i += 2) * sizeof(char *));
	arr[--i] = NULL;
	arr[--i] = ft_strdup((const char *)addback);
	while (--i > -1)
		*(arr + i) = *(*src + i);
	free(*src);
	*src = arr;
}
