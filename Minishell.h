/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 18:19:50 by azarda            #+#    #+#             */
/*   Updated: 2023/05/22 14:49:17 by ouaarabe         ###   ########.fr       */
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

typedef struct Command_t {
	char	*command;
	char	**arguments;
	char	*infile;
	char	*outfile;
	int 	pipe;
	struct Command_t *next;
} Command;

typedef struct {
	Command	*head;
} CommandTable;

typedef struct arg_s {
    char    *argument;
	int 	argIndex;
    int 	inQuote;
    int 	argCount;
    int 	argSize;
}arg_t;
/************************************************************************************************
 *                              PARSING                                                         *
************************************************************************************************/
Command	*createCommandNode();
void	freeCommandNode(Command *node);
void	freeCommandTable(CommandTable  *table);
void	parsecommand(char  *input, CommandTable *table);

/************************************************************************************************
 *                              UTILS                                                           *
************************************************************************************************/
int	ft_strcmp(char	*s1, char	*s2);
char	*ft_strjoin(char *s1, char *s2); // free
char	**ft_split(char *st, char c);
int		ft_strlen(char const *str);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strdup(char *s1);
void	ft_free_(char **tab);

#endif
