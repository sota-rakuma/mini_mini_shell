SRCS_DIR=srcs

SRCS_FILES=\
build_in.c \
builtin_2.c \
builtin_cd.c \
builtin_exit.c \
builtin_export.c \
cd_canonicalisation.c \
cd_get_curpath.c \
child.c \
child_check_redirect.c \
child_exec.c \
child_make_list.c \
env_builtin.c \
exec_cmd.c \
exec_cmd_pipe.c \
ft_isspace.c \
ft_lltoatoll.c \
ft_strncpy.c \
ft_substr_cmd.c \
general_builtin.c \
general_expansion.c \
get_cmd_search_len.c \
get_cmd_search_len2.c \
heredoc_find.c \
heredoc.c \
inequality.c \
init_env.c \
interpret_dollar_quotation.c \
main.c \
parse_cmd.c \
pipe.c \
pipe_utils.c \
proc_env.c \
set_parse_cmd.c \
signal_handler.c \
srakuma_cmd_utils.c \
srakuma_env_utils.c \
srakuma_utils_1.c \
tmp_file.c \
utils.c \
utils2.c \
utils_free.c \
validate_cmd.c \
ft_split_path.c \
var_expansion.c
#malloc_test.c

SRCS=$(addprefix ${SRCS_DIR}/,${SRCS_FILES})

OBJS_DIR:=objs

OBJS=$(addprefix $(OBJS_DIR)/,$(SRCS_FILES:.c=.o))

NAME=minishell

HEADER_FILES = ft_struct.h

CFLAGS := -Wall -Wextra -Werror -g -fsanitize=address

LIB:= -Llibft -lft

ifeq ($(shell uname), Darwin)
	CFLAGS += -I$(shell brew --prefix readline)/include
	LIB += -L$(shell brew --prefix readline)/lib -lreadline
else
	LIB += -lreadline
endif

-include $(DEPS)

all: $(NAME)

$(NAME): libft/libft.a $(OBJS_DIR) $(OBJS)
	gcc ${CFLAGS} -o $(NAME) $(OBJS) $(LIB)
	@echo "set echo-control-characters off" > ~/.inputrc

libft/libft.a:
	$(MAKE) -C ./libft

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	gcc ${CFLAGS} -Ilibft -c -o $@ $<
#gcc ${CFLAGS} -c $< -o ${<:.c=.o} -Ilibft

clean:
	rm -fR $(OBJS_DIR)
	$(MAKE) -C ./libft clean

fclean: clean
	rm -f ${NAME} ~/.inputrc
	$(MAKE) -C ./libft fclean

re:	fclean all

.PHONY: all clean fclean re
