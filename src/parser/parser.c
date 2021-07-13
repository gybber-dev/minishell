#include "../includes/minishell.h"

typedef struct s_flag
{
	int dq;
	int sq;
}				t_flag;


//
//void 	realloc_cmd(t_cmd **cmd)
//{
//	int i;
//
//	i = 0;
//	while (*cmd != NULL)
//	{
//		printf("%s\n", (*cmd)[i].command);
//		i++;
//		}
//	printf("%d\n", i);
//	printf("%p\n", cmd[2]);
//
//
//}
//t_cmd		*get_cmd(char *line, t_all *all)
//{
//	t_cmd	*cmd;
//
//	cmd = (t_cmd *)ft_calloc(sizeof(t_cmd), 2);
//
//}

int 	parser(char **line, t_all *all)
{
	 char *head;
	 char *prev_head;
	 char *n_line;
	 int flag;

	flag = 0;
	head = *line;
	 if (!(*line = ft_strtrim((const char *)(head), " ")))
		 exit(EXIT_FAILURE);
	 free(head);
	 head = *line;
	 prev_head = head;
	 n_line = NULL;
	 while(*head++ != '\0')
	 {
	 	if (*head == '\'' && !flag)
	 		flag = 1;
		if (*head == '\'' && flag)
	 		flag = 0;
	 	if (*head == '$' && !flag)//Если после " ", то $PWD, del ""
 		{
	 		*head++ = '\0';
	 		if (!(n_line = ft_strjoin(n_line, prev_head)))//need free if !Null
	 			n_line = ft_strdup(prev_head);

	 		prev_head = head;
			while (*head++ != '\0')
			{
				if (*head == ' ')
				{
					*head = '\0';
					break;
				}
			}
			n_line = ft_strjoin(n_line, get_value(all->envs, prev_head));//need free if !Null
			prev_head = head;
			prev_head++;
		}
	 }
	if (n_line)
		*line = n_line;
	printf("%s\n", *line);

	return 1;
}
