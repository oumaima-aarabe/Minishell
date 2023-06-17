/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azarda <azarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 18:19:44 by azarda            #+#    #+#             */
/*   Updated: 2023/06/09 21:48:43 by azarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

void  ctr_c(int sig)
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

//________________________________________________________________________________

void le()
{
	system("leaks Minishell");
}
//________________________________________________________________________________



//________________________________________________________________________________


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
			if(cmd[i][j] ==  '$')
			{
				tmp = ft_substr(cmd[i], 0, j);
				free(cmd[i]);
				new = ft_take_key(cmd[i], en, j + 1);
				cmd[i] = ft_strjoin(tmp , new);
			}
			j++;
		}
		i++;
	}
	return (cmd);
}




int main(int ac, char **av, char  **env)
{
	(void)av;
	// char *pwd;
	char *str;
	char **cmd;


	t_env *en;

	// if(!env || !(*env))
	// 	exit(5);

	en = environment(env);


	if(ac != 1)
	{
		printf("Minishell no take arguments\n"); // change msg
		exit(1);
	}

	// atexit(le);
	rl_catch_signals=0;
	while(1337)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT,  ctr_c);
		//pwd = ft_strjoin(getcwd(NULL, 0), " -> "); // 1bite leaks pwd
		str = readline("Minishell $ ");
		// free(pwd);
		if(!str)
		{
			printf("exit\n");
			exit(0);
		}
		cmd = ft_split(str, ' ');
		cmd = ft_expend(cmd,en);
		add_history(str);
		free(str);
		str = NULL;
		if(ft_execut_bultins(cmd, en))
		{
			ft_free_(cmd);
			continue;
		}

			ft_exec(cmd, en);


			ft_free_(cmd);

	}
}
