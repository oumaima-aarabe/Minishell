/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 18:19:50 by azarda            #+#    #+#             */
/*   Updated: 2023/05/26 01:46:43 by ouaarabe         ###   ########.fr       */
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


typedef struct s_env
{
    char *key;
    char *valu;
    struct s_env *next;
}   t_env;


int	ft_strcmp(char	*s1, char	*s2);
char	*ft_strjoin(char *s1, char *s2); // free
char	**ft_split(char *st, char c);
int		ft_strlen(char const *str);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strdup(char *s1);
void	ft_free_(char **tab);
void ft_exec(char **ok, char **env);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_lstadd_back(t_env **alst, t_env *new);


#endif
