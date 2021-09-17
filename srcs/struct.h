#ifndef STRUCT_H
# define STRUCT_H

# include <unistd.h>
# include <signal.h>

typedef struct s_cmd
{
	char			*str;
	char			*flag;
	char			is;
	char			list_num;
	int				fd;
	char			*tmp_name;
	struct s_cmd	*prev;
	struct s_cmd	*next;
	struct s_cmd	*m_next;
	struct s_cmd	*top;
}				t_cmd;

typedef struct s_bilst
{
	char			*key;
	char			*var;
	struct s_bilst	*prev;
	struct s_bilst	*next;
}				t_bilst;

typedef t_bilst	t_env;

typedef struct s_common_process
{
	t_cmd			*cmd;
	t_env			*env_list;
	int				in_fd;
	int				out_fd;
	int				process_count;
	pid_t			*id_list;
}				t_common_process;
typedef struct s_tmp
{
	char			*tmp_file;
	struct s_tmp	*next;
}				t_tmp;
typedef struct s_minishell
{
	int						exit_num;
	t_tmp					*tmp_file;
}				t_minishell;

#endif
