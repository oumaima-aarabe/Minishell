/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azarda <azarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 21:14:49 by ouaarabe          #+#    #+#             */
/*   Updated: 2023/06/25 15:52:14 by azarda           ###   ########.fr       */
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

t_env *ft_shelvl(t_env *env)
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
		}
		tmp = tmp->next;
	}
	return(env);
}

t_env *environment(char **env)
{
	int i = 0;
	int j = 0;
	t_env *en = NULL;
	while(env[i])
	{
		j = ft_sine(env[i], '=');
		ft_lstadd_back(&en, ft_creat(ft_substr(env[i], 0, j), ft_substr(env[i], j + 1, (ft_strlen(env[i]) - j ))));
		i++;
	}
	en = ft_shelvl(en);
	return(en);
}








//________________________________________________________________________________

void free_split_nodes(splitnode *head)
{
    while (head != NULL)
    {
        splitnode   *current = head;
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

char *ft_take_key(char *str, t_env *env, int j)
{

	str += j;
	while(env)
	{
		if(!ft_strcmp(str, env->key))
		return (ft_strdup(env->valu));
		env = env->next;
	}
	return (ft_strdup(""));
}

char **ft_expend(char **cmd, t_env *en)
{
	int i = 0;
	int j = 0;
	char *tmp;
	char *new;

	while(cmd[i])
	{
		j = 0;
		while(cmd[i][j])
		{
			if(cmd[i][j] ==  '$' && cmd[i][j + 1] ==  '?')
			{
				tmp = ft_substr(cmd[i], 0, j);
				new = ft_substr(cmd[i], j + 2, ft_strlen(cmd[i]) - j);
				free(cmd[i]);
				cmd[i] = ft_strjoin(tmp, ft_strjoin(ft_itoa(g_v.ex_s), new));
				g_v.ex_s = 0;
			}
			if(cmd[i][j] ==  '$')
			{
				tmp = ft_substr(cmd[i], 0, j);
				new = ft_take_key(cmd[i], en, j + 1);
				free(cmd[i]);
				cmd[i] = ft_strjoin(tmp , new);

			}
			j++;
		}
		i++;
	}
	return (cmd);
}

int main(int argc, char **argv, char **env)
{
	// char *pwd;
	char *prompt;
	// char *path;
	splitnode *tokens = NULL;

	(void)argc;
	(void)argv;
	// if (!env[0])
	// 	ft_syntax_err();
	g_v.env = environment(env);
	rl_catch_signals = 0;
	while(2307)
	{
		signal(SIGINT, hendl_ctr_c);
		signal(SIGQUIT, SIG_IGN);

		// path = getcwd(NULL, 0);
		// pwd = ft_strcat(path, " -> ");
		// free (path);
		prompt = readline("Minishell -> ");
		if (!prompt)
		{
			printf("exit \n");
			// free (pwd);
            exit(0);
		}
		// free(pwd);
		add_history(prompt);
		if (!lexer(prompt) || !lexer2(prompt))
		{
			ft_syntax_err();
			continue;
		}
		tokens = parsing(prompt);
		if(!tokens)
			continue;
		free(prompt);
		prompt = NULL;
		execution(tokens);
		puts("");
		free_split_nodes(tokens);

	}
}

