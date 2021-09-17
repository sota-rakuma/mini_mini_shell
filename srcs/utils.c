#include "minishell.h"

char	**double_char_dup(char **envp)
{
	char	**res;
	int		i;

	i = 0;
	while (envp[i] != NULL)
		i++;
	res = (char **)malloc(sizeof(char *) * (i + 1));
	if (res == NULL)
		return (NULL);
	i = 0;
	while (envp[i] != NULL)
	{
		res[i] = ft_strdup(envp[i]);
		if (res[i] == NULL)
			return (double_char_free(res));
		i++;
	}
	res[i] = NULL;
	return (res);
}

void	ft_put_2array_cmd(t_cmd *array)
{
	int	index2;

	if (array == NULL)
		write(2, "NULL\n", 4);
	while (array != NULL)
	{
		write(2, "-", 1);
		ft_putstr_fd(array->str, 2);
		write(2, "-\n", 2);
		index2 = 0;
		write(2, "-", 1);
		while (array->str[index2] != '\0')
			ft_putchar_fd(array->flag[index2++], 2);
		write(2, "-\n", 2);
		array = array->next;
	}
}

void	ft_free_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (cmd)
	{
		tmp = cmd->next;
		free(cmd);
		cmd = tmp;
	}
}

char	*ft_strjoin_3(char *str1, char *str2, char *str3)
{
	char	*tmp_cmd1;
	char	*tmp_cmd2;

	tmp_cmd1 = ft_strjoin(str1, str2);
	if (tmp_cmd1 == NULL)
		return (NULL);
	tmp_cmd2 = ft_strjoin(tmp_cmd1, str3);
	free(tmp_cmd1);
	if (tmp_cmd2 == NULL)
		return (NULL);
	return (tmp_cmd2);
}

int	print_error_return(char *str)
{
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	return (1);
}
