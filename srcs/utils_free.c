#include "minishell.h"

void	*ft_free_pointer(void *ptr1, void *ptr2, void *ptr3, void *ptr4)
{
	if (ptr1)
		free(ptr1);
	if (ptr2)
		free(ptr2);
	if (ptr3)
		free(ptr3);
	if (ptr4)
		free(ptr4);
	return (NULL);
}

void	*double_char_free(char **list)
{
	int	i;

	i = 0;
	if (list == NULL)
		return (NULL);
	while (list[i] != NULL)
	{
		free(list[i]);
		i++;
	}
	free(list);
	return (NULL);
}

void	double_char_free_4(char **ptr1, char **ptr2, char **ptr3, char **ptr4)
{
	if (ptr1 != NULL)
		double_char_free(ptr1);
	if (ptr2 != NULL)
		double_char_free(ptr2);
	if (ptr3 != NULL)
		double_char_free(ptr3);
	if (ptr4 != NULL)
		double_char_free(ptr4);
}

void	free_common_process(t_common_process *c_p)
{
	free_list_cmd(c_p->cmd);
	ft_free_all_bidir_lst(c_p->env_list);
	free(c_p->id_list);
}

// if flag is true, elements free from last element.
void	ft_port_free_cmd(t_cmd *first, t_cmd *last, int flag)
{
	t_cmd	*tmp;

	if (flag)
	{
		while (last != first)
		{
			tmp = last->prev;
			ft_free_pointer(last->str, last->flag, last, NULL);
			last = tmp;
		}
		return ;
	}
	while (first != last)
	{
		tmp = first->next;
		ft_free_pointer(first->str, first->flag, first, NULL);
		first = tmp;
	}
}
