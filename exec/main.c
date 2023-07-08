/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azarda <azarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 21:14:49 by ouaarabe          #+#    #+#             */
/*   Updated: 2023/07/08 21:39:30 by azarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

t_gs	g_v;

void  hendl_ctr_c(int sig)
{
	(void)sig;
	if (waitpid(0, NULL, WNOHANG))
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line(" ", 0);
		rl_redisplay();
		// exit status
	}
}

int ft_sine(char *st, char c)
{
	int i = 0;

	while(st[i])
	{
		if(st[i] == c)
			return (i);
		i++;
	}
	return 0;
}

void	ft_shelvl(t_env *env)
{
	t_env *tmp;
	static  int i;
	tmp = env;
	while(tmp)
	{
		if(!ft_strcmp("SHLVL", tmp->key))
		{
			i = ft_atoi(tmp->valu);
			if(i >= 999)
				i = 0;
			else
				i += 1;
			free(tmp->valu);
			tmp->valu = ft_itoa(i);
			return ;
		}
		tmp = tmp->next;
	}
	ft_add_export("SHLVL=1");
}

void	environment(char **env)
{
	int i = 0;
	int j = 0;
	// g_v.env = malloc(sizeof(t_env));
	// 	if(!g_v.env)
	// 		return(exit(1));
	// 	puts("herr");
	while(env[i])
	{
		j = ft_sine(env[i], '=');
		ft_lstadd_back(&g_v.env, ft_creat(ft_substr(env[i], 0, j), ft_substr(env[i], j + 1, (ft_strlen(env[i]) - j ))));
		i++;
	}
	ft_shelvl(g_v.env);
}








//________________________________________________________________________________

void free_split_nodes(t_splitnode *head)
{
    while (head != NULL)
    {
        t_splitnode   *current = head;
        head = head->next;

        int i = 0;
        while (current->splitdata[i])
        {
            free(current->splitdata[i]);
            i++;
        }
        free(current->splitdata);
        free(current);
    }
}


//________________________________________________________________________________

char *ft_take_key(char *str, t_env *env, int j, int len)
{

	str += j;
	while(env)
	{
		if(!ft_strncmp(str, env->key, len))
		{
			if(env->valu)
				return (ft_strdup(env->valu));
			else
				break;
		}
		env = env->next;
	}
	return (ft_strdup(""));
}

char *ft_expand(char *cmd, t_env *en)
{
	int j = 0;
	char *tmp;
	char *new;
	int in_single_quotes = 0;
	int in_double_quotes = 0;

		// printf ("cmd ={%s}\n", cmd);
		fflush(stdout);
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
				// Variable expansion for $?
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
					j += len + 1;
				}
				else
				{
					free(cmd);
					cmd = ft_strjoin(tmp, new);
				}

			}
			else
				j++;
			// printf ("new : j = %d cmd ={%s}\n", j, cmd);
		}
	return cmd;
}

int main(int argc, char **argv, char **env)
{
	// char *pwd;
	char *prompt = NULL;
	// char *path;
	t_splitnode *tokens = NULL;
	// int i = 0;
	// while(env[i])
	// 	printf("-> %s\n", env[i++]);

	(void)argc;
	(void)argv;
	// if (!env[0])
	// 	ft_syntax_err();
	environment(env);
	// rl_catch_signals = 0;
	while(2307)
	{
		signal(SIGINT, hendl_ctr_c);
		signal(SIGQUIT, SIG_IGN);

		prompt = readline("Minishell -> ");
		if (!prompt)
		{
			printf("exit\n");
			// free (pwd);
            exit(0);
		}
		// free(pwd);
		int i = -1;
		while (prompt[++i])
			if (prompt[i] != ' ' && prompt[i] != '\t')
				break ;
		if (prompt[i])
			add_history(prompt);
		if (!lexer(prompt) || !lexer2(prompt))
		{
			ft_syntax_err();
			continue;
		}
		// tokens = parsing(prompt, g_v.env);
		tokens = parsing(prompt, g_v.env);
		free(prompt);
		prompt = NULL;
		// puts("----mora hna bdit ana ------");
		execution(tokens);
		free_split_nodes(tokens);
	}
}

