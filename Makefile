# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: azarda <azarda@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/12 18:21:14 by azarda            #+#    #+#              #
#    Updated: 2023/05/16 21:44:05 by azarda           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Minishell

INCLUDE = Minishell.h


CC = cc

READLINE = $(shell brew --prefix readline)

FLAGS = -Wall -Werror -Wextra -I$(READLINE)/include

# FLAGS = -Wall -Wextra -Werror -g
# -fsanitize=address


SRC =	obj/Minishell.c \
		obj/libft_util.c


OBJ = $(SRC:.c=.o)

mkdir = mkdir -p

dir = obj


all: $(NAME)

$(NAME): ${dir} $(OBJ)  $(INCLUDE)
	$(CC) $(FLAGS) $(OBJ) -lreadline -L$(READLINE)/lib -o $(NAME)


obj/%.o : %.c $(INCLUDE)
	$(CC) $(FLAGS) -c $< -o $@

${dir} :
	@${mkdir} ${dir}


clean:
	rm -rf obj
fclean:
	rm -rf $(NAME) obj

re: fclean all
