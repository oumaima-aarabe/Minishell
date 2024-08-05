# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: azarda <azarda@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/15 15:19:53 by azarda            #+#    #+#              #
#    Updated: 2023/07/19 05:35:50 by azarda           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

INCLUDE = src/Minishell.h


CC = cc

READLINE = $(shell brew --prefix readline)

FLAGS = -Wall -Werror -Wextra  -I$(READLINE)/include

SRC =	src/*.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)  $(INCLUDE)
	$(CC) $(FLAGS) $(OBJ) -lreadline -o $(NAME) -L$(READLINE)/lib


obj/%.o : %.c $(INCLUDE)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -rf ${OBJ}
fclean:
	rm -rf $(NAME) ${OBJ}

re: fclean all
