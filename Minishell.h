/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azarda <azarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 18:19:50 by azarda            #+#    #+#             */
/*   Updated: 2023/06/09 22:21:00 by azarda           ###   ########.fr       */
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
# include <sys/wait.h>
# include <fcntl.h>


typedef struct s_env
{
	char *key;
	char *valu;
	struct s_env *next;
}   t_env;

// typedef struct s_shell
// {
// 	char *pwd;
// } t_shell;


void	ft_lstadd_back(t_env **alst, t_env *new);
void	ft_lstclear(t_env **alist);
void	ft_putstr_fd(char *s, int fd);
void	ft_free_(char **tab);
void	ft_exec(char **ok, t_env *en, char **ex);


char	*ft_strjoin(char *s1, char *s2); // free
char	*ft_strdup(char *s1);
char	*ft_substr(char const *s,  int start, int len);
char	**ft_split(char *st, char c);

int	ft_strcmp(char	*s1, char	*s2);
int	ft_strlen(char const *str);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
int	ft_execut_bultins(char **cmd, t_env *env);
int	ft_atoi(char *str);


t_env	*ft_creat(char *key, char *val);
t_env	*duplicate_linked_list(t_env *last);

#endif
