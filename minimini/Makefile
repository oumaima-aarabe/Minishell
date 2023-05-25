# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/12 18:21:14 by azarda            #+#    #+#              #
#    Updated: 2023/05/23 00:57:51 by ouaarabe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Minishell

INCLUDE = minishell.h


CC = cc

READLINE = $(shell brew --prefix readline)

FLAGS = -Wall -Werror -Wextra -I$(READLINE)/include




SRC =	minishell.c \
		# obj/libft_util.c \
		# obj/testing.c 


OBJ = $(SRC:.c=.o)

mkdir = mkdir -p

dir = obj


all: $(NAME)

$(NAME): ${dir} $(OBJ)  $(INCLUDE)
	$(CC) $(FLAGS) $(OBJ) -lreadline -o $(NAME)  -L$(READLINE)/lib


%.o : %.c $(INCLUDE)
	$(CC) $(FLAGS) -c $< -o $@

${dir} :
	@${mkdir} ${dir}


clean:
	rm -rf $(OBJ)
fclean:
	rm -rf $(NAME) $(OBJ)

re: fclean all
