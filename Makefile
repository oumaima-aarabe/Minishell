# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: azarda <azarda@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/12 18:21:14 by azarda            #+#    #+#              #
#    Updated: 2023/05/12 18:22:05 by azarda           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



INCLUDE = Minishell.h


CC = cc


FLAGS = -Wall -Wextra -Werror -g
# -fsanitize=address


SRC =	obj/Minishell.c
		
OBJ = $(SRC:.c=.o)

mkdir = mkdir -p

dir = obj

all: $(NAME)

$(NAME): ${dir} $(OBJ)  $(INCLUDE)
	$(CC) $(FLAGS) $(OBJ) -lreadline -o $(NAME) 


obj/%.o : %.c $(INCLUDE)
	$(CC) $(FLAGS) -c $< -o $@

${dir} : 
	@${mkdir} ${dir}


clean:
	rm -rf obj
fclean:
	rm -rf $(NAME) obj

re: fclean all