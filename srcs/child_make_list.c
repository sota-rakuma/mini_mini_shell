#include "minishell.h"

static int	measure_cmd_len(t_cmd *cmd)
{
	int	cmd_len;

	cmd_len = 0;
	while (cmd != NULL)
	{
		cmd_len++;
		cmd = cmd->next;
	}
	return (cmd_len);
}

char	**make_cmd_list(t_cmd *cmd)
{
	char	**res;
	int		cmd_len;
	int		index;

	cmd_len = measure_cmd_len(cmd);
	res = (char **)malloc(sizeof(char *) * (cmd_len + 1));
	if (res == NULL)
		return (NULL);
	index = 0;
	while (cmd != NULL)
	{
		res[index] = ft_strdup(cmd->str);
		if (res[index] == NULL)
		{
			double_char_free(res);
			return (NULL);
		}
		index++;
		cmd = cmd->next;
	}
	res[index] = NULL;
	return (res);
}

char	**make_path_list(char **env_list)
{
	int		index;
	char	*paths;
	char	**path_list;

	index = 0;
	while (env_list[index] && ft_strncmp(env_list[index], "PATH=", 5) != 0)
		index++;
	if (env_list[index] == NULL)
		return (ft_split(" ", ' '));
	paths = ft_strdup(&env_list[index][5]);
	if (paths == NULL)
		return (NULL);
	path_list = ft_split_path(paths, ':');
	free(paths);
	return (path_list);
}
