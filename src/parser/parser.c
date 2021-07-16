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
	if ((**head == '\"' || **head == '\'') && !flag)
	{
		flag = 1;
		if (**head == '\'' && (*head)++)
			flag = 2;
		*prev_head = *head;
	}
	while (**head != '\0' && **head != '\'' && flag == 2)
		(*head)++;
	while (**head != '\0' && **head != '\"' && flag == 1)
		(*head)++;
	while(**head != '\0' && **head != ' ' && !flag && **head != '<' && **head != '>')
			(*head)++;
}

void	read_redirs(t_cmd *cmd, char **prev_head, char **head)
{
	int		var;

	if (!ft_strncmp(*head, ">>", 2))
		var = GT2;
	else if (!ft_strncmp(*head, ">", 1))
		var = GT;
	else if (!ft_strncmp(*head, "<<", 2))
		var = LOW2;
	else if (!ft_strncmp(*head, "<", 1))
		var = LOW;
	next_head(head, prev_head);
	*(*head)++ = '\0';
	add_tred(&(cmd->reds), ft_strdup(*prev_head), var);
	*prev_head = *head;
}

void 	add_cmd(t_cmd *cmd, char **prev_head, char **head)
{
	next_head(head, prev_head);
	*(*head)++ = '\0';
	lineaddback(&(cmd->command), *prev_head);
	*prev_head = *head;
}
void check_end(t_cmd *cmd, char **head)
{
	if (!ft_strncmp(*head, "||", 2) && (*head += 2))
		cmd->spec = S_OR;
	else if(!ft_strncmp(*head, "&&", 2) && (*head + 2))
		cmd->spec = S_AND;
	else if (**head == '|' && (*head)++)
		cmd->spec = PIPE;
	else if (**head == '\0')
		cmd->spec = 0;
}
t_cmd	read_cmd(char **line)
{
	t_cmd 	cmd;
	char 	*head;
	char 	*prev_head;

	init_cmd(&cmd);
	head = *line;
	prev_head = head;
	while (*head != '\0' && *head != '|' && *head != '&')
	{
		if (*head == '>' || *head == '<')
			read_redirs(&cmd, &prev_head, &head);
		else if (*head == '\'' || *head == '\"' || *head)
			add_cmd(&cmd, &prev_head, &head);
		else
			head++;
		while(*head == ' ')
			head++;
	}
	check_end(&cmd, &head);
	prev_head = *line;
	if (*head && (*line = ft_strdup(head)))
		free(prev_head);
	return cmd;
}

void		unc_envs(char **line, t_all *all)
{
	char	*head;
	char 	*prev_head;
	char 	*n_line;
	int		flag;
	char	*tmp;

	head = *line;
	n_line = NULL;
	while(*head++ != '\0')
	{
		prev_head = head;
		if (*head == '\'' && !flag)
			flag = 1;
		if (*head == '\'' && flag)
			flag = 0;
		if (*head == '$' && !flag)//Если после " ", то $PWD, del ""
		{
			*head++ = '\0';
			tmp = n_line;
			if (ft_strlen(prev_head) && !(n_line = ft_strjoin(n_line, prev_head)))
				n_line = ft_strdup(prev_head);
			free_and_return(&tmp, 1);
			prev_head = head;
			get_dollar(&head, &n_line);//TODO
		}
	}
	if (n_line)
		*line = n_line;
}

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
	*(all->cmd) = cmd;
	if (all->cmd->spec)
		all->is_pipel = 1;
//	if (*(all->cmd->reds))
//		printf("from all	reds 1: %s\n", all->cmd->reds[0]->value);
////	printf("from all	reds type : %d\n", all->cmd->reds[0]->type);
////	printf("from all reds 2: %s\n", all->cmd->reds[1]->value);
////	printf("from all	reds 2 type: %d\n", all->cmd->reds[1]->type);
//	printf("from all command1: %s\n", all->cmd->command[0]);
//	printf("from all command2: %s\n", all->cmd->command[1]);
//	printf("spec: %d\n", all->cmd->spec);
	return all->cmd->spec;
}
