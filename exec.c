/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azarda <azarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 23:34:37 by azarda            #+#    #+#             */
/*   Updated: 2023/06/09 17:04:11 by azarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"


void ft_hairdoc(char **tab)
{
	char *str;
	while(1)
	{
		str = readline("> ");
		if(!ft_strcmp(str, tab[1]))
			break;
		free(str);
		str = NULL;

	}
}

void lea()
	{
		system("leaks Minishell");
	}

void ft_exec(char **tab, t_env *env, char **ex)
{
	char *test;
	char **tmp;
	// char **str0;
	char *ss;
	int p;
	int i = 0;
	// (void)ex;

	if(tab[0] != NULL)
	{

		if(!ft_strcmp(tab[0], "<<"))
				ft_hairdoc(tab);
			else
			{
		while(env)
		{
			if((!ft_strcmp("PATH", env->key)))
				break;
			env = env->next;
		}
		tmp = ft_split(env->valu, ':');
		// while(env[i])
		// {
		// 	if(!strncmp(env[i],"PATH=", 5))
		// 	{
		// 		str0 = ft_split(env[i], '=');
		// 		tmp = ft_split(str0[1], ':');
		// 		ft_free_(str0);
		// 	}
		// 	i++;
		// }
		i = 0;
		// int fd = open ("test", O_RDWR, 0777);
		if(!(access(tab[0], F_OK)))
		{
			ss = ft_strdup(tab[0]);
		}
		else
		{
		while(tmp[i])
		{
			test = ft_strjoin(ft_strdup("/"), ft_strdup(tab[0]));
			ss = ft_strjoin(ft_strdup(tmp[i]), test);
			if(!(access(ss, F_OK)))
				break;
			else
			{
			free(ss);
			ss = NULL;
			i++;
			}
			if(!tmp[i])
				printf("Minishell: %s: command not found\n", tab[0]);
		}
		}
		ft_free_(tmp);
		// dup2(fd, 1);
		// printf("--->>%s\n", ss);
//---------------------------------------------------------------------------------------------------
		if(ss)
		{
			p = fork();
			if(!p)
			{
				if(execve(ss, tab, ex) == -1)
				exit (0);
			}
		}

		wait(&p);
		free(ss);
		ss = NULL;
		}
	}
}
