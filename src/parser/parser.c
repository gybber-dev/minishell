#include "../includes/minishell.h"


void 	init_cmd(t_cmd *cmd)
{
	cmd->command = (char **)malloc(sizeof(char *));
	cmd->reds = (t_red **)malloc(sizeof(t_red *));
	cmd->reds[0] = NULL;
	cmd->command[0] = NULL;
}

void 	add_tred(t_red ***reds, char *value, int type)
{
	int i;
	t_red	**n_red;
	t_red	*one_red;

	one_red = (t_red *)malloc(sizeof(t_red));
	*one_red = (t_red){type, value};
	i = 0;
	while (*(*reds + i) != NULL)
		i++;
	n_red = (t_red **)malloc((i += 2) * sizeof(t_red *));
	n_red[--i] = NULL;
	n_red[--i] = one_red;
	while(--i > -1)
		*(n_red + i) = *(*reds + i);
	free(*reds);
	*reds = n_red;
}

void	next_head(char **head, char **prev_head)
{
	int flag;

	flag = 0;

	while (**head != '\0' && (**head == ' ' || **head == '>' || **head == '<'))
		(*head)++;
	*prev_head = *head;
	while ((**head != ' ' || flag) && **head != '\0')
	{
		if (**head == '\'' && !flag)
			flag = 1;
		else if (**head == '\"' && !flag)
			flag = 2;
		else if (**head == '\'' && flag == 1)
			flag = 0;
		else if (**head == '\"' && flag == 2)
			flag = 0;
		(*head)++;
	}
}
void 	add_cmd(char ***command, char *value)
{

}
t_cmd	read_cmd(char **line)
{
	t_cmd 	cmd;
	int		flag;
	char 	*head;
	char 	*prev_head;
	char 	*tmp;


	init_cmd(&cmd);
	head = *line;
	flag = 0;
	prev_head = head;
	while (*head != '\0' && *head != '|' && ft_strncmp(head, "||", 2) && ft_strncmp(head, "&&", 2))
	{
		if ((*head == '\'' || *head == '\"') && !flag)
			flag = 1;
		else if ((*head == '\'' || *head == '\"') && flag)
			flag = 0;
		else if (!ft_strncmp(head, ">>", 2) && !flag)
		{
			next_head(&head, &prev_head);
			*head = '\0';
			head++;
			add_tred(&(cmd.reds), ft_strtrim(prev_head, " "), GT2);
			prev_head = head;
		}
		else if (!ft_strncmp(head, ">", 1) && !flag)
		{
			next_head(&head, &prev_head);
			*head = '\0';
			head++;
			add_tred(&(cmd.reds), ft_strtrim(prev_head, " "), GT);
			prev_head = head;
		}
		else if (*head == ' ')
		{
			*head = '\0';
			head++;
			tmp = ft_strtrim(prev_head, " ");
			lineaddback(&(cmd.command), tmp);
			free(tmp);
			prev_head = head;
		}
		else
			head++;
	}
	return cmd;
}

char 	*read_redirs();

int 	parser(char **line, t_all *all)
{
	 char *head;
	 char *prev_head;
	 char *n_line;
	 int flag;
	 t_cmd cmd;

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
	 		//-------------------------------------------------------------------
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
			//-------------------------------------------------------------------
		}
	 }
	if (n_line)
		*line = n_line;
	cmd = read_cmd(line);
	all->cmd = &cmd;
//	printf("%s\n", cmd.command[0]);
	return 1;
}
