NAME		=	philo
EXC			=	philo

#-------------------SOURCES PATH----------------------

UTILS		=	./utils/
SOURCES		=	./srcs/

#-------------------COMPILATION----------------------

CC			=	gcc
FLAGS		=	-Wall -Werror -Wextra

#-------------------SOURCES FILES----------------------

SRCS		=	$(SOURCES)main.c \
				$(SOURCES)init_struct.c \
				$(SOURCES)error.c \
				$(SOURCES)mutex.c


SRCS_UTILS	=	$(UTILS)ft_atoi.c \
				$(UTILS)ft_isdigit.c \
				$(UTILS)libft_utils.c 

#-------------------OBJECTS----------------------

OBJS		=	$(SRCS:.c=.o)

OBJS_UTILS	=	$(SRCS_UTILS:.c=.o)


#-------------------COLORS----------------------

RED			=	\x1b[31m

YELLOW		=	\x1b[33m

GREEN		=	\x1b[32m

NO_COLOR	=	\x1b[0m


#-------------------RULES-----------------------
%.o: %.c
		@printf "$(YELLOW)Generating philo objects... %-33.33s\r$(NO_COLOR)" $@
		@$(CC) $(FLAGS) -c $< -o $@

$(NAME):	$(OBJS) $(OBJS_UTILS)
			@echo "\n"
			@echo "$(GREEN)\nCompiling philo...$(NO_COLOR)"
			@$(CC) $(FLAGS) $(OBJS) $(OBJS_UTILS) -o $(NAME)
			@echo "\nPhilo ready to be used!"

all:	$(NAME)

bonus:	$(NAME)

clean:
		@echo "$(RED)Deleting objects...\n$(NO_COLOR)"
		@rm -f $(OBJS) $(OBJS_UTILS)

fclean:	clean
		@echo "$(RED)Deleting executables...\n$(NO_COLOR)"
		@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean bonus re

#-------------------TESTS-----------------------

test1 : all
		./$(EXC) 5 800 200 200

test2 : all
		./$(EXC) 4 310 200 100

test3 : all
		./$(EXC) 5 800 200 200 7
