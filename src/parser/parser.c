#include "../includes/minishell.h"

void	init_all(t_all *all)
{
	all->command = (char **)malloc(sizeof(char *));
	all->envs = (char **)malloc(sizeof(char *));
	all->specs = ft_calloc(1, sizeof(char));
	(all->command)[0]= NULL;
	(all->command)[1]= NULL;
	(all->envs)[0]= NULL;

}

char			**ft_get_one_command(char **line,char ***src)
{
	/**
	 * return allocated new arr
	 */
	int		i;
	char	**arr;
	char	*sub_line;
	int		n;
	int 	flag;

	i = 0;
	n = -1;
	flag = 0;
	while(*(*src + i) != NULL)
		i++;
	arr = (char **)malloc(i + 2 * sizeof(char));
	while (++n < i)
		*(arr + n) = *(*src + n);
	i = -1;


	while((*line)[++i] != ' ')
		if ((*line)[i] == '\'')
		{
			//flag_1();
			if (flag == 0)
				flag = 1;
			while (flag > 0 && (*line)[i] != '\0' && (*line)[++i] != '\'')
				;
		}

	sub_line = ft_calloc(i + 1, sizeof(char));
	ft_strlcpy(sub_line, (const char*)(*line), i);
	arr[n++] = sub_line;
	arr[n] = NULL;
	free(*src);

	return arr;
}

void			parser(char *line, t_all *all)
{
	/**
	 *1) event = get_one_peace(line, exp)
	 * 2) while (line != '\0' && line != spec)
	 * 			envs[i] = get-one_peace()
	 * 			realloc(envs)
	 * 3) IF LINE == spec
	 * 		specs = line
	 */


	int i;

	i = -1;
	line = ft_strtrim(line, " ");
//parse bin
// parse args
		all->command = ft_get_one_command(&line, &(all->command));
}
