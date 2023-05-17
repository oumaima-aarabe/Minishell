/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azarda <azarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 18:19:44 by azarda            #+#    #+#             */
/*   Updated: 2023/05/17 01:57:41 by azarda           ###   ########.fr       */
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
void ft_exut_cd()
{
	fork();
	chdir("/Users/azarda/Desktop/");
	// sleep(10);
	// exit(0);
}


int main(int ac, char **av, char  **env)
{
	(void)av;
	(void)env;
	char *pwd;
	if(ac != 1)
	{
		printf("Minishell ma katakhod waloo \n"); // change msg
		exit(1);
	}
	char *str;
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
			free(pwd);
		}
		if(!ft_strcmp(str, "pwd"))
			printf("%s\n", getcwd(NULL, 0));
		if(!ft_strcmp(str, "cd"))
			ft_exut_cd();
		if(!ft_strcmp(str, "exit"))
		{
			free(pwd);
			exit(0);
		}
		add_history(str);
		free(str);
	}
}
