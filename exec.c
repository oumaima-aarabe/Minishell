/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azarda <azarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 23:34:37 by azarda            #+#    #+#             */
/*   Updated: 2023/06/09 17:04:11 by azarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"


void ft_hairdoc(char **tab)
{
	char *str;
	while(1)
	{
		str = readline("> ");
		if(!ft_strcmp(str, tab[1]))
			break;
		free(str);
		str = NULL;

	}
}
void ft_exucve(char *cmd, char **arg, char **env)
{
	int pid;
			pid = fork();
			if(!pid)
			{
				if(execve(cmd, arg, env) < 0)
				{
				ft_print_err(cmd , " : No such file or directory\n");
				free(cmd);
				ft_free_(arg);
				ft_free_(env);
				exit (0);
				}
			// ft_free_(env);
			}
	wait(&pid);

}


// void le ()
// {
// 	system("leaks Minishell");
// }
//________________________________________________________________________________

int ft_lstsize(t_env *env)
{
	int i = 0;

	while(env)
	{
		i++;
		env = env->next;
	}
	return i;

}

char **ft_my_env(t_env *en)
{
	char **tab;
	t_env *env = duplicate_linked_list(en);

	// while(env)
	// {
	// 	printf("key is  %s valu is %s\n" ,env->key, env->valu);
	// 	env = env->next;
	// }
	// exit(8);



	tab = (char **)malloc(sizeof(char *) * (ft_lstsize(env) + 1));
	int i = 0;
	char *key;
	char *valu;

	while(env)
	{
		key = ft_strjoin(ft_strdup(env->key), ft_strdup("="));
		valu = ft_strjoin(key ,ft_strdup(env->valu));
		tab[i] = valu;
		free(env);
		env = env->next;
		i++;
	}
	// free(env);
	ft_lstclear(&env);
	tab[i] = NULL;
	return tab;
}



//________________________________________________________________________________


void ft_exec(char **tab, t_env *env)
{
	char *test = NULL;
	char **tmp = NULL;
	// char **str0;
	char *ss;
	// int p;
	int i = 0;


	ss = NULL;

	char **my_env = NULL;


	my_env = ft_my_env(env);



	if(tab[0] != NULL)
	{

		if(!ft_strcmp(tab[0], "<<"))
				ft_hairdoc(tab);
			else
			{
		while(env)
		{
			if((!ft_strcmp("PATH", env->key)))
			{

				tmp = ft_split(env->valu, ':');
				break;
			}
			env = env->next;
		}

		if(tab[0][0] == '.' || tab[0][0] == '/')
		{
			ft_free_(tmp);
			ss = ft_strdup(tab[0]);
		}
		else if(tmp)
		{
		while(tmp[i])
		{
			test = ft_strjoin(ft_strdup("/"), ft_strdup(tab[0]));
			ss = ft_strjoin(ft_strdup(tmp[i]), test);
			if(!(access(ss, F_OK)))
				break;
			else
			{
				free(ss);
				ss = NULL;
				i++;
			}
			if(!tmp[i])
			{
				ft_print_err(tab[0], ": command not found\n");
				ex_s = 127;
			}
		}
		ft_free_(tmp);
		}
		// dup2(fd, 1);
		// printf("--->>%s\n", ss);
//---------------------------------------------------------------------------------------------------

		if(ss)
		{
			ft_exucve(ss, tab, my_env);
		}

		ft_free_(my_env);

		free(ss);
		ss = NULL;
		}
	}

}
