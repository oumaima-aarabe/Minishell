/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 23:34:37 by azarda            #+#    #+#             */
/*   Updated: 2023/05/26 04:15:05 by ouaarabe         ###   ########.fr       */
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
		while(tab[i] && (ft_strncmp(tab[i], "-n", 2)) == 0)
		{
			j = 2;
			while(tab[i][j] && tab[i][j] == 'n')
				j++;
			if(tab[i][j])
				bol = 1;
			else
				bol = 0;
			i++;
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



	if(!ft_strcmp(tab[0], "pwd"))
			printf("%s\n", getcwd(NULL, 0));
	else if(!ft_strcmp(tab[0], "exit"))
	{
		// free(pwd);
		// atexit(lea);
		printf("exit\n");
		exit(0);
	}
		else if(!ft_strcmp(tab[0], "cd"))
			ft_exut_cd(tab);
		else if(!ft_strcmp(tab[0], "echo"))
			echo(tab);
		else if(!ft_strcmp(tab[0], "<<"))
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
			execve(ss, tab, ex);
		}
	}
	wait(&p);
	free(ss);
	ss = NULL;
	}
}
