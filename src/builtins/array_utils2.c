#include "../includes/minishell.h"

static void	service_iterator(char ***tmp_src, char ***tmp_arr,
								char ***found_line)
{
	if (**tmp_src != **found_line)
		**tmp_arr = ft_strdup(**tmp_src);
	else
		(*tmp_arr)--;
	(*tmp_src)++;
	(*tmp_arr)++;
}

int	del_line_arr_2x(char *line, char ***src)
{
	int		size;
	char	**arr;
	char	**found_line;
	char	**tmp_src;
	char	**tmp_arr;

	found_line = check_key(*src, line);
	if (!found_line)
		return (EXIT_SUCCESS);
	size = get_arr_2x_len(*src);
	arr = (char **)malloc(size * sizeof(char *));
	if (!arr)
		return (EXIT_FAILURE);
	tmp_src = *src;
	tmp_arr = arr;
	while (*tmp_src)
		service_iterator(&tmp_src, &tmp_arr, &found_line);
	*tmp_arr = NULL;
	clear_arr_2x(src);
	*src = arr;
	return (EXIT_SUCCESS);
}
