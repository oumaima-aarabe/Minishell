# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/15 15:19:53 by azarda            #+#    #+#              #
#    Updated: 2023/07/03 08:16:41 by ouaarabe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc

FLAGS = -Wall -Wextra -Werror -g -fsanitize=address
INCLUDE = minishell.h

READ_LINE = /Users/ouaarabe/.brew/Cellar/readline/8.2.1

LIBRARIES	= -L${READ_LINE}/lib -lreadline -I includes -I ${READ_LINE}/include

INCLUDES	= -I${READ_LINE}/include


SRC =	obj/ft_error.c\
		obj/split_args.c\
		obj/split_tokens.c\
		obj/parse.c\
		obj/utils1.c\
		obj/quotes.c\
		obj/utils2.c\
		obj/main.c\
		obj/lexer.c\
		obj/redirections.c\
		obj/rm.c\
		obj/libft_azarda.c\
		obj/lst_azarda.c\
		# obj/ft_error.c\


OBJ = $(SRC:.c=.o)

mkdir = mkdir -p

dir = obj

#  //// should i use object file to compil //*/**/

all: $(NAME)

$(NAME): ${dir} $(OBJ)  $(INCLUDE)
	$(CC) $(FLAGS) ${LIBRARIES} $(OBJ) -o $(NAME) 


obj/%.o : %.c $(INCLUDE)
	$(CC) $(FLAGS) ${INCLUDES} -c $< -o $@

${dir} : 
	@${mkdir} ${dir}


clean:
	rm -rf obj
fclean:
	rm -rf $(NAME) obj

re: fclean all
