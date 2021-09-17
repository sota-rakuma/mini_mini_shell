#include "minishell.h"

static char	*make_file_name(void)
{
	static int	count;
	char		*head_file;
	char		*tmp_num;
	char		*res;

	count++;
	if (count == 10000)
		count = 0;
	head_file = ft_strdup("/tmp/ms_sirjflsslgr_");
	if (head_file == NULL)
		return (NULL);
	tmp_num = ft_itoa(count);
	if (tmp_num == NULL)
	{
		free(head_file);
		return (NULL);
	}
	res = ft_strjoin(head_file, tmp_num);
	free(head_file);
	free(tmp_num);
	return (res);
}

void	add_tmpfile(t_tmp *new)
{
	t_tmp	*tmp;

	if (g_minishell.tmp_file == NULL)
		g_minishell.tmp_file = new;
	else
	{
		tmp = g_minishell.tmp_file;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	save_file_name(char *file_name)
{
	t_tmp	*new;

	new = (t_tmp *)malloc(sizeof(t_tmp) * (1));
	if (new == NULL)
		ft_exit(1);
	new->tmp_file = ft_strdup(file_name);
	if (new->tmp_file == NULL)
		ft_exit(1);
	new->next = NULL;
	add_tmpfile(new);
}

int	set_tmpfile(t_cmd *cmd, t_common_process *c_p)
{
	char	*file_name;
	int		exit_num;

	while (cmd != NULL)
	{
		if (ft_strncmp(cmd->str, "<<", 3) == 0)
		{
			file_name = make_file_name();
			if (file_name == NULL)
			{
				ft_putendl_fd("minishell: tmpfile can't open", 2);
				ft_exit(1);
			}
			cmd->tmp_name = file_name;
			exit_num = heredoc(cmd->next, file_name, c_p->env_list);
			if (exit_num)
				return (1);
			save_file_name(file_name);
		}
		cmd = cmd->next;
	}
	return (0);
}

void	close_tmpfile(void)
{
	t_tmp	*tmp;
	t_tmp	*delete;

	tmp = g_minishell.tmp_file;
	g_minishell.tmp_file = NULL;
	while (tmp != NULL)
	{
		if (tmp->tmp_file != NULL)
		{
			unlink(tmp->tmp_file);
		}
		delete = tmp;
		tmp = tmp->next;
		free(delete->tmp_file);
		free(delete);
	}
}
