#include "../includes/minishell.h"

void 	init_cmd(t_cmd **cmd)
{
	(*cmd)->command = (char **)malloc(sizeof(char *));
	(*cmd)->reds = (t_red **)malloc(sizeof(t_red *));
	(*cmd)->reds[0] = NULL;
	(*cmd)->command[0] = NULL;
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
	if (**head == '\"' || **head == '\'')
	{
		flag = 1;
		if (**head == '\'')
			flag = 2;
		(*head)++;
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
	if (**head != '\0' && **head != '<' && **head != '>')
		*(*head)++ = '\0';
	if (**head == '<' || **head == '>')
		add_tred(&(cmd->reds), ft_substr(*prev_head, 0, *head - *prev_head), var);
	else
		add_tred(&(cmd->reds), ft_strdup(*prev_head), var);
	*prev_head = *head;
}

void 	add_cmd(t_cmd *cmd, char **prev_head, char **head)
{
	char *tmp;
	next_head(head, prev_head);
	if (**head != '\0' && **head != '<' && **head != '>')
		*(*head)++ = '\0';
	if (**head == '<' || **head == '>')
	{
		tmp = ft_substr(*prev_head, 0, *head - *prev_head);
		lineaddback(&(cmd->command), tmp);
		free_and_return(&tmp, 1);
	}
	else if (ft_strlen(*prev_head))
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

t_cmd	*read_cmd(char **line)
{
	t_cmd 	*cmd;
	char 	*head;
	char 	*prev_head;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	init_cmd(&cmd);
	head = *line;
	prev_head = head;
	while (*head != '\0' && *head != '|' && *head != '&')
	{
		if (*head == '>' || *head == '<')
			read_redirs(cmd, &prev_head, &head);
		else if (*head == '\'' || *head == '\"' || *head)
			add_cmd(cmd, &prev_head, &head);
		else
			head++;
		while(*head == ' ')
			head++;
	}
	check_end(cmd, &head);
	prev_head = *line;
	if (*head && (*line = ft_strdup(head)))
		free(prev_head);
	return cmd;
}


void		get_dollar(char **head, char **n_line, t_all *all)
{
	char *prev_head;
	char *tmp;

	if (**head == '?' && (*head)++)
	{
		prev_head = *n_line;
		tmp = ft_itoa(all->vlast);
		if(!(*n_line = ft_strjoin(prev_head, tmp)))
			*n_line = ft_strdup(tmp);
		free_and_return(&tmp, 1);
		free_and_return(&prev_head, 1);
	}
	else if (ft_isdigit(**head))
		(*head)++;
	else if (ft_isalpha(**head) || **head == '_')
	{
		prev_head = *head;
		while(ft_isdigit(**head) || ft_isalpha(**head) || **head == '_')
			(*head)++;
		tmp = ft_substr(prev_head, 0, *head - prev_head);
		prev_head = tmp;
		if ((tmp = get_value(all->envs, prev_head)))
		{
			free_and_return(&prev_head, 1);
			prev_head = *n_line;
			if (!(*n_line = ft_strjoin(prev_head, tmp)))
				*n_line = ft_strdup(tmp);
			free_and_return(&prev_head, 1);
		}
	}
}

void 	check_quotes(char head, t_brack *br)
{
	if (head == '\'')
	{
		if (br->single)
			br->single = 0;
		else
			br->single = 1;
	}
	if (head == '\"')
	{
		if (br->twice)
			br->twice = 0;
		else
			br->twice = 1;
	}
}

void		add_tonline(char **n_line, char *prev_head, char **line)
{
	char *tmp;

	tmp = *n_line;
	if (ft_strlen(prev_head) && !(*n_line = ft_strjoin(tmp, prev_head)) ||
		free_and_return(&tmp, 0))
			*n_line = ft_strdup(*line); //скопировать в н_лайн, либо добавить либо проигнорить
}

char		*init_unc_envs(t_brack *br, char **head, char **line, char **prev)
{
	br->single = 0;
	br->twice = 0;
	*head = *line;
	*prev = *head;
	return (NULL);
}
void		with_dolr(char **head, char **n_line, char **prev_head)
{

	char	*tmp;

	*(*head)++ = '$';
	tmp = *n_line;
	*prev_head = ft_substr(*prev_head, 0, *head - *prev_head);
	if (!(*n_line = ft_strjoin(tmp, *prev_head)) || free_and_return(&tmp, 0))
		*n_line = *prev_head;
	else
		free_and_return(prev_head, 1);
}

void		unc_envs(char **line, t_all *all)
{
	char	*head;
	char	*prev_head;
	char	*n_line;
	t_brack	br;

	n_line = init_unc_envs(&br, &head, line, &prev_head);
	while(*head != '\0')
	{
		check_quotes(*head, &br);
		if (*head == '$' && !br.single)
		{
			*head++ = '\0';
			if (*head == '\'' && br.twice && head--)
				with_dolr(&head, &n_line, &prev_head);
			else
				add_tonline(&n_line, prev_head, line);
			get_dollar(&head, &n_line, all);//TODO
			prev_head = head;
		}
		else
			head++;
	}
	if (ft_strlen(prev_head))
		add_tonline(&n_line, prev_head, line);
	if (n_line && free_and_return(line, 1))
		*line = n_line;
}

int 	parser(char **line, t_all *all)
{
	 char *head;

	head = *line;
	 if (!(*line = ft_strtrim((const char *)(head), " ")))
		 exit(EXIT_FAILURE);
	 free(head);
	unc_envs(line, all);
	all->cmd = read_cmd(line);
	if (all->cmd->spec)
		all->is_pipel = 1;
	return all->cmd->spec;
}
