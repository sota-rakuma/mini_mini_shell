#include "minishell.h"

static void	translate_heredoc_find_shell(char **line, char	*tmp, \
			char	*env_key)
{
	char	*nbr_tmp;

	if (env_key[1] == '?')
	{
		nbr_tmp = ft_itoa(g_minishell.exit_num);
		*line = replace_str(tmp, env_key, nbr_tmp, 1);
		free(nbr_tmp);
	}
	else
	{
		*line = replace_str(tmp, env_key, "", 0);
	}
	free(tmp);
}

static int	translate_heredoc_find(char **line, t_env *env_list, \
size_t len, size_t *index)
{
	char	*tmp;
	char	*env_key;
	t_env	*env;

	env_key = ft_substr(*line, *index, len);
	if (env_key == NULL)
		ft_exit(1);
	env = search_key(env_list, env_key + 1);
	tmp = *line;
	if (env == NULL || env->var == NULL)
		translate_heredoc_find_shell(line, tmp, env_key);
	else
	{
		*line = replace_str(tmp, env_key, env->var, 1);
		free(tmp);
		*index += ft_strlen(env->var);
	}
	if (*line == NULL)
		ft_exit(1);
	free(env_key);
	return (0);
}

char	*translate_heredoc(char **line, t_env *env_list)
{
	size_t	index;
	size_t	len;

	index = 0;
	while ((*line)[index])
	{
		if ((*line)[index] == '$')
		{
			len = 1;
			while (is_env_val_ele((*line)[index + len]))
				len++;
			if (len != 1 || ((*line)[index + len] == '?' && ++len))
				translate_heredoc_find(line, env_list, len, &index);
			else
				index++;
		}
		else
			index++;
	}
	return (*line);
}
