/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 21:14:49 by ouaarabe          #+#    #+#             */
/*   Updated: 2023/07/19 05:31:18 by ouaarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

void	hendl_ctr_c(int sig)
{
	(void)sig;
	if (waitpid(0, NULL, WNOHANG))
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_v.ex_s = 1;
	}
}

void	ft_pwd(void)
{
	char	*pwd;

	pwd = NULL;
	free(pwd);
	pwd = getcwd(NULL, 0);
	if (pwd)
	{
		free(g_v.pwd);
		g_v.pwd = pwd;
	}
}

int	main(int argc, char **argv, char **env)
{
	char		*prompt;
	t_splitnode	*tokens;

	tokens = NULL;
	(void)argc;
	(void)argv;
	if (isatty(STDIN_FILENO) == 0)
		return (0);
	rl_catch_signals = 0;
	environment(env);
	while (1337)
	{
		prompt = NULL;
		signal(SIGINT, hendl_ctr_c);
		signal(SIGQUIT, SIG_IGN);
		prompt = readline("Minishell -> ");
		if (!prompt)
			return (printf("exit\n"), g_v.ex_s);
		if (prompt[0])
			if (!valid_syntax(prompt))
				continue ;
		free (prompt);
	}
}
