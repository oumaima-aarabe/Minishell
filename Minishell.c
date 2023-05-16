/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azarda <azarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 18:19:44 by azarda            #+#    #+#             */
/*   Updated: 2023/05/16 22:30:24 by azarda           ###   ########.fr       */
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
		pwd = ft_strjoin(getcwd(NULL, 0), " -> "); 
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT,  ctr_c);
		str = readline(pwd);
		free(pwd);
		if(!str)
		{
			printf("exit\n");
			exit(0);
		}
		if(!ft_strcmp(str, "pwd"))
			printf("%s\n", getcwd(NULL, 0));


	}
}
