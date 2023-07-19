# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/15 15:19:53 by azarda            #+#    #+#              #
#    Updated: 2023/07/19 05:17:07 by ouaarabe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

INCLUDE = Minishell.h


CC = cc

READLINE = $(shell brew --prefix readline)

FLAGS = -Wall -Werror -Wextra  -I$(READLINE)/include -g -fsanitize=address



SRC =	obj/ft_error.c\
		obj/split_args.c\
		obj/split_tokens.c\
		obj/new_list.c\
		obj/parse.c\
		obj/utils1.c\
		obj/utils2.c\
		obj/utils3.c\
		obj/main.c\
		obj/lexer.c\
		obj/libft_util.c \
		obj/exec.c \
		obj/lst_utils.c \
		obj/builtins.c \
		obj/ft_go_exec.c\
		obj/redirections.c\
		obj/quotes.c\
		obj/free.c\
		obj/ft_excute_cd.c\
		obj/env.c\
		obj/expand.c\
		obj/double_split.c\
		obj/ft_export.c\
		obj/ft_export2.c\
		obj/ft__execution.c\
		obj/red_handle.c\
		obj/rm_utils.c\
		obj/heredoc_rm.c\
		obj/utils4.c\
		obj/exec_2.c\
		obj/heredoc.c\
		obj/rm.c



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
