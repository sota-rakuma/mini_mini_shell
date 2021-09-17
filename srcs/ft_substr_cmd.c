#include "minishell.h"

static int	check_flag(char *str, size_t start, size_t index, size_t flag)
{
	if (str[start + index] == '\'' && flag == 1)
		flag = 2;
	else if (str[start + index] == '\'' && flag == 2)
		flag = 1;
	else if (str[start + index] == '\"' && flag == 1)
		flag = 3;
	else if (str[start + index] == '\"' && flag == 3)
		flag = 1;
	return (flag);
}

static void	search_cmd_len(t_cmd *cmd, char *str, size_t start, size_t len)
{
	size_t		index;
	int			flag;

	index = 0;
	flag = 1;
	while (index != len)
	{
		(cmd->str)[index] = str[start + index];
		flag = check_flag(str, start, index, flag);
		(cmd->flag)[index] = flag + '0';
		index++;
	}
	(cmd->str)[index] = '\0';
	(cmd->flag)[index] = '\0';
}

t_cmd	*ft_substr_cmd(char *str, size_t start, size_t len)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd) * 1);
	if (cmd == NULL)
		ft_exit(1);
	cmd->str = (char *)malloc(sizeof(char) * (len + 1));
	cmd->flag = (char *)malloc(sizeof(char) * (len + 1));
	if (cmd->str == NULL || cmd->flag == NULL)
		ft_exit(1);
	cmd->next = NULL;
	cmd->m_next = NULL;
	cmd->prev = NULL;
	search_cmd_len(cmd, str, start, len);
	cmd->tmp_name = NULL;
	return (cmd);
}
