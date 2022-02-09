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
				$(SOURCES)error.c \
				$(SOURCES)init_struct.c \
				$(SOURCES)mutex.c \
				$(SOURCES)dead.c \
				$(SOURCES)routine_philo.c


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

test_one_philo: all
		./$(NAME) 1 800 200 200

# Test 1: no one should die
test1:	all
		./$(NAME) 5 800 200 200

# Test 2: no one should die and the philosophers each eats 7 times
test2:	all
		./$(NAME) 5 800 200 200 7

test2_count:
		make test2 | grep eating | wc -l

# Test 3: no one should die
test3:	all
		./$(NAME) 4 410 200 200

# Test 4: A philosopher should die
test4:	all
		./$(NAME) 4 310 200 100

test5:	all
		./$(NAME) 50 410 200 200

test6:	all
		./$(NAME) 200 410 200 200

test_min: all
		./$(NAME) 2 130 60 60

test_min_d: all
		./$(NAME) 2 120 60 60

test_max: all
		./$(NAME) 200 800 200 200

test_max_d: all
		./$(NAME) 200 310 200 100
