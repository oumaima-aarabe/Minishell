/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azarda <azarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 18:19:44 by azarda            #+#    #+#             */
/*   Updated: 2023/05/22 01:25:55 by azarda           ###   ########.fr       */
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

void le()
{
	system("leaks Minishell");
}

int main(int ac, char **av, char  **env)
{
	(void)av;
	char *pwd;
	char *str;
	char **ok;
	if(ac != 1)
	{
		printf("Minishell ma katakhod waloo \n"); // change msg
		exit(1);
	}
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
			// atexit(le);
			exit(0);
		}
		ok = ft_split(str, ' ');
		add_history(str);
		free(str);
		str = NULL;
		ft_exec(ok, env);
		ft_free_(ok);
		ok = NULL;
	}
}
