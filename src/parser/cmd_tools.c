#include "../includes/minishell.h"

t_cmd	*read_cmd(char **line, t_cmd *cmd)
{
	char	*head;
	char	*prev_head;

	head = *line;
	prev_head = head;
	while (*head != '\0' && *head != '|' && *head != '&')
	{
		if (*head == '>' || *head == '<')
			read_redirs(cmd, &prev_head, &head);
		else if (*head)
			add_cmd(cmd, &prev_head, &head);
		else
			head++;
		while (*head == ' ')
			head++;
	}
	check_end(cmd, &head);
	prev_head = *line;
	if (*head)
	{
		*line = ft_strdup(head);
		if (*line)
			free(prev_head);
	}
	return (cmd);
}

void	add_cmd(t_cmd *cmd, char **prev_head, char **head)
{
	char	*n_line;

	next_cmd(head, prev_head, &n_line, cmd);
	while (*prev_head != *head)
	{
		if (**prev_head == '\'' || **prev_head == '\"')
			*prev_head = copy_until_to_end(**prev_head, \
							n_line, (*prev_head + 1));
		else
			append_back(n_line, **prev_head);
		(*prev_head)++;
	}
	lineaddback(&(cmd->command), n_line);
	free(n_line);
}

void	next_cmd(char **head, char **prev_head, char **n_line, t_cmd *cmd)
{
	t_brack	brack;

	brack.single = 0;
	brack.twice = 0;
	while (**head == ' ')
		(*head)++;
	*prev_head = *head;
	while (!(**head == '\0' || (ft_strchr("> <", **head) \
			&& !brack.twice && !brack.single)))
	{
		check_quotes(**head, &brack);
		(*head)++;
	}
	*n_line = ft_calloc((*head - *prev_head + 1), sizeof(char));
	if (!(*n_line))
		cmd->err = 1;
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
		add_tred(&(cmd->reds), ft_substr(*prev_head, 0, \
										 *head - *prev_head), var, cmd);
	else
		add_tred(&(cmd->reds), ft_strdup(*prev_head), var, cmd);
	*prev_head = *head;
}

void	add_tred(t_red ***reds, char *value, int type, t_cmd *cmd)
{
	int		i;
	t_red	**n_red;
	t_red	*one_red;

	one_red = (t_red *)malloc(sizeof(t_red));
	if (!(one_red))
		cmd->err = 1;
	*one_red = (t_red){type, value};
	i = 0;
	while (*(*reds + i) != NULL)
		i++;
	n_red = (t_red **)malloc((i += 2) * sizeof(t_red *));
	if (!n_red)
		cmd->err = 1;
	n_red[--i] = NULL;
	n_red[--i] = one_red;
	while (--i > -1)
		*(n_red + i) = *(*reds + i);
	free(*reds);
	*reds = n_red;
}
