/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azarda <azarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 18:19:50 by azarda            #+#    #+#             */
/*   Updated: 2023/05/21 22:54:59 by azarda           ###   ########.fr       */
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

typedef struct Command {
    char* command;
    char** arguments;
    char* infile;
    char* outfile;
    int pipe;
    struct Command* next;
} Command;

typedef struct {
    Command* head;
} CommandTable;

int	ft_strcmp(char	*s1, char	*s2);
char	*ft_strjoin(char *s1, char *s2); // free
char	**ft_split(char *st, char c);
int		ft_strlen(char const *str);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strdup(char *s1);
void	ft_free_(char **tab);

#endif
