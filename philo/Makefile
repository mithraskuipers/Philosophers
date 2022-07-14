# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mikuiper <mikuiper@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/06/03 17:36:28 by mikuiper      #+#    #+#                  #
#    Updated: 2022/07/13 15:40:21 by mikuiper      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME		= philo
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
CFLAGS_DBG	= -g3 -fsanitize=address
LIBRARIES	= -lpthread

INCS	=	-I./inc

SRC_DIR		= ./src/

SRCS		=	$(SRC_DIR)main.c \
				$(SRC_DIR)time.c \
				$(SRC_DIR)libft.c \
				$(SRC_DIR)init.c \
				$(SRC_DIR)tools.c \
				$(SRC_DIR)parse_input.c \
				$(SRC_DIR)tasks.c \
				$(SRC_DIR)printer.c \
				$(SRC_DIR)threads.c

OBJS		= $(SRCS:.c=.o)

GREEN = \033[92m
NOCOLOR = \033[0;38m

all: $(NAME)

$(NAME): $(OBJS)
	@echo "\n$(GREEN)[philo] - Compiling $(NAME)..$(NOCOLOR)"
	@$(CC) $(CFLAGS) $(INCS) -o $(NAME) $(OBJS) $(LIBRARIES) 

dbg: fclean all
	@echo "\n$(GREEN)[philo] - Compiling $(NAME)..$(NOCOLOR)"
	@$(CC) $(CFLAGS_DBG) $(INCS) -o $(NAME) $(OBJS)

.c.o:
	@$(CC) $(CFLAGS) $(INCS) -c -o $@ $<

clean:
	@echo "$(GREEN)[philo] - Running clean..$(NOCOLOR)"
	@echo "$(GREEN)[philo] - Removing object files..$(NOCOLOR)"
	@$(RM) $(OBJS)
	@echo "$(GREEN)[philo] - Finished running clean!$(NOCOLOR)"

fclean:
	@echo "$(GREEN)[philo] - Running fclean..$(NOCOLOR)"
	@echo "$(GREEN)[philo] - Removing object files..$(NOCOLOR)"
	@echo "$(GREEN)[philo] - Finished running fclean!$(NOCOLOR)"
	@$(RM) $(OBJS)
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re