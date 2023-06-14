# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: azarda <azarda@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/12 18:21:14 by azarda            #+#    #+#              #
#    Updated: 2023/06/09 17:14:50 by azarda           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Minishell

INCLUDE = Minishell.h


CC = cc

READLINE = $(shell brew --prefix readline)

FLAGS = -Wall -Werror -Wextra -I$(READLINE)/include #-fsanitize=address




SRC =	obj/Minishell.c \
		obj/libft_util.c \
		obj/exec.c \
		obj/lst_utils.c \
		obj/builtins.c


OBJ = $(SRC:.c=.o)

mkdir = mkdir -p

dir = obj


all: $(NAME)

$(NAME): ${dir} $(OBJ)  $(INCLUDE)
	$(CC) $(FLAGS) $(OBJ) -lreadline -o $(NAME) -L$(READLINE)/lib


obj/%.o : %.c $(INCLUDE)
	$(CC) $(FLAGS) -c $< -o $@

${dir} :
	@${mkdir} ${dir}


clean:
	rm -rf obj
fclean:
	rm -rf $(NAME) obj

re: fclean all
