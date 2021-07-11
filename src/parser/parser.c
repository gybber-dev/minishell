#include "../includes/minishell.h"

typedef struct s_flag
{
	int dq;
	int sq;
}				t_flag;


/**
 *
 * @param src is allocated array for (char *)
 * @param addback is line, which add back to src **
 * src is reallocated with free old src
 * addback is not free
 */

void			lineaddback(char ***src,char *addback)
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



char	*get_words(char **line)
{
	/**
	 * return one line
	 */

//	while((*line)[++i] != ' ' && (*line)[i] != '\0')
//		if ((*line)[i] == '\'')
//		{
//			flag = (*line)[i];
//			while ((*line)[i] != '\0' && (*line)[++i] != '\'')
//				;
//		}
//
//	if (flag == '\'')
//	{
//		tmp = sub_line;
//		sub_line = ft_strtrim(sub_line, &flag);
//		free(tmp);
//	}

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
t_cmd		*get_cmd(char *line, t_all *all)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)ft_calloc(sizeof(t_cmd), 2);

}
int 	parser(char **line, t_all *all) {
	/**
	 *1) event = get_one_peace(line, exp)
	 * 2) while (line != '\0' && line != spec)
	 * 			envs[i] = get-one_peace()
	 * 			realloc(envs)
	 * 3) IF LINE == spec
	 * 		specs = line
	 */
	 char *tmp;
	 tmp = ft_strtrim((const char *)(*line), " ");
	printf("%s\n", tmp);
	free(*line);
//	 while(*line != '\0')
//	 {
//
//	 }

	return 1;
}
