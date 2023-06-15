/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 21:14:49 by ouaarabe          #+#    #+#             */
/*   Updated: 2023/06/15 16:05:07 by ouaarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void  hendl_ctr_c(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line(" ", 0);
	rl_redisplay();
		
}
int main(int argc, char **argv, char **env)
{
	char *pwd;
	char *prompt;

	(void)argc;
	(void)argv;
	if (!env[0])
		ft_syntax_err();
	while(2307)
	{
		signal(SIGINT, hendl_ctr_c);
		signal(SIGQUIT, SIG_IGN);
		pwd = strcat(getcwd(NULL, 0), " -> ");
		prompt = readline(pwd);		
		if (!prompt)
		{
			printf("exit \n");
            exit(0);
		}
		free(pwd);
		add_history(prompt);
		if (!lexer(prompt) || !lexer2(prompt))
		{
			ft_syntax_err();
			continue;
		}
		parsing(prompt);
		free(prompt);
		prompt = NULL;	
	}
}

