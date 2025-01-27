NAME        = minishell
CC          = cc
CFLAGS      = -Wall -Werror -Wextra 
LDFLAGS     = -lreadline -g3 #-fsanitize=address
RM          = rm -rf

SOURCES     = src/parsing/pars_bin.c src/parsing/pars_cd.c src/parsing/pars_quot.c src/parsing/pars_dolar.c src/parsing/pars_export.c src/parsing/pars_cmd.c src/parsing/pars_syntax.c src/parsing/pars_check.c src/parsing/pars_main.c \
              src/token/token_main.c src/token/token_id.c src/token/token_set.c src/token/token_utils.c src/token/token_pars.c src/token/token_id_utils.c src/token/token_utils_next.c \
              src/executer/exec_main.c src/executer/exec_pipe.c src/executer/exec_multi_pipe.c src/executer/exec_main_path.c src/executer/exec_main_utils.c src/executer/exec_pipe_file.c src/executer/exec_pipe_submain.c src/executer/exec_multi_file.c src/executer/exec_multi_process.c src/executer/exec_multi_step.c \
			  src/builtins/echo.c src/builtins/pwd.c src/builtins/cd.c src/builtins/env.c src/builtins/export.c src/builtins/unset.c src/builtins/in_out.c src/builtins/exit.c \
			  src/env/env_main.c src/env/env_expansion.c src/env/env_utils.c src/env/env_expansion_copy.c src/env/env_expansion_utils.c \
              src/herdoc/herdoc_exec.c src/herdoc/herdoc_expansion.c src/herdoc/herdoc_main.c src/herdoc/herdoc_utils.c \
			  src/signals/signal.c  \
			  src/organizer/cmd_cleaner.c src/organizer/cmd_utils.c \
			  src/micro_lib/ft_split.c src/micro_lib/utils.c src/micro_lib/ft_strjoin.c src/micro_lib/split_basic.c src/micro_lib/get_next_line.c src/micro_lib/get_next_line_utils.c src/micro_lib/put_nbr.c src/micro_lib/ft_itoa.c src/micro_lib/init_struct.c src/micro_lib/utils_next.c src/micro_lib/ft_split_utils.c src/micro_lib/ft_split_quote.c \
              main.c

OBJECTS     = $(SOURCES:%.c=%.o)

%.o: %.c
	@printf "\033[0;30mGenerating minishell objects... %-33.33s\r" $@
	@$ $(CC) $(CFLAGS) -c -g3 $< -o $@

$(NAME): $(OBJECTS)
	@echo "\n"
	@echo "\033[0;32mCompiling minishell..."
	@ $(CC) $(OBJECTS) $(LDFLAGS) -o $(NAME) 
	@echo "\n\033[0;32mDone !"

clean:
	@ $(RM) $(OBJECTS)
	@echo "\033[33;36mClean ✅"

fclean: clean
	@echo "\n\033[33;36mFclean ✅\n"
	@ $(RM) $(NAME)

all: $(NAME)

re: fclean all

.PHONY: all clean fclean re