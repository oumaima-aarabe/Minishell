/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 21:14:49 by ouaarabe          #+#    #+#             */
/*   Updated: 2023/07/02 03:46:55 by ouaarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char *ft_take_key(char *str, t_env *env, int j, int *pos)
{
    str += j;
    if (*str == '?')
    {   
        int ex_s = g_v.ex_s;
        g_v.ex_s = 0;
        if (*(str + 1))
        {
            *pos = j + 1;
            return ft_itoa(ex_s);
        }
        else
        {
            *pos = j;
            return ft_itoa(ex_s);
        }
    }
    else
    {
        // Find the end of the key by checking for non-alphanumeric characters
        int key_len = 0;
        while (*(str + key_len)  && (*(str + key_len) != '$' || *(str + key_len) != '\'' || *(str + key_len) != '\"' || *(str + key_len) != '+'))
            key_len++;
        
        char *key = ft_substr(str, 0, key_len);
		// *pos = key_len;
        while (env)
        {
            if (!ft_strcmp(key, env->key))
            {
                char *value = ft_strdup(env->valu);
                free(key);
                return value;
            }
            env = env->next;
        }

        free(key);
    }

    return ft_strdup("");
}



char *ft_expand(char *cmd, t_env *en)
{
    int j = 0;
    char *tmp;
    char *new;
    int in_single_quotes = 0;
    int in_double_quotes = 0;

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

        if (!in_single_quotes && cmd[j] == '$')
        {
            // Variable expansion for other variables
            tmp = ft_substr(cmd, 0, j);
            new = ft_take_key(&cmd[j + 1], en, 0, &j);
            free(cmd);
            cmd = ft_strjoin(tmp, new);
        }

        j++;
    }

    return cmd;
}




int main(int argc, char **argv, char **env)
{
	// char *pwd;
	char *prompt;
	// char *path;
	// splitnode *tokens = NULL;

	(void)argc;
	(void)argv;
	// if (!env[0])
	// 	ft_syntax_err();
	g_v.env = environment(env);
	// rl_catch_signals = 0;
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
	 	parsing(prompt, g_v.env );
		free(prompt);
		prompt = NULL;
	}
}

