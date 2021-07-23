#include "../includes/minishell.h"

int	init_cmd(t_cmd **cmd)
{
	g_pid = 0;
	*cmd = (t_cmd *) malloc(sizeof(t_cmd));
	if (!(*cmd))
		return (-1);
	(*cmd)->is_builtin = 0;
	(*cmd)->path = NULL;
	(*cmd)->command = (char **)malloc(sizeof(char *));
	if (!(*cmd)->command)
		return (-1);
	(*cmd)->reds = (t_red **)malloc(sizeof(t_red *));
	if (!(*cmd)->reds)
		return (-1);
	(*cmd)->reds[0] = NULL;
	(*cmd)->command[0] = NULL;
	(*cmd)->err = 0;
	return (0);
}

void	next_head(char **head, char **prev_head)
{
	int		flag;

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
	while (**head != '\0' && **head != ' '
		   && !flag && **head != '<' && **head != '>')
		(*head)++;
}

void	append_back(char *dst, char c)
{
	char	*tmp;

	tmp = dst;
	while (*tmp)
		tmp++;
	*tmp = c;
}

char	*copy_until_to_end(char stop, char *dst, char *src)
{
	while (*dst)
		dst++;
	while (!(*src == '\0' || *src == stop))
	{
		*dst = *src;
		src++;
		dst++;
	}
	return (src);
}

void	check_end(t_cmd *cmd, char **head)
{
	if (!ft_strncmp(*head, "||", 2) && (*head++) && (*head++))
		cmd->spec = S_OR;
	else if (!ft_strncmp(*head, "&&", 2) && (*head++) && (*head++))
		cmd->spec = S_AND;
	else if (**head == '|' && (*head)++)
		cmd->spec = PIPE;
	else if (**head == '\0')
		cmd->spec = 0;
}
