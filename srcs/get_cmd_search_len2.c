#include "minishell.h"

void	change_flag_quart(char *str, size_t *str_index, int *flag)
{
	if ((str[*str_index] == '\'') && *flag == 0)
		*flag = 1;
	else if ((str[*str_index] == '\'') && *flag == 1)
		*flag = 0;
	else if ((str[*str_index] == '\"') && *flag == 0)
		*flag = 2;
	else if ((str[*str_index] == '\"') && *flag == 2)
		*flag = 0;
}
