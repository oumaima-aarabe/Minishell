# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: azarda <azarda@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/15 15:19:53 by azarda            #+#    #+#              #
#    Updated: 2023/06/21 22:33:54 by azarda           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

INCLUDE = Minishell.h


CC = cc

READLINE = $(shell brew --prefix readline)

FLAGS = -Wall -Werror -Wextra -I$(READLINE)/include # -g -fsanitize=address



SRC =	obj/ft_error.c\
		obj/split_args.c\
		obj/split_tokens.c\
		obj/parse.c\
		obj/utils1.c\
		obj/utils2.c\
		obj/main.c\
		obj/lexer.c\
		obj/Minishell.c \
		obj/libft_util.c \
		obj/exec.c \
		obj/lst_utils.c \
		obj/builtins.c \
		obj/ft_go_exec.c



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
