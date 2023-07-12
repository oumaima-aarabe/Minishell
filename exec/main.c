/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azarda <azarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 21:14:49 by ouaarabe          #+#    #+#             */
/*   Updated: 2023/07/12 01:10:30 by azarda           ###   ########.fr       */
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

char *ft_expand(char *cmd, t_env *en)
{
	int j = 0;
	char *tmp;
	char *new;
	int in_single_quotes = 0;
	int in_double_quotes = 0;

	if (cmd)
	{
		while (cmd[j])
		{
			if (cmd[j] == '\'')
			{
				if (!in_double_quotes)
					in_single_quotes = !in_single_quotes;
			}
			else if (cmd[j] == '\"')
			{
				if (!in_single_quotes)
					in_double_quotes = !in_double_quotes;
			}

			if (!in_single_quotes && (cmd[j] == '$' && cmd[j + 1] == '?'))
			{
				printf("===%d\n", g_v.ex_s);
				tmp = ft_substr(cmd, 0, j);
				new = ft_substr(cmd, j + 2, ft_strlen(cmd) - j);
				free(cmd);
				cmd = ft_strjoin(tmp, ft_strjoin(ft_itoa(g_v.ex_s), new));
				g_v.ex_s = 0;
			}
			else if (!in_single_quotes && cmd[j] == '$' && cmd[j + 1] && (isalnum(cmd[j + 1]) || cmd[j + 1] == '_'))
			{
				int len = 0;
				int pos = j + 1;
				while (cmd[pos] && (isalnum(cmd[pos]) || cmd[pos] == '_'))
				{
					len++;
					pos++;
				}
				// Variable expansion for other variables
				tmp = ft_substr(cmd, 0, j);
				new = ft_substr(cmd, j + len + 1, ft_strlen(cmd) - (j + len + 1));
				char *value = ft_take_key(cmd, en, j + 1, len);
				if (ft_strlen(value))
				{
					char *expanded = ft_strjoin(value, new);
					free(cmd);
					cmd = ft_strjoin(tmp, expanded);
					j += len;
				}
				else
				{
					free(cmd);
					cmd = ft_strjoin(tmp, new);
				}

			}
			else if (cmd[j])
				j++;
		}
	}
	return cmd;
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
