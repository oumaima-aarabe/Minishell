/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azarda <azarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 23:34:37 by azarda            #+#    #+#             */
/*   Updated: 2023/05/22 00:57:37 by azarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"


void echo(char **tab)
{
	int i = 0;
	int j = 0;
	int bol = 1;

	if(!ft_strcmp(tab[i], "echo"))
	{
		i++;
		if(tab[i] && tab[i][0] == '-' && tab[i][1] == 'n')
		{
			j = 2;
			while(tab[i][j] && tab[i][j] == 'n')
				j++;
			if(tab[i][j])
				bol = 1;
			else
			{
				bol = 0;
				i++;
			}
		}
		while (tab[i])
			printf("%s ", tab[i++]);
		if(bol)
			printf("\n");
	}

}

void ft_exut_cd(char **str)
{

	if(!ft_strcmp(str[0], "cd"))
	{
		if(!str[1])
			chdir(getenv("HOME"));
		else if(chdir(str[1]) < 0)
		{
			ft_putstr_fd("Minishell: cd: ", 2);
			perror(str[1]);
		}
	}
}

void lea()
	{
		system("leaks Minishell");
	}

void ft_exec(char **tab, char **env)
{
	char *test;
	char **tmp;
	char **str0;
	char *ss;
	int p;
	int i = 0;



	if(!ft_strcmp(tab[0], "pwd"))
			printf("%s\n", getcwd(NULL, 0));
	else if(!ft_strcmp(tab[0], "exit"))
	{
		// free(pwd);
		// atexit(lea);
		exit(0);
	}
		else if(!ft_strcmp(tab[0], "cd"))
			ft_exut_cd(tab);
		else if(!ft_strcmp(tab[0], "echo"))
			echo(tab);
		else
		{
	while(env[i])
	{
		if(!strncmp(env[i],"PATH=", 5))
		{
			str0 = ft_split(env[i], '=');
			tmp = ft_split(str0[1], ':');
			ft_free_(str0);
		}
		i++;
	}
	i = 0;
	while(tmp[i])
	{
		test = ft_strjoin(ft_strdup("/"), tab[0]);
		ss = ft_strjoin(ft_strdup(tmp[i]), test);
		free(test);
		test = NULL;
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
	ft_free_(tmp);
	if(ss)
	{
		p = fork();
		if(!p)
		{
			execve(ss, tab, env);
		}
	}
	wait(&p);
	free(ss);
	ss = NULL;
	}
}
