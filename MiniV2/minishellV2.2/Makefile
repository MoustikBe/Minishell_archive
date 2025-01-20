NAME		= minishell
CC			= cc
CFLAGS		= -lreadline -c
RM			= rm -rf

SOURCES		= main parsing/checker/main_check
		 	  

OBJECTS     = $(SOURCES:%.c=%.o)

%.o: %.c
	$(CC) $< -o $@

$(NAME): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(NAME)
	@echo "\033[33;32mCompilation finish with no problem ✅"

clean:
	$(RM) $(OBJECTS)

fclean: clean
	$(RM) $(NAME)
	@echo "\033[33;36mAll the file his delete correctly ✅"

all : $(NAME)

re: fclean all

.PHONY: all clean fclean re

.SILENT:
