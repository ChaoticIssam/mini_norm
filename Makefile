NAME = Minishell
CC = cc
RM = rm -f
LIBS = -lreadline -L/Users/iszitoun/goinfre/Homebrew/Cellar/readline/8.2.1/lib
CFLAGS = -Wall -Wextra -Werror -I /Users/iszitoun/goinfre/Homebrew/Cellar/readline/8.2.1/include
src = main.c\
		utils.c\
		parssing.c\
		ft_split.c\
		toke_it.c\
		toke_it_utils.c\
		toke_it_utils1.c\
		toke_it_utils2.c\
		parssing_utils.c\
		parssing_utils1.c\
		parssing_utils2.c\
		parssing_utils2_1.c\
		parssing_utils3.c\
		parssing_utils4.c\
		parssing_utils5.c\
		quote_parss_utils.c\
		quote_parss_utils1.c\
		quotes_parssing_utils.c\
		quotes_parssing_utils1.c\
		listes_commandes.c\
		listes_files.c\
		main_utils.c\
		main_utils1.c\
		my_malloc.c\
		my_malloc_utils.c\
		env_parss.c\
		ft_itoa.c\
		error.c\
		./minis/exec.c\
		./minis/pwd.c\
		./minis/export.c\
		./minis/echo.c\
		./minis/cd.c\
		./minis/ft_strdup.c\
		./minis/ft_list.c\
		./minis/unset.c\
		./minis/ft_str_ncmp.c\
		./minis/env.c\
		./minis/multiple_pipe.c\
		./minis/gett_ev.c\
		./minis/exit.c\
		./minis/ft_atoi.c\
		./minis/herdoc_utils.c\
		./minis/multiple_pipe_utils.c\

OBJECTS = ${src:.c=.o}

all	:	$(NAME)

$(NAME):	$(OBJECTS)
	$(CC) $(CFLAGS) ${LIBS} $(OBJECTS) -o $(NAME)
		
clean :
	$(RM) $(OBJECTS)
fclean : clean
	$(RM) $(NAME)
re : fclean all
.PHONY: all clean fclean re
