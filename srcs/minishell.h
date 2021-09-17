#ifndef MINISHELL_H
# define MINISHELL_H

# define ERROR 1
# define SUCCESS 1

# include "struct.h"
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include "libft.h"

t_minishell	g_minishell;

int			ft_isspace(int c);
char		*ft_lltoa(long long num);
long long	ft_atoll(const char *str);
char		*ft_strncpy(char *dest, char *src, unsigned int n);

size_t		get_cmd_search_len(char *str, size_t *str_index);
void		*ft_free_pointer(void *ptr1, void *ptr2, void *ptr3, void *ptr4);
void		ft_port_free_cmd(t_cmd *first, t_cmd *last, int flag);
void		ft_free_cmd(t_cmd *cmd);
void		*double_char_free(char **list);
char		**double_char_dup(char **envp);
void		ft_put_2array_cmd(t_cmd *array);
int			set_parse_cmd(t_cmd **res, char *str);
t_cmd		*parse_cmd(char **str);
t_cmd		*ft_substr_cmd(char *str, size_t start, size_t len);
void		free_list_cmd(t_cmd *cmd);
char		*translate_heredoc(char **line, t_env *env_list);
int			heredoc(t_cmd *here, char *file_name, t_env *env_list);

void		free_list_cmd_one(t_cmd *cmd);
void		put_error_str(char *cmd, char *message, int flag);
int			validate_cmd(t_cmd *cmd);

void		heredoc_sig_handler(int sig);
int			proc_child_stop_by_sig(int sig);
void		shell_sig_handler(int sig);
int			sig_error(int num);

int			set_key_value(char *str, char **key, char **value);
t_env		*set_envlist(char **envp);
t_bilst		*search_key(t_bilst *env_list, const char *str);

t_env		*ft_get_new_env(void);
char		*ft_get_shlvl(int level);
int			ft_incliment_shlvl(t_env **env_list);
t_env		*ft_init_env(char **envp);

void		*ft_free_pointer(void *ptr1, void *ptr2, void *ptr3, void *ptr4);
void		*double_char_free(char **list);
void		ft_free_all_bidir_lst(t_bilst *env_lst);
void		ft_port_free_cmd(t_cmd *first, t_cmd *last, int flag);
char		**double_char_dup(char **envp);
int			is_env_val_ele(int c);
t_bilst		*ft_bidir_lst_new(char *key, char *value);
t_bilst		*ft_bidir_lst_last(t_bilst *env_list);
void		ft_bidir_lst_add_back(t_bilst **bidir_list, char *key, \
				char *value);
size_t		ft_vallen(char *dollar_ptr);
int			ft_check_enval(char *key);
size_t		ft_bidir_lst_size(t_bilst *bilist);
t_cmd		*ft_cmd_first(t_cmd *last);
t_cmd		*ft_cmd_last(t_cmd *cmd);
char		*replace_str(char *old_str, char *old, char *new, int times);
char		*ft_get_key_in_str(t_cmd *target, char *dollar_ptr);
void		add_cmd(t_cmd **res, t_cmd *new);

char		*get_expnaded_str(char *old_str, char *new, char *old, \
				size_t index);
void		ft_change_flag(t_cmd *target, size_t old_len, size_t new_len, \
				size_t index);
void		ft_interpret_dq_sq(t_cmd *target);
void		dollar_expansion(t_cmd *target, size_t dindex, char *dptr, \
				t_env *env_list);
void		translate_string(t_cmd **cmd, t_env *env_list);

void		rewrite_envlist(t_env *env_list, char *key, char *var);
char		*ft_set_pwd(char *dir, int flag);
int			ft_get_curpath(t_env *env_list, char *dir_ope, char buff[]);
void		ft_get_canonical_form(char buff[]);
int			cd_cmd(t_env **env_list, t_cmd *cmd);
int			echo_cmd(t_cmd *cmd);
int			env_cmd(t_env *env_list);
int			exit_cmd(t_env *env_list, t_cmd *cmd);
int			export_cmd(t_env *env_list, t_cmd *cmd);
int			pwd_cmd(t_env *env_list);
void		ft_exit(int	exit_num);
void		close_tmpfile(void);
int			check_build_in(t_cmd *cmd);
int			check_redirect_1(t_cmd **cmd);
int			check_redirect(t_cmd **cmd);
char		*search_path_exec(char **cmd_list, char **path_list, \
char **env_list);
char		**make_cmd_list(t_cmd *cmd);
char		**make_path_list(char **env_list);
int			set_fd(int	in_fd, int out_fd);
void		exec_cmd_child(t_cmd *cmd, t_env *env_list, int in_fd, int out_fd);
int			exec_cmd_no_pipe(t_common_process *common_process);
int			exec_cmd_pipe(t_common_process *common_process, int pipe_count);
void		make_id_list(t_common_process *common_process, int pipe_count);
int			exec_cmd(t_cmd *cmd, t_env **env_list);
int			inequality_r1(t_cmd *cmd);
int			inequality_r2(t_cmd *cmd);
int			inequality_l1(t_cmd *cmd);
int			inequality_l2(t_cmd *cmd);
void		delete_list_two(t_cmd **cmd);
void		delete_list_two_next(t_cmd *cmd);
t_cmd		*make_pipe_cmd(t_cmd **cmd);
int			count_pipe(t_cmd *cmd);
int			first_pipe(t_common_process *c_p);
int			middle_pipe(t_common_process *c_p, int where_flag);
int			last_pipe(t_common_process *c_p);
int			set_tmpfile(t_cmd *cmd, t_common_process *c_p);
void		close_tmpfile(void);
void		free_common_process(t_common_process *c_p);
void		double_char_free_4(char **ptr1, char **ptr2, \
				char **ptr3, char **ptr4);
char		*ft_strjoin_3(char *str1, char *str2, char *str3);
int			print_error_return(char *str);
int			print_error_strings(char *message_1, char *message_2, \
				char *message_3);
int			str_is_space_only(char *str, size_t str_index);
int			unset_cmd(t_env **env_list, t_cmd *cmd);
int			search_cmd(t_env **env_list, t_cmd *cmd);
void		change_flag_quart(char *str, size_t *str_index, int *flag);
char		**ft_split_path(const char *str, char character);

#endif
