/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azarda <azarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 18:19:44 by azarda            #+#    #+#             */
/*   Updated: 2023/05/21 20:26:44 by azarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

void  ctr_c(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line(" ", 0);
	rl_redisplay();

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

void ft_autre_cmd(char **tab, char **env)
{
	execve(tab[0], tab, env);
}

int main(int ac, char **av, char  **env)
{
	(void)av;
	// (void)env;
	char *pwd;
	if(ac != 1)
	{
		printf("Minishell ma katakhod waloo \n"); // change msg
		exit(1);
	}
	int i = 0;
	char **tmp = NULL;
	char **str0 = NULL;
	// int j = 5;
	// int x = 0;
	while(env[i])
	{
		if(!strncmp(env[i],"PATH=", 5))
		{
			str0 = ft_split(env[i], '=');
			tmp = ft_split(str0[1], ':');
			// printf("%s\n", str0);
			// exit (0);
		}
		i++;
	}
	i = 0;
	// while(tmp[i])
	// {
	// 	printf("%s\n", tmp[i++]);

	// }


	int p;
	char *str;
	char *ss;
	char *test;
	char **ok;

	while(1337)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT,  ctr_c);
		pwd = ft_strjoin(getcwd(NULL, 0), " -> "); // 1bite leaks pwd
		str = readline(pwd);
		free(pwd);
		if(!str)
		{
			printf("exit\n");
			exit(0);
		}
		ok = ft_split(str, ' ');
//--------------------------------------------------------------------------------
		if(!ft_strcmp(str, "pwd"))
			printf("%s\n", getcwd(NULL, 0));
//--------------------------------------------------------------------------------

		else if(!ft_strcmp(str, "exit"))
		{
			// free(pwd);
			exit(0);
		}
//--------------------------------------------------------------------------------

		else if(!ft_strcmp(ok[0], "cd"))
			ft_exut_cd(ok);
		else if(!ft_strcmp(ok[0], "echo"))
			echo(ok);
		else
		{


//--------------------------------------------------------------------------------
	i = 0;
		while(tmp[i])
		{
		// printf("-->%s\n", str);
			test = ft_strjoin(ft_strdup("/"), ok[0]);
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
				printf("Minishell: %s: command not found\n", ok[0]);
		}
		if(ss)
		{
			p = fork();
			if(!p)
			{
				execve(ss, ok, env);
				// exit(0);
			}
			free(ss);
			ss = NULL;
		}
		wait(&p);
		}
//--------------------------------------------------------------------------------
		add_history(str);
		free(str);
		str = NULL;
	}
}
