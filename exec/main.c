/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 21:14:49 by ouaarabe          #+#    #+#             */
/*   Updated: 2023/07/12 01:58:43 by ouaarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

t_gs	g_v;

void  hendl_ctr_c(int sig)
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

int main(int argc, char **argv, char **env)
{
	char *prompt;
	t_splitnode *tokens;

	tokens = NULL;
	(void)argc;
	(void)argv;
	if(isatty(STDIN_FILENO) == 0)
		return (0);
	rl_catch_signals = 0;
	environment(env);
	while(1337)
	{
		prompt = NULL;
		signal(SIGINT, hendl_ctr_c);
		signal(SIGQUIT, SIG_IGN);
		prompt = readline("Minishell -> ");
		if (!prompt)
			return(printf("exit\n"), exit(0), 1);
		if (prompt[0])
			add_history(prompt);
		if (!lexer(prompt) || !lexer2(prompt))
		{
			ft_syntax_err();
			continue;
		}
		tokens = parsing(prompt, g_v.env);
		free(prompt);
		execution(tokens);
		free_split_nodes(tokens);
	}
}
