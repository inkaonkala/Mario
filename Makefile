# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/22 15:44:20 by iniska            #+#    #+#              #
#    Updated: 2024/01/22 15:45:13 by iniska           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRC = main.c init_pipes.c exec_command.c clean_n_errors.c arguments.c command_line.c files.c here_dog.c

BONUS_SRC = bonus_main.c init_pipes.c exec_command.c clean_n_errors.c arguments.c command_line.c files.c here_dog.c

OBJ = $(SRC:.c=.o)
BONUS_OBJ = $(BONUS_SRC:.c=.o)

CC = cc
FLAGS = -Wall -Wextra -Werror
LDFLAGS = -L/Users/iniska/Desktop/Code/libft
LDLIBS = -lft

INCLUDES = -I/Users/iniska/Desktop/Code/libft

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) -o $@ $(OBJ) $(LDFLAGS) $(LDLIBS) 

bonus: .bonus

.bonus: $(BONUS_OBJ)
	$(CC) $(FLAGS) -o $(NAME) $(LDFLAGS) $(LDLIBS) $(BONUS_OBJ)
	touch .bonus

%.o: %.c
	$(CC) -c $(FLAGS) $(INCLUDES) $< -o $@

clean:
	rm -f $(OBJ) $(BONUS_OBJ)

fclean: clean
	rm -f $(NAME) .bonus

re: fclean all

.PHONY: all clean flean re bonus



