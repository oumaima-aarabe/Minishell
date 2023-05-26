/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 18:19:44 by azarda            #+#    #+#             */
/*   Updated: 2023/05/26 04:17:02 by ouaarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

void  ctr_c(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	// rl_replace_line(" ", 0);
	rl_redisplay();

}

void le()
{
	system("leaks Minishell");
}

t_env *ft_creat(char *key, char *val)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	else
	{
		new->key =  key;
		new->valu = val;
		new->next = NULL;
	}
	return (new);
}
t_env *environment(char **env)
{
	int i = 0;
	
	t_env *en = NULL;
	char **tmp;
	while(env[i])
	{
		tmp = ft_split(env[i], '=');
		ft_lstadd_back(&en, ft_creat(ft_strdup(tmp[0]) ,ft_strdup(tmp[1])));
		ft_free_(tmp);
		tmp = NULL;
		i++;
	}
	return(en);
}
void ft_env(t_env *env)
{
	while(env)
	{
		printf("%s=%s\n", env->key, env->valu);
		env = env->next;
	}
}

int compar(int a, int b)
{
	return (a <= b);
}


void ft_export(t_env *env)
{
	char 	*swap;

	t_env *tmp;
	tmp = env;
	while(env->next != NULL)
	{
		if ((compar(env->key[0], env->next->key[0])) == 0)
		{
			swap = env->key;
			env->key = env->next->key;
			env->next->key = swap;
			env = tmp;
		}
		else
			env = env->next;
	}
	env = tmp;
	while(env)
	{
		printf("declare -x %s=%s\n",env->key, env->valu);
		env = env->next;
	}
}

int main(int ac, char **av, char  **env)
{
	(void)av;
	char *pwd;
	char *str;
	char **ok;
	t_env *en;
	en = environment(env); 
	if(ac != 1)
	{
		printf("Minishell no take arguments\n"); // change msg
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
		if(!(ft_strcmp(ok[0], "env")))
			ft_env(en); // he nide SHELV
		else if(!(ft_strcmp(ok[0], "export")))
			ft_export(en); 
		else
			ft_exec(ok, en, env);
		ft_free_(ok);
		ok = NULL;
	}
}
