/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 02:31:42 by ouaarabe          #+#    #+#             */
/*   Updated: 2023/05/25 01:13:03 by ouaarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

int		lexer(char *line);
void	ft_syntax_err(void);
char	*ft_strjoin(char *s1, char *s2);
// void    parse_command(char *prompt);
// char	**ft_split(char const *s, char c);
// int		ft_isalnum(int c)''


typedef enum t_flags
{
	PIPE,
	DQ,
	SQ,
	WORD,
	SP,
	HEREDOC,
	APPEND,
	RIN,
	ROUT
}           flag;

typedef struct command_list{
	char **cmd;
	struct command_list *next;
	struct command_list *prev;
}cmd_l;

typedef struct  t_tokens{
	int 	flag;
	char	*cmd;
	struct t_tokens *right;
	struct t_tokens *left;
}s_tokens;

#endif