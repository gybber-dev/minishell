#include "../includes/minishell.h"

typedef struct s_flag
{
	int dq;
	int sq;
}				t_flag;



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

int 	parser(char **line, t_all *all)
{
	 char *tmp;
	 char *tmp2;
	 int i;
	 int flag;

	 i = -1;
	flag = 0;
	 tmp = *line;
	 if (!(*line = ft_strtrim((const char *)(tmp), " ")))
		 exit(EXIT_FAILURE);
	 free(tmp);
	 tmp = NULL;
	 while((*line)[++i] != '\0')
	 {
	 	if ((*line)[i] == '\'' && !flag)
	 		flag = 1;
		if ((*line)[i] == '\'' && flag)
	 		flag = 0;
	 	if ((*line)[i] == '$' && !flag)
		{
	 		//дописать тут, проблема с i
			(*line)[i] = '\0';
	 		tmp = ft_strjoin(tmp, *line);
	 		i++;
			while ((*line)[i] != '\0')
			{
				if ((*line)[i] == ' ')
					(*line)[i++] = '\0';

			}

		}
	 }

	return 1;
}
