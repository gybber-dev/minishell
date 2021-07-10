#include "../includes/minishell.h"



char			**ft_get_one_command(char **line,char ***src)
{
	/**
	 * return allocated new arr
	 */
	int		i;
	char	**arr;
	char	*sub_line;
	int		n;
	char 	flag;
	char 	*tmp;

	i = 0;
	n = -1;
	flag = 0;
	while(*(*src + i) != NULL)
		i++;
	arr = (char **)malloc(i + 2 * sizeof(char));
	while (++n < i)
		*(arr + n) = *(*src + n);
	i = -1;


	while((*line)[++i] != ' ' && (*line)[i] != '\0')
		if ((*line)[i] == '\'')
		{
			flag = (*line)[i];
			while ((*line)[i] != '\0' && (*line)[++i] != '\'')
				;
		}

	sub_line = ft_calloc(i++, sizeof(char));
	ft_strlcpy(sub_line, (const char*)(*line), i);
	if (flag == '\'')
	{
		tmp = sub_line;
		sub_line = ft_strtrim(sub_line, &flag);
		free(tmp);
	}
	arr[n++] = sub_line;
	arr[n] = NULL;
	free(*src);

	return arr;
}

void 	realloc_cmd(t_cmd **cmd)
{
	int i;

	i = 0;
	while (*cmd != NULL)
	{
		printf("%s\n", (*cmd)[i].command);
		i++;
		}
	printf("%d\n", i);
	printf("%p\n", cmd[2]);


}

int 	parser(char *line, t_all *all) {
	/**
	 *1) event = get_one_peace(line, exp)
	 * 2) while (line != '\0' && line != spec)
	 * 			envs[i] = get-one_peace()
	 * 			realloc(envs)
	 * 3) IF LINE == spec
	 * 		specs = line
	 */


	int		i;
	char	*tmp;
	int		ret;
	t_cmd	*cmd;

	t_cmd q;

	i = -1;
	cmd = (t_cmd *)malloc(sizeof(t_cmd) * 3);
	cmd[0].command = ft_strdup("sdf");
	cmd[1].command = ft_strdup("hi");



//	while (*line != '\0')
		realloc_cmd(&cmd);
//	tmp = line;
//	line = ft_strtrim(line, " ");
	//free(tmp);Not work!!!!!!!!!!!!!!!!!!!
//parse bin
// parse args
//	all->command = ft_get_one_command(&line, &(all->command));
	return 1;
}
